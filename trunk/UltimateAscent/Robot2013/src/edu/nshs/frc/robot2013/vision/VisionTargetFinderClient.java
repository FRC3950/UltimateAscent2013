/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package edu.nshs.frc.robot2013.vision;

import edu.wpi.first.wpilibj.networktables.NetworkTable;
import edu.wpi.first.wpilibj.networktables2.type.NumberArray;
import edu.wpi.first.wpilibj.tables.ITable;
import edu.wpi.first.wpilibj.tables.ITableListener;

/**
 *
 * @author rsaccone
 */
public class VisionTargetFinderClient implements ITableListener {
 
    final Object lock = new Object();
    long requestId;
    int goalType;
    double avgDistance = 0.0;
    double angle = 0.0;
    
    NetworkTable table;
    
    public static void clearVisionTableValues() {
        NetworkTable table = NetworkTable.getTable(VisionNetworkTableDefs.VISION_NETWORK_TABLE);
        NumberArray data = new NumberArray();
        data.add(0);
        data.add(0);
        
        // Clear out the request data.
        table.putValue(VisionNetworkTableDefs.TARGETING_REQUEST, data);
        
        // The result data is an array of four values, add two more.
        data.add(0);
        data.add(0);
        
        table.putValue(VisionNetworkTableDefs.TARGETING_RESULT, table);
        
        /*
        table.putNumber(VisionNetworkTableDefs.TARGET_TYPE_REQUEST_ID, (double)0);
        table.putNumber(VisionNetworkTableDefs.TARGET_TYPE_REQUEST, (double)GoalType.None);
        table.putNumber(VisionNetworkTableDefs.TARGET_AVG_DISTANCE_RESULT , (double)0);
        table.putNumber(VisionNetworkTableDefs.TARGET_ANGLE_RESULT, (double)0);
        */
    }
    
    public VisionTargetFinderClient(int goalType) {
        table = NetworkTable.getTable(VisionNetworkTableDefs.VISION_NETWORK_TABLE);
        this.goalType = goalType;
        table.addTableListener(this);
        requestId = System.currentTimeMillis();
        
        NumberArray msgRequest = new NumberArray();
        msgRequest.setSize(VisionNetworkTableDefs.TARGETING_REQUEST_ARRAY_SIZE);
        msgRequest.set(VisionNetworkTableDefs.TARGETING_REQUEST_ID_INDEX, requestId);
        msgRequest.set(VisionNetworkTableDefs.TARGETING_REQUEST_GOAL_TYPE_INDEX, goalType);
        
        // Publish the request
        table.putValue(VisionNetworkTableDefs.TARGETING_REQUEST, msgRequest);
        
        /* Get rid of this once arrays work.
        table.putNumber(VisionNetworkTableDefs.TARGET_TYPE_REQUEST_ID, (double)requestId);
        table.putNumber(VisionNetworkTableDefs.TARGET_TYPE_REQUEST, (double)goalType);
        */
        
        System.out.println("Published Targeting Request with Id = " + requestId);
    }
    
    public double getAngle() {
        synchronized(lock) {
            return angle;
        }
    }
    
    public double getDistance() {
        synchronized(lock) {
            return avgDistance;
        }
    }
    
    public void cancel() {
        synchronized(lock) {
            table.removeTableListener(this);
        }
    }
    
    public void valueChanged(ITable source, String key, Object value, boolean isNew) {
        System.out.println("ValueChanged: " + key + " Value: " + value + " new: " + isNew);
        
        if (key.equals(VisionNetworkTableDefs.TARGETING_RESULT)) {
            if (value instanceof NumberArray) {
                NumberArray msgResult = (NumberArray)value;
                synchronized(lock) {
                    parseTargetingResult(msgResult);
                }
            }        
        }
       
        /* 
         * Get rid of this once arrays work.
        
        synchronized(lock) {
            if (key.equals(VisionNetworkTableDefs.TARGET_TYPE_RESULT)) {
                if (value instanceof Double) {
                    double resultGoalType = ((Double)value).doubleValue(); 
                    if ((resultGoalType == goalType)  && matchRequestIdInTable()) {
                        angle = getDoubleFromNetworkTable(table, VisionNetworkTableDefs.TARGET_ANGLE_RESULT, 0.0);
                        avgDistance = getDoubleFromNetworkTable(table, VisionNetworkTableDefs.TARGET_AVG_DISTANCE_RESULT, 0.0);
                        System.out.println("VisionTargetFindClient: Received Results - angle = " + angle + ", avgDistance = " + avgDistance);
                    }
                }
            }
         }
         */
    }
    
    private boolean parseTargetingResult(NumberArray targetingResult) {
         
        if (targetingResult.size() != VisionNetworkTableDefs.TARGETING_RESULT_ARRAY_SIZE) {
            System.out.println("Targeting Result contained " + targetingResult.size() + " which isn't expected number of values" + VisionNetworkTableDefs.TARGETING_RESULT_ARRAY_SIZE);
            return false;
        }
        
        long resultId = (long)targetingResult.get(VisionNetworkTableDefs.TARGETING_RESULT_ID_INDEX);
        
        if (resultId != requestId) {
            System.out.println("Targeting Result Id (" + resultId + ") != requestId (" + requestId + ") ignoring");
            return false;
        }

        int resultGoalType = (int)targetingResult.get(VisionNetworkTableDefs.TARGETING_RESULT_GOAL_TYPE_INDEX);
        
        if (resultGoalType != goalType) {
            System.out.println("Targeting Result Goal Type (" + resultGoalType + ") != requestGoalType (" + goalType + ") ignoring");
            return false;
        }
        
        // Ids and goal type match!
        angle = targetingResult.get(VisionNetworkTableDefs.TARGETING_RESULT_ANGLE_INDEX);
        avgDistance = targetingResult.get(VisionNetworkTableDefs.TARGETING_RESULT_AVG_DISTANCE);
        
        return true;
    }
 
    /* Get rid of this once arrays work.
    private boolean matchRequestIdInTable() {
        long resultIdInTable = (long) getDoubleFromNetworkTable(table, VisionNetworkTableDefs.TARGET_TYPE_RESULT_ID, 0.0);
        
        return (resultIdInTable == requestId) ? true : false;
    }

    private static double getDoubleFromNetworkTable(NetworkTable table, String key, double defaultValue) {
        double result;
        
        Object v = table.getValue(key);
        
        if ((v != null) && (v instanceof Double)) {
            result = ((Double)v).doubleValue();
        }
        else {
            result = defaultValue;
        }
        
        return result;
    }
    */ 
}
