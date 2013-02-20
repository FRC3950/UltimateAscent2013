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

    /*************************************************************************** 
     * To be removed once we prove arrays can be passed.

    public static final String TARGET_TYPE_REQUEST_ID = "TARGET_TYPE_REQUEST_ID";
    public static final String TARGET_TYPE_REQUEST = "TARGET_TYPE_REQUEST";
    public static final String TARGET_TYPE_RESULT_ID = "TARGET_TYPE_RESULT_ID";
    public static final String TARGET_TYPE_RESULT = "TARGET_TYPE_RESULT";
    public static final String TARGET_AVG_DISTANCE_RESULT = "TARGET_AVG_DISTANCE_RESULT";
    public static final String TARGET_ANGLE_RESULT = "TARGET_ANGLE_RESULT";
    ***************************************************************************/ 
   
    // This key will hold an array of values that consist of the targeting request.
    public static final String TARGETING_REQUEST = "TARGETING_REQUEST";

    // These are the indexes into the NumberArray that is passed over in
    // the NetworkTable when a TARGETTING_REQUEST is made.
    public static final int TARGETING_REQUEST_ID_INDEX = 0;
    public static final int TARGETING_REQUEST_GOAL_TYPE_INDEX = 1;
    public static final int TARGETING_REQUEST_ARRAY_SIZE = 2;


    // This key will hold an array of values that consist of the targetting result.
    public static final String TARGETING_RESULT = "TARGETING_RESULT";

    // These are the indexes into the NumberArray that is passed over in
    // the NetworkTable when a targeting result is published/
    public static final int TARGETING_RESULT_ID_INDEX = 0;
    public static final int TARGETING_RESULT_GOAL_TYPE_INDEX = 1;
    public static final int TARGETING_RESULT_ANGLE_INDEX = 2;
    public static final int TARGETING_RESULT_AVG_DISTANCE = 3;
    public static final int TARGETING_RESULT_ARRAY_SIZE = 4;

    // Target types   
    public static final int NO_TARGET     = 0;
    public static final int HIGH_TARGET   = 1;
    public static final int MIDDLE_TARGET = 2;

    // Don't allow any instances of the class to be constructed.
    private VisionNetworkTableDefs() {
        
    }
}
