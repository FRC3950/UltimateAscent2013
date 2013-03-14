/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package roborealmtestharness;

import edu.wpi.first.wpilibj.networktables.NetworkTable;

import java.util.Arrays;


/**
 *
 * @author Max
 */  
public class RoboRealmTestHarness {
    
    public static void tryNetworkTable() {
        NetworkTable.setClientMode();
        NetworkTable.setIPAddress("10.39.50.2");
        NetworkTable table = NetworkTable.getTable("SmartDashboard");
        
        while (true) {
            try {
                Thread.sleep(1000);
            
            }
            catch (InterruptedException ex) {
                // Eat the exception.
            }
            
            double imageCount = table.getNumber("IMAGE_COUNT", 0.0);
            
            System.out.println("TestHarness: IMAGE_COUNT = " + imageCount);
            
            Object bfrCoords = table.getValue("BFR_COORDINATES");
            
            System.out.println("Test Harness: BFR_COORDINATES " + bfrCoords);
            
            if (bfrCoords != null) {
               Object[] bfr = (Object[]) bfrCoords;
            
                for (int i = 0; i < bfr.length; ++i) {
                    Object o = bfr[i];

                    if (o instanceof Double) { 
                      Double d = (Double)o; 
                      System.out.println("Test Harness: BFR_COORDINATES " + d);
                    }   
                }
            }
         }
    }
    
    private static void runVisionSubsystem() {
        RoboRealmVisionTargetFinder targetFinder = new RoboRealmVisionTargetFinder(GoalType.HighGoal, null);
        
        targetFinder.start();
        
        while (true)
        {
            double avgDistance = targetFinder.getAvgDistance();
            
            System.out.println("Distance from Image " + avgDistance);

            double targetAngle = targetFinder.getTargetAngle();
            
            System.out.println("Target angle is " + targetAngle + " degrees");
            
            System.out.println("Vision finder state is: " + targetFinder.getState());
        }
    }
    
    private static void runRobotServer() {
        RobotVisionServer robotVisionServer = new RobotVisionServer("10.39.50.2");
        
        while (true)
        {
            try {
                Thread.sleep(60000);
            }
            catch (InterruptedException ex) {
                
            }
        }
    }
     /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
         if (args.length != 0) {
            runVisionSubsystem();
        }
         else {
             runRobotServer();
         } 
    }
}
