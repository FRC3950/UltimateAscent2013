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

    private final double CAMERA_FIELD_OF_VIEW = 47.5;
    private final double TARGET_HEIGHT = 12.0;
    private int imageHeight;

    public ImageDataProcessor(int imageHeight) {
        this.imageHeight = imageHeight;
    }

    public double calculateDistance(double righty,
            double rightyy,
            double lefty,
            double leftyy) {
        
        System.out.println("righty = " + righty + " rightyy = " + rightyy);
        System.out.println("lefty = " + lefty + " leftyy = " + leftyy);
        
        double targetSamples = 0.0;
        
        // based on these two side lines get the center line height
        // the center line is used since we want to aim to the center
        // of the target. This also removes any perspective distortion
        // where the right or left size may be a couple inches closer
        // or further away from the camera
        double targetPixelHeight = ((lefty - leftyy) + (righty - rightyy)) / 2.0;
        
        // Determine the distance in inches.
        double totalDistance = (((TARGET_HEIGHT * imageHeight) / targetPixelHeight) / 2.0) / Math.tan(((CAMERA_FIELD_OF_VIEW * Math.PI) / 180.0) / 2.0);
        
        return totalDistance;
    }
}