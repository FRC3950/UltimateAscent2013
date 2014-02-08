#include "LaunchAngle.h"
#include "../Subsystems/ArmPIDSubsystem.h"

LaunchAngle::LaunchAngle()
	: angleVoltage(0.0)
{
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	Requires(Robot::armPIDSubsystem);
	
}

// Called just before this Command runs the first time
void LaunchAngle::Initialize() {
	
}

// Called repeatedly when this Command is scheduled to run
void LaunchAngle::Execute() {
	Robot::armPIDSubsystem->SetPIDSubsystem(true);
	angleVoltage = Robot::armPIDSubsystem->SetArmAngle(LAUNCHING_ANGLE, false);
}

// Make this return true when this Command no longer needs to run execute()
bool LaunchAngle::IsFinished() {
	if (Robot::armPIDSubsystem->HasReachedTargetVoltage(angleVoltage))
	{
		return true;
	}
	return false;
}

// Called once after isFinished returns true
void LaunchAngle::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LaunchAngle::Interrupted() {
}
