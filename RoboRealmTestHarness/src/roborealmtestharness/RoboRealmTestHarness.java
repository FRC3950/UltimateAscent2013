/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package roborealmtestharness;

import java.util.Arrays;


/**
 *
 * @author Max
 */
public class RoboRealmTestHarness {
    public final String ROBO_REALM_SERVER_ADDRESS = "10.39.50.9";
    
    public final int NUM_BFR_COORDS = 8;
    public final int MAX_SAMPLES = 30;
    
    public final int RIGHTY_INDEX = 1;
    public final int RIGHTYY_INDEX = 7;
    public final int LEFTY_INDEX = 3;
    public final int LEFTYY_INDEX = 5;

    private RR_API roboRealm;
    private ImageDataProcessor imgDataProcessor;
    private int numSamples = 0;
    private double distanceSum = 0.0;
    
    public RoboRealmTestHarness()
    {
        roboRealm = new RR_API();
        
        // Need to handle if connect fails
        roboRealm.connect(ROBO_REALM_SERVER_ADDRESS);
        
        int imageHeight = getImageHeight();
        
        System.out.println("IMAGE_HEIGHT = " + imageHeight);

        imgDataProcessor = new ImageDataProcessor(imageHeight);
    }
    
    private int getImageHeight()
    {
       String response = roboRealm.getVariable("IMAGE_HEIGHT");
        
        return Integer.parseInt(response);
    }
    
    public double calcImageDistance()
    {
        double[] coords = getBfrCoords();
        
        if (coords != null)
        {
 //          System.out.println("Bfr coords = " + Arrays.toString(coords));
             
            int numBlobs = coords.length / NUM_BFR_COORDS;
            
            for (int indexOffset = 0, blobNum = 0; blobNum < numBlobs; ++blobNum, indexOffset += NUM_BFR_COORDS)
            {
                distanceSum += imgDataProcessor.calculateDistance(coords[indexOffset + RIGHTY_INDEX], coords[indexOffset + RIGHTYY_INDEX], coords[indexOffset + LEFTY_INDEX], coords[indexOffset + LEFTYY_INDEX]);
                ++numSamples;
            }
         }
        else
        {
            ++numSamples;
            
            System.out.println("Couldn't get BFR_COORDINATES!");
        }
     
        double distance = distanceSum / numSamples;
        
        if (numSamples > MAX_SAMPLES)
        {
            System.out.println("Resetting sample count.");
            numSamples = 1;
            distanceSum = distance;
        }
        else if ((distance == Double.POSITIVE_INFINITY) || (distance == Double.NEGATIVE_INFINITY))
        {
            distance = 0.0;
            numSamples = 0;
            distanceSum = 0;
        }
        
        return distance;
    }
    
    public double[] getBfrCoords()
    {
        final int EXPECTED_ELEMENTS = 8;
        
        double[] result = null;
        
        String response = roboRealm.getVariable("BFR_COORDINATES");
        
        if (response != null)
        {
            String[] strCoords = response.split(",");
            
            if ((strCoords != null) && (strCoords.length >= EXPECTED_ELEMENTS) && ((strCoords.length % EXPECTED_ELEMENTS) == 0))
            {
                result = convertStringsToDoubles(strCoords);
            }
        }
        
        return result;
   }
    
    public static double[] convertStringsToDoubles(String[] strCoords)
    {
        double[] coords = new double[strCoords.length];
        
        for (int index = 0; index < strCoords.length; ++index)
        {
            coords[index] = Double.parseDouble(strCoords[index]);
        }
        
        return coords;
    }
    
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        RoboRealmTestHarness harness = new RoboRealmTestHarness();
        
        while (true)
        {
            double distance = harness.calcImageDistance();
            
            
            System.out.println("Distance from Image " + distance);
        }
    }
}
