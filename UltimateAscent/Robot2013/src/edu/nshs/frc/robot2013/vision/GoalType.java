/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package edu.nshs.frc.robot2013.vision;

/**
 * The various goals the vision code can target.
 * @author rsaccone
 */
public class GoalType
{
    public static final int None = VisionNetworkTableDefs.NO_TARGET ;
    public static final int HighGoal = VisionNetworkTableDefs.HIGH_TARGET;
    public static final int MiddleGoal = VisionNetworkTableDefs.MIDDLE_TARGET;
    
    private GoalType() {
        
    }
}