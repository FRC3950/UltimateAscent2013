/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package roborealmtestharness;

import static java.lang.Math.*;

/**
 *
 * @author Max
 */
public class ImageDataProcessor {
    
     private static final double CAMERA_FIELD_OF_VIEW = 47.5; //35;
    
    private static final double HIGH_GOAL_TARGET_HEIGHT_IN_INCHES = 20.0;
    private static final double MIDDLE_GOAL_TARGET_HEIGHT_IN_INCHES = 29;
    
    private static final double MID_GOAL_HEIGHT_TO_GOAL_MIDPOINT_IN_INCHES = 99.125;
    private static final double HIGH_GOAL_HEIGHT_TO_GOAL_MIDPOINT_IN_INCHES = 110.125;
 
    private GoalType targetGoal;
    private double targetHeight;
    private double totalGoalHeight;
    
    private int imageHeight;
 
    public ImageDataProcessor(GoalType targetGoal, int imageHeight) {
        
        if (imageHeight <= 0) {
            throw new IllegalArgumentException("imageHeight must be greater than zero");
        }
        
        this.imageHeight = imageHeight;
        this.targetGoal = targetGoal;
        
        switch (targetGoal) {
            case HighGoal:
                targetHeight = HIGH_GOAL_TARGET_HEIGHT_IN_INCHES;
                totalGoalHeight = HIGH_GOAL_HEIGHT_TO_GOAL_MIDPOINT_IN_INCHES;
                break;
                
            case MiddleGoal:
                targetHeight = MIDDLE_GOAL_TARGET_HEIGHT_IN_INCHES;
                totalGoalHeight = MID_GOAL_HEIGHT_TO_GOAL_MIDPOINT_IN_INCHES;
                break;
                
            default:
                throw new IllegalArgumentException("targetGoal value is unexpected: " + targetGoal);
        }
     }
    
    
    // This part of the formula is the same every time, calculate it once.
    private static final double HALF_CAMERA_FOV_RADIANS = tan(((CAMERA_FIELD_OF_VIEW * PI) / 180.0) / 2.0);
    
    public double calculateDistance(double righty,
            double rightyy,
            double lefty,
            double leftyy) {
        
        //System.out.println("righty = " + righty + " rightyy = " + rightyy);
        //System.out.println("lefty = " + lefty + " leftyy = " + leftyy);
        
        // based on these two side lines get the center line height
        // the center line is used since we want to aim to the center
        // of the target. This also removes any perspective distortion
        // where the right or left size may be a couple inches closer
        // or further away from the camera
        double targetPixelHeight = ((lefty - leftyy) + (righty - rightyy)) / 2.0;
        
        // Determine the distance in inches.
        double totalDistance = (((targetHeight * imageHeight) / targetPixelHeight) / 2.0) / HALF_CAMERA_FOV_RADIANS;
        
        return totalDistance;
    }
    
    private static final double RADIANS_TO_DEGREES = 180.0 / PI;
    
    public double calculateAngleFromDistance(double measuredDistance)
    {
        double angle = Math.asin(totalGoalHeight / measuredDistance);
        
        angle *= RADIANS_TO_DEGREES;
        return angle;
    }
}