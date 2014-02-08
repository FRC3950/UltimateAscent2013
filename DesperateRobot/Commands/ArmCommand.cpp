#include "ArmCommand.h"

ArmCommand::ArmCommand() {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	Requires(Robot::armPIDSubsystem);
	
}

// Called just before this Command runs the first time
void ArmCommand::Initialize() {
	
}

// Called repeatedly when this Command is scheduled to run
void ArmCommand::Execute() {
	
	//Robot::armPIDSubsystem->MoveArm(Robot::oi->GetArmStickY());
	
	bool TopButtonPressed = Robot::oi->GetTopButton();
	bool ShootButtonPressed = Robot::oi->GetShootButton();
	bool BottomButtonPressed = Robot::oi->GetBottomButton();
	
	if (TopButtonPressed == true)
	{
		// INSERT CODE TO MOVE ARM TO TOP
	}
	
	
	
	if (ShootButtonPressed == true)
	{
		// INSERT CODE TO MOVE ARM TO SHOOTING POSITION
	}
	
	

	
	
	if (BottomButtonPressed == true)
	{
		// INSERT CODE TO MOVE ARM TO BOTTOM
	}
	
}

// Make this return true when this Command no longer needs to run execute()
bool ArmCommand::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void ArmCommand::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ArmCommand::Interrupted() {
}
