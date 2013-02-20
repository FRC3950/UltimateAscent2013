/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package roborealmtestharness;

import java.util.concurrent.*;
import edu.wpi.first.wpilibj.networktables.*;
import edu.wpi.first.wpilibj.networktables2.type.NumberArray;
import edu.wpi.first.wpilibj.tables.ITable;
import edu.wpi.first.wpilibj.tables.ITableListener;

/**
 * Instances of this class will take a request (from the Robot) to calculate the
 * distance and angle for the desired target goal using the SmartDashboard as
 * the communication mechanism. Once a calculation has been it will publish the
 * results back to the SmartDashboard.
 *
 * @author rsaccone
 */
public class RobotVisionServer implements ITableListener, VisionTargetFinderCallback {

    // Holds the details for a TargetingRequest.
    private class TargetingRequest implements Runnable {

        public long requestId;
        public GoalType targetType;

        public TargetingRequest(long reqId, GoalType goalType) {
            this.requestId = reqId;
            this.targetType = goalType;
        }

        public void run() {
            handleNewTargetingRequest(this);
        }
    }
    private static final double ANGLE_MARGIN_OF_ERROR_RANGE = 5.0;
    private final Object lock = new Object();  // Used to synchronize internal state.
    private ExecutorService _pool;
    private TargetingRequest _currTargetingRequest = null;
    private GoalType _currTargetRequest;
    private long _currRequestId = 0;
    private double _currTargetAsDouble;
    private double _lastAngleCalc = 0.0;
    private RoboRealmVisionTargetFinder _targetFinder = null;
    private NetworkTable _table;

    public RobotVisionServer(String address) {
        NetworkTable.setClientMode();
        NetworkTable.setIPAddress(address);
        _table = NetworkTable.getTable(VisionNetworkTableDefs.VISION_NETWORK_TABLE);

        if (_table == null) {
            // TBD: What to do if we can't get the _table
            // Does getTable return null or throw an exception.
        }


        // May want to use a pool with more than one thread.
        _pool = Executors.newSingleThreadExecutor();

        _table.addTableListener(this);
    }

    // Called each time a value changes in the network _table
    // Note this method is called with the internal lock the 
    // NetworkTable uses.  This means that we shouldn't take
    // any additional locks that could be used in a method that
    // publishes because a deadlock occurs.
    public void valueChanged(ITable source, String key, Object value, boolean isNew) {
        System.out.println("ValueChanged: " + key + " Value: " + value + " new: " + isNew);

        // Is this a key we care about?

        if (key.equals(VisionNetworkTableDefs.TARGETING_REQUEST)) {
            // Try to convert the number array into a TargetingRequest.
            TargetingRequest targReq = tryToConvertReceivedRequest(value);

            if (targReq != null) {
                // See note above. It isn't safe to take our 'lock' here 
                // due to the danger of deadlock.  Schedule the processing of
                // the request onto another thread.
                _pool.submit(targReq);
            }
        }
    }

    // Called each time the vision target _targetFinder calculates a new results.
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
            if (_currTargetingRequest == null) {
                System.out.println("Dropping angle calculation result, no _currTargetingRequest!");
                return;
            }

            if (_targetFinder == finder) {
                double marginOfError = angle - _lastAngleCalc;


                if (Math.abs(marginOfError) < ANGLE_MARGIN_OF_ERROR_RANGE) {
                    System.out.println("RobotServer publishing calculation results: (goal, avgDisance, angle) = (" + goalType + "," + avgDistance + "," + angle + ")");

                    NumberArray targetingResult = new NumberArray();
                    targetingResult.setSize(VisionNetworkTableDefs.TARGETING_RESULT_ARRAY_SIZE);

                    targetingResult.set(VisionNetworkTableDefs.TARGETING_RESULT_ID_INDEX, (double) _currTargetingRequest.requestId);
                    targetingResult.set(VisionNetworkTableDefs.TARGETING_RESULT_GOAL_TYPE_INDEX, mapGoalTypeToDouble(_currTargetingRequest.targetType));
                    targetingResult.set(VisionNetworkTableDefs.TARGETING_RESULT_AVG_DISTANCE, avgDistance);
                    targetingResult.set(VisionNetworkTableDefs.TARGETING_RESULT_ANGLE_INDEX, angle);

                    _table.putValue(VisionNetworkTableDefs.TARGETING_RESULT, targetingResult);
                    System.out.println("RobotVisionServer:Published targeting result back to client");
                }

                _lastAngleCalc = angle;
            }
        }
    }

    private TargetingRequest tryToConvertReceivedRequest(Object value) {
        double[] requestArray = tryToConvertObjectToDoubleArray(value);
        
        if (requestArray == null) {
            return null;
        }

        if (requestArray.length != VisionNetworkTableDefs.TARGETING_REQUEST_ARRAY_SIZE) {
            return null;
        }

        TargetingRequest newReq = new TargetingRequest((long) requestArray[VisionNetworkTableDefs.TARGETING_REQUEST_ID_INDEX],
                                                       mapDoubleToGoalType(requestArray[VisionNetworkTableDefs.TARGETING_REQUEST_GOAL_TYPE_INDEX]));

        return newReq;
    }

    private void handleNewTargetingRequest(TargetingRequest newRequest) {
        synchronized (lock) {
            if ((_targetFinder != null) && (_currTargetingRequest != null) && (_currTargetingRequest.targetType == newRequest.targetType)) {
                // Already targeting the new requested type.  We can reuse the target finder.
                _currTargetingRequest = newRequest;
                return;
            }

            // Have to start from scratch.
            if (_targetFinder != null) {
                _targetFinder.stop();
                _targetFinder = null;
            }

            _currTargetingRequest = newRequest;

            if (_currTargetingRequest.targetType != GoalType.None) {
                _targetFinder = new RoboRealmVisionTargetFinder(_currTargetingRequest.targetType, this);
                _targetFinder.start();
            }
        }
    }

    private static GoalType mapDoubleToGoalType(double requestedGoal) {
        int reqGoalAsInt = (int) requestedGoal;

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

    private static double[] tryToConvertObjectToDoubleArray(Object o) {
        if (o instanceof Object[]) {
            Object[] oarray = (Object[]) o;
            double result[] = new double[oarray.length];

            for (int i = 0; i < oarray.length; ++i) {
                if (oarray[i] instanceof Double) {
                    result[i] = ((Double) oarray[i]).doubleValue();
                } else {
                    // Unexpected result.
                    return null;
                }
            }

            return result;
        }

        return null;
    }
}
