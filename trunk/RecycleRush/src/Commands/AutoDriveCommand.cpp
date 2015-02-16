#include "AutoDriveCommand.h"
#include "../Subsystems/DriveSubsystem.h"
#include "../Robot.h"
#include "Logging.h"


AutoDriveCommand::AutoDriveCommand(DriveHeading heading, float distanceInInches, float speedScaleFactor)
	: driveHeading(heading),
	  distanceToDriveInInches(distanceInInches),
	  motorSpeedScaleFactor(speedScaleFactor),
	  autoDriveIsSetup(false)
{
	// Use Requires() here to declare subsystem dependencies
	Requires(Robot::driveSubsystem);

	SetInterruptible(true);
}

// Called just before this Command runs the first time
void AutoDriveCommand::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void AutoDriveCommand::Execute()
{
	if (IsCanceled())
	{
		return;
	}

	if (!autoDriveIsSetup)
	{
		autoDriveIsSetup = Robot::driveSubsystem->AutoDriveSetup(driveHeading, distanceToDriveInInches, motorSpeedScaleFactor);

		if (!autoDriveIsSetup)
		{
			Logger::GetInstance()->Log(DriveSubsystemLogId, Logger::kERROR,"AutoDriveCommand: AutoDriveSetup failed.  Canceling Command.\n");

			Cancel();

			return;
		}
	}

	if (autoDriveIsSetup)
	{
		Robot::driveSubsystem->AutoDriveExecute();
	}
}

// Make this return true when this Command no longer needs to run execute()
bool AutoDriveCommand::IsFinished()
{
	if (IsCanceled() || !autoDriveIsSetup)
	{
		return true;
	}

	return Robot::driveSubsystem->AutoDriveHasReachedLocation();
}

// Called once after isFinished returns true
void AutoDriveCommand::End()
{
	Robot::driveSubsystem->AutoModeDisable();
	autoDriveIsSetup = false;
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutoDriveCommand::Interrupted()
{
	Robot::driveSubsystem->AutoModeDisable();
	autoDriveIsSetup = false;
}
