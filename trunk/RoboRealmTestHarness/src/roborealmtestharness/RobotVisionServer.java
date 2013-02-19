/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package roborealmtestharness;

import edu.wpi.first.wpilibj.networktables.*;
import edu.wpi.first.wpilibj.tables.ITable;
import edu.wpi.first.wpilibj.tables.ITableListener;

/**
 * Instances of this class will take a request (from the Robot) to calculate the
 * distance and angle for the desired target goal using the SmartDashboard as 
 * the communication mechanism.  Once a calculation has been it will publish
 * the results back to the SmartDashboard.  
 * @author rsaccone
 */
public class RobotVisionServer implements ITableListener, VisionTargetFinderCallback {
    private static final double ANGLE_MARGIN_OF_ERROR_RANGE = 5.0;
    
    private final Object lock = new Object();  // Used to synchronize internal state.
    private GoalType currTargetRequest;
    private long currRequestId = 0;
    private double currTargetAsDouble;
    private double lastAngleCalc = 0.0;
    private RoboRealmVisionTargetFinder targetFinder = null;
    
    private NetworkTable table;
    
    public RobotVisionServer(String address) {
        NetworkTable.setClientMode();
        NetworkTable.setIPAddress(address);
        NetworkTable table = NetworkTable.getTable(VisionNetworkTableDefs.VISION_NETWORK_TABLE);
        
        if (table == null) {
            // TBD: What to do if we can't get the table
            // Does getTable return null or throw an exception.
        }
        
        table.addTableListener(this);
    }
    
    // Called each time a value changes in the network table
    public void valueChanged(ITable source, String key, Object value, boolean isNew) {
        System.out.println("ValueChanged: " + key + " Value: " + value + " new: " + isNew);
        
        // Is this a key we care about?
        if (key.equals(VisionNetworkTableDefs.TARGET_TYPE_REQUEST)) {
            
            // Expecting a double value.
            if (value instanceof Double) {
                double reqGoal = ((Double)value).doubleValue(); 
                newGoalTypeRequestHandler(reqGoal);
            }
            else {
                System.out.println("Received goal targeting request but value is not a Double as expected.");
            }
        }
    }
    
    // Called each time the vision target targetFinder calculates a new results.
    public void calcResult(RoboRealmVisionTargetFinder finder,
                           GoalType goalType,
                           double avgDistance,
                           double angle) {
        
        //*****************************************************************
        // TBD: Have to decide when to publish a result.  In other words do
        // we do results smoothing and stabilization here or on the robot.
        //*****************************************************************
        
        // Take the lock so that state is updated in a consistent manner with
        // respect to anyother methods that could be running concurrently.
        synchronized (lock) {
            // Make sure the target finder the message is from is the one
            // that we're using. (It could be left over!).
            if (targetFinder == finder) {
                double marginOfError = angle - lastAngleCalc;
                
                if (Math.abs(marginOfError) < ANGLE_MARGIN_OF_ERROR_RANGE) {
                    System.out.println("RobotServer publishing calculation results: (goal, avgDisance, angle) = (" + goalType + "," + avgDistance + "," + angle + ")");
                    table.putNumber(VisionNetworkTableDefs.TARGET_TYPE_RESULT, mapGoalTypeToDouble(goalType));
                    table.putNumber(VisionNetworkTableDefs.TARGET_TYPE_RESULT_ID, currRequestId);
                    table.putNumber(VisionNetworkTableDefs.TARGET_AVG_DISTANCE_RESULT , avgDistance);
                    table.putNumber(VisionNetworkTableDefs.TARGET_ANGLE_RESULT, angle);
                }
                
                lastAngleCalc = angle;
            }
        }
     }

    
    private void newGoalTypeRequestHandler(double goalRequest) {
        GoalType goalType = mapDoubleToGoalType(goalRequest);
                
        // Take the lock so that state is updated in a consistent manner with
        // respect to anyother methods that could be running concurrently.
        synchronized(lock) {
//           if (currTargetRequest != goalType) {
                if (targetFinder != null) {
                    // Tell the target targetFinder to quit.
                    targetFinder.stop();
                    currTargetRequest = GoalType.None;
                    currRequestId = 0;
                    currTargetAsDouble = VisionNetworkTableDefs.NO_TARGET;
                }

                // TBD: Need to do some error handling here.

                // Start a new targetFinder
                if (goalType != GoalType.None) {
                    lastAngleCalc = 0.0;
                    targetFinder = new RoboRealmVisionTargetFinder(goalType, this);
                    targetFinder.start();
                    currRequestId = 0; //(long)getDoubleFromNetworkTable(table, VisionNetworkTableDefs.TARGET_TYPE_REQUEST_ID, 0.0);
                    currTargetRequest = goalType;
                    currTargetAsDouble = goalRequest;
                }
                System.out.println("VisionServer: Received Target Type Request Notification id " + currRequestId + "for goal type " + goalType);
               
             }
//        }
    }
    
    private static GoalType mapDoubleToGoalType(double requestedGoal) {
        int reqGoalAsInt = (int)requestedGoal;
        
        switch (reqGoalAsInt) {
            case VisionNetworkTableDefs.HIGH_TARGET:
                return GoalType.HighGoal;
                
            case VisionNetworkTableDefs.MIDDLE_TARGET:
                return GoalType.MiddleGoal;
                
            case VisionNetworkTableDefs.NO_TARGET:
            default:
              return GoalType.None;
        }
    }
    
    private static double mapGoalTypeToDouble(GoalType goalType) {
        double result;
        
        switch (goalType) {
            case None:
            default:
                result = VisionNetworkTableDefs.NO_TARGET;
                break;
                
            case MiddleGoal:
                result = VisionNetworkTableDefs.MIDDLE_TARGET;
                break;
                
            case HighGoal:
                result = VisionNetworkTableDefs.HIGH_TARGET;
                break;
        }
        
        return result;
    }
    
    private static double getDoubleFromNetworkTable(NetworkTable table, String key, double defaultValue) {
        double result;

        return table.getNumber(key);
 //       Object v = table.getValue(key);

//        if ((v != null) && (v instanceof Double)) {
//            result = ((Double)v).doubleValue();
//        }
//        else {
//            result = defaultValue;
//        }
//
//        return result;
    }
}
