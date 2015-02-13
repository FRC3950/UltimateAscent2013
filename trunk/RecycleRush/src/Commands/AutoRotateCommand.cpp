#include "AutoRotateCommand.h"
#include "../Subsystems/DriveSubsystem.h"
#include "../Robot.h"


AutoRotateCommand::AutoRotateCommand(float angle, RotateDirection direction)
{
	// Use Requires() here to declare subsystem dependencies
	Requires(Robot::driveSubsystem);

	this->angle = angle;
	this->direction = direction;

	Robot::driveSubsystem->AutoRotateSetup(this->angle, this->direction);

}

// Called just before this Command runs the first time
void AutoRotateCommand::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void AutoRotateCommand::Execute()
{
	Robot::driveSubsystem->AutoRotateExecute();
}

// Make this return true when this Command no longer needs to run execute()
bool AutoRotateCommand::IsFinished()
{
	return Robot::driveSubsystem->AutoHasFinishedRotating();
}

// Called once after isFinished returns true
void AutoRotateCommand::End()
{
	Robot::driveSubsystem->AutoModeDisable();//i'm not sure about this, should I be disabling here?
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutoRotateCommand::Interrupted()
{
	Robot::driveSubsystem->AutoModeDisable();//i'm not sure about this, should I be disabling here?
}
