#include "VisionTargeting.h"
#include "StallCommand.h"

#include "NetworkTables/NetworkTable.h"
#include "../Logger.h"
#include "../LoggingComponentDefs.h"

static const double TargetActiveDelayAferAutoMoveInSecs = 0.0;
static const double TargetNotActiveDelayAfterAutoMoveInSecs  = 3.0;
		
static const char *NetworkTableName = "SmartDashboard";
static const char *TargetDetectedVarName = "DETECTED";

static const double CheckTargetTimeOutInSecs = 1.0;

VisionTargeting::VisionTargeting(StallCommand *stallCommand) 
	: stallCommand_(stallCommand),
	  targetActive_(false)
{
	networkTable_ = NetworkTable::GetTable(NetworkTableName);
	
	if (networkTable_ == NULL)
	{
		Logger::GetInstance()->Log(VisionTargetingId, Logger::kWARNING, "VisionTargeting::ctor(): *** Couldn't get NetworkTable. ***");
	}
}

// Called just before this Command runs the first time
void VisionTargeting::Initialize() {
	SetTimeout(CheckTargetTimeOutInSecs);
}


// Called repeatedly when this Command is scheduled to run
void VisionTargeting::Execute() {
	if (networkTable_ != NULL)
	{
		targetActive_ = networkTable_->GetBoolean(TargetDetectedVarName, false);
		Logger::GetInstance()->Log(VisionTargetingId, Logger::kINFO, "VisionTargeting: DETECTED = %s", targetActive_ ? "TRUE" : "FALSE");
	}
	else
	{
		targetActive_ = false;
	}
}

// Make this return true when this Command no longer needs to run execute()
bool VisionTargeting::IsFinished() {
	bool finished = false;
	double stallTimeInSecs = 0;
	
	if (targetActive_)
	{
		stallTimeInSecs = TargetActiveDelayAferAutoMoveInSecs;
		finished = true;
	}
	else if (IsTimedOut())
	{
		stallTimeInSecs = TargetNotActiveDelayAfterAutoMoveInSecs;
		finished = true;
	}
	
	if (finished)
	{
		if (stallCommand_ != NULL)
		{
			Logger::GetInstance()->Log(VisionTargetingId, 
									   Logger::kINFO, 
									   "VisionTargeting: Setting time to stall after driving forward = %g secs.", 
									   stallTimeInSecs);
			
			stallCommand_->SetStallTime(stallTimeInSecs);
		}
		else
		{
			Logger::GetInstance()->Log(VisionTargetingId, 
									   Logger::kERROR, 
									   "VisionTargeting: No StallCommand instance to set stall time of %g secs on", 
									   stallTimeInSecs);
		}
	}
	
	return finished;
}

// Called once after isFinished returns true
void VisionTargeting::End() {
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void VisionTargeting::Interrupted() {
}
