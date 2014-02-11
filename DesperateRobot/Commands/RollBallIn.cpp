// RobotBuilder Version: 1.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.


#include "RollBallIn.h"


RollBallIn::RollBallIn() {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	Requires(Robot::intakeSubsystem);
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
}

// Called just before this Command runs the first time
void RollBallIn::Initialize() {
	
}

// Called repeatedly when this Command is scheduled to run
void RollBallIn::Execute() {
	Robot::intakeSubsystem->RollBallIn(1.0); // Roll ball out at sepcified speed
											 // positive should be in
}

// Make this return true when this Command no longer needs to run execute()
bool RollBallIn::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void RollBallIn::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RollBallIn::Interrupted() {

}
