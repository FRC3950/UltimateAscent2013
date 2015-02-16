#include "Autonomous_1TS_Command.h"
#include "ToggleLiftSolenoidCommand.h"
#include "CloseGripCommand.h"
#include "DropDownCommand.h"
#include "LiftUpCommand.h"
#include "OpenGripCommand.h"
#include "ToggleGripCommand.h"
#include "AutoDriveCommand.h"
#include "../ConfigKeys.h"
#include "../Config/ConfigInstanceMgr.h"

static const double Auto1TS_MoveLeftDistanceDefault = 60;
static const double Auto1TS_MoveForwardDistanceDefault = 60;

Autonomous_1TS_Command::Autonomous_1TS_Command()
{
	ConfigMgr *configMgr = ConfigInstanceMgr::getInstance();

	AddSequential(new CloseGripCommand());
	AddSequential(new LiftUpCommand());
	AddSequential(new AutoDriveCommand(DriveForward, configMgr->getDoubleVal(ConfigKeys::Auto1TS_MoveForwardDistance_Key, Auto1TS_MoveForwardDistanceDefault)));
	AddSequential(new DropDownCommand());
	AddSequential(new OpenGripCommand());
	AddSequential(new CloseGripCommand());
	AddSequential(new LiftUpCommand());
	AddSequential(new AutoDriveCommand(DriveLeft, configMgr->getDoubleVal(ConfigKeys::Auto1TS_MoveLeftDistance_Key, Auto1TS_MoveLeftDistanceDefault)));
}
