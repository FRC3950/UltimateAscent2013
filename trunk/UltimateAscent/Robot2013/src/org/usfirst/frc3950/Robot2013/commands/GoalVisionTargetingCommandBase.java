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
    private double VISION_TARGETING_TIMEOUT_SECS = 5.0;

    private int goalType;
    private VisionTargetFinderClient vtfc;
    private double angle = 0.0;
    private double angleVoltage = 0.0;
    private double avgDistance = 0.0;
    private boolean publishedRequest = false;
    private boolean foundAngle = false;
    
    private void internalCtor(int goalType) {
       requires(Robot.shootingScrew);
       this.goalType = goalType;
       this.setTimeout(VISION_TARGETING_TIMEOUT_SECS);
    }
    
    private void resetState() {
        if (vtfc != null) {
            vtfc.cancel();
            vtfc = null;
        }
//        Robot.shootingScrew.setPIDSubsystem(false);
        
        angle = 0.0;
        angleVoltage = 0.0;
        avgDistance = 0.0;
        publishedRequest = false;
        foundAngle = false;
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
       resetState();
    }
   
   private void publishRequest() {
       System.out.println("GVTCB: Publishing goalType Request = " + goalType);
        vtfc = new VisionTargetFinderClient(goalType);
        publishedRequest = true;
   }

    // Called repeatedly when this Command is scheduled to run
    protected final void execute() {
        if (!publishedRequest) {
            publishRequest();
        }
        
        double angle = vtfc.getAngle();
        double distance = vtfc.getDistance();
        
        if (angle > 0.0) {
            this.angle = angle;
            this.avgDistance = distance;
            foundAngle = true;
            Robot.shootingScrew.setPIDSubsystem(true);
            angleVoltage = Robot.shootingScrew.setInclineAngle(angle, true);
        }
     }

    // Make this return true when this Command no longer needs to run execute()
    protected final boolean isFinished() {
        
        if (!foundAngle && this.isTimedOut()) {
            System.out.println("GTVCB: isFinished - No angle found and time out reached.  Returning true");
            return true;
        }
        
        // Have an angle that we're trying to target so monitor the PID
        // to see if it has been reached.
        if (foundAngle && Robot.shootingScrew.hasReachedTargetVoltage(angleVoltage)) {
            System.out.println("GVTCB: isFinished = true foundAngle = " + foundAngle + ", timedOut = " + this.isTimedOut());
            return true;
        }
        
        return false;
    }

    // Called once after isFinished returns true
    protected final void end() {
        System.out.println("GVTCB:end() called.");
        resetState();
    }

    public boolean isInterruptible() {
        return true;
    }
    
    // Called when another command which requires one or more of the same
    // subsystems is scheduled to run
    protected final void interrupted() {
        System.out.println("GVTCB:interrupted() called.");
        resetState();
    }
}
