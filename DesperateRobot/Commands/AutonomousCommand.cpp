#include "AutonomousCommand.h"

AutonomousCommand::AutonomousCommand() {
	AddSequential(new AutoMoveForward()); // this moves the robot forward and stops it after a set period of time 
	AddSequential(new LaunchAngle());     // this puts the arm in to shooting position
	AddSequential(new OpenClaw(true));    // this opens the claw to alow the ball to be launched
	AddSequential(new Fire());            // this releses the trigger and resets the shooter
}
	
