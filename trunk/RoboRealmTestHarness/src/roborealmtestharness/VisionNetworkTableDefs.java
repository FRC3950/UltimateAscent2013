/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package roborealmtestharness;

/**
 * This class simply encapsulates definitions used to communicate data
 * through the SmartDashboard.
 * 
 * @author rsaccone
 */
public final class VisionNetworkTableDefs {
    public static final String VISION_NETWORK_TABLE = "SmartDashboard";
    public static final String TARGET_TYPE_REQUEST_ID = "TARGET_TYPE_REQUEST_ID";
    public static final String TARGET_TYPE_REQUEST = "TARGET_TYPE_REQUEST";
    public static final String TARGET_TYPE_RESULT_ID = "TARGET_TYPE_RESULT_ID";
    public static final String TARGET_TYPE_RESULT = "TARGET_TYPE_RESULT";
    public static final String TARGET_AVG_DISTANCE_RESULT = "TARGET_AVG_DISTANCE_RESULT";
    public static final String TARGET_ANGLE_RESULT = "TARGET_ANGLE_RESULT";
    
    public static final int NO_TARGET     = 0;
    public static final int HIGH_TARGET   = 1;
    public static final int MIDDLE_TARGET = 2;

    // Don't allow any instances of the class to be constructed.
    private VisionNetworkTableDefs() {
        
    }
}
