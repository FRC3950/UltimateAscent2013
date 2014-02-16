#include "MoveArm.h"
#include "../Subsystems/ArmPIDSubsystem.h"

MoveArm::MoveArm() {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	Requires(Robot::armPIDSubsystem);
	
}

// Called just before this Command runs the first time
void MoveArm::Initialize() {
	
}

// Called repeatedly when this Command is scheduled to run
void MoveArm::Execute() {
	Robot::armPIDSubsystem->ManualMoveArmControl(-Robot::oi->GetArmSpeed());
}

// Make this return true when this Command no longer needs to run execute()
bool MoveArm::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void MoveArm::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void MoveArm::Interrupted() {
}
