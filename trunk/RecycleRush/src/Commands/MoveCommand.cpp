#include "MoveCommand.h"
#include "../Robot.h"

MoveCommand::MoveCommand(DriveHeading heading, float distanceInInches)
	: m_heading(heading),
	  m_distanceInInches(distanceInInches),
	  m_startedMoving(false),
	  m_setup(false)
{
	Requires(Robot::driveSubsystem);
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	SetInterruptible(true);
}

// Called just before this Command runs the first time
void MoveCommand::Initialize()
{
	m_setup = Robot::driveSubsystem->AutoModeSetup(m_heading, m_distanceInInches);
}

// Called repeatedly when this Command is scheduled to run
void MoveCommand::Execute()
{
	if (m_setup && !m_startedMoving) {
		Robot::driveSubsystem->AutoMoveExecute();
		m_startedMoving = true;
	}
}

// Make this return true when this Command no longer needs to run execute()
bool MoveCommand::IsFinished()
{
	if (!m_setup) {
		return true;
	}


	bool isfinished = Robot::driveSubsystem->AutoAreWeThereYet();
	return isfinished;
}

// Called once after isFinished returns true
void MoveCommand::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void MoveCommand::Interrupted()
{
	Robot::driveSubsystem->AutoModeDisable();
}
