#include "AutonomousCommand.h"

#include "AutoMoveForward.h"
#include "LaunchAngle.h"
#include "Fire.h"
#include "OpenClaw.h"
#include "StallCommand.h"
#include "VisionTargeting.h"

AutonomousCommand::AutonomousCommand() {
	StallCommand * stallCommand = new StallCommand();
	VisionTargeting *visionTargeting = new VisionTargeting(stallCommand);
	
	AddSequential(visionTargeting);		  // checks for a target detection using vision.
	AddSequential(new AutoMoveForward()); // this moves the robot forward and stops it after a set period of time 
	AddSequential(stallCommand);		  // this command stalls for a configurable amount of time (stall time set by vision);
	AddSequential(new LaunchAngle(true)); // this puts the arm in to shooting position
	AddParallel(new LaunchAngle(false));  // Keep the launch angle in place.
	AddSequential(new OpenClaw(true));    // this opens the claw to alow the ball to be launched
	AddSequential(new Fire());            // this releses the trigger and resets the shooter
}
	
