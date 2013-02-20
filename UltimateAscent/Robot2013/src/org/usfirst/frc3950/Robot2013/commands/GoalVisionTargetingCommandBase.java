/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package org.usfirst.frc3950.Robot2013.commands;

import edu.nshs.frc.robot2013.vision.VisionTargetFinderClient;
import edu.wpi.first.wpilibj.command.*;
import org.usfirst.frc3950.Robot2013.Robot;

/**
 *
 * @author rsaccone
 */
public class GoalVisionTargetingCommandBase extends Command {
    private double VISION_TARGETING_TIMEOUT_SECS = 60.0;

    private int goalType;
    private VisionTargetFinderClient vtfc;
    private double angle = 0.0;
    private double avgDistance = 0.0;
    private boolean foundAngle = false;
    
    private void internalCtor(int goalType) {
       requires(Robot.shootingScrew);
       this.goalType = goalType;
       this.setTimeout(VISION_TARGETING_TIMEOUT_SECS);
    }
    
    public GoalVisionTargetingCommandBase(String name, int goalType) {
        super(name); 
        internalCtor(goalType);
    }
            
    public GoalVisionTargetingCommandBase(int goalType) {
        super();
        internalCtor(goalType);
    }
    
   protected final void initialize() {
       System.out.println("GVTCB: Publishing goalType Request = " + goalType);
        vtfc = new VisionTargetFinderClient(goalType);
    }

    // Called repeatedly when this Command is scheduled to run
    protected final void execute() {
        double angle = vtfc.getAngle();
        double distance = vtfc.getDistance();
        
        if (angle > 0.0) {
            this.angle = angle;
            this.avgDistance = distance;
            foundAngle = true;
            Robot.shootingScrew.setInclineAngle(angle);
        }
     }

    // Make this return true when this Command no longer needs to run execute()
    protected final boolean isFinished() {
        boolean result = foundAngle || this.isTimedOut();
        
        System.out.println("GVTCB: isFinished = " + result +" foundAngle = " + foundAngle + ", timedOut = " + this.isTimedOut());
        
        return result;
    }

    // Called once after isFinished returns true
    protected final void end() {
        vtfc.cancel();
    }

    // Called when another command which requires one or more of the same
    // subsystems is scheduled to run
    protected final void interrupted() {
    }
    
    public final boolean isInterruptible() {
        return false;
    }
}
