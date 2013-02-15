/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package roborealmtestharness;

import java.lang.Math;

/**
 *
 * @author Max
 */
public class ImageDataProcessor {

    private final double CAMERA_FIELD_OF_VIEW = 47.5; //35;//47.5;
    private final double HIGH_GOAL_TARGET_HEIGHT = 20.0;    // inches
    private final double MIDDLE_GOAL_TARGET_HEIGHT = 29;    // inches
    private final double MID_GOAL_HEIGHT_TO_GOAL_MIDPOINT = 99.125;  // Inches.
    private final double HIGH_GOAL_HEIGHT_TO_GOAL_MIDPOINT = 110.125;  // Inches.
 
    private int imageHeight;
    private double targetHeight = HIGH_GOAL_TARGET_HEIGHT;
    private double lastTargetPixelHeight = 0.0;

    public ImageDataProcessor(int imageHeight) {
        this.imageHeight = imageHeight;
    }

    public double calculateDistance(double righty,
            double rightyy,
            double lefty,
            double leftyy) {
        
        //System.out.println("righty = " + righty + " rightyy = " + rightyy);
        //System.out.println("lefty = " + lefty + " leftyy = " + leftyy);
        
        double targetSamples = 0.0;
        
        // based on these two side lines get the center line height
        // the center line is used since we want to aim to the center
        // of the target. This also removes any perspective distortion
        // where the right or left size may be a couple inches closer
        // or further away from the camera
        lastTargetPixelHeight = ((lefty - leftyy) + (righty - rightyy)) / 2.0;
        
        // Determine the distance in inches.
        double totalDistance = (((targetHeight * imageHeight) / lastTargetPixelHeight) / 2.0) / Math.tan(((CAMERA_FIELD_OF_VIEW * Math.PI) / 180.0) / 2.0);
        
        return totalDistance;
    }
    
    public double calculateAngleFromDistance(double measuredDistance)
    {
        // ((((atan(((targetHeight * imageHeight) / targetPixelHeight) / 2)/ measuredDistance) * 2) * 180) / PI)
        
        double angle = Math.asin(HIGH_GOAL_HEIGHT_TO_GOAL_MIDPOINT / measuredDistance);
        
        angle *= 180.0 / Math.PI;
        return angle;
    }
}