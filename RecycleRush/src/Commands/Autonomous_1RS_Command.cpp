#include "Autonomous_1RS_Command.h"
#include "ToggleLiftSolenoidCommand.h"
#include "CloseGripCommand.h"
#include "DropDownCommand.h"
#include "LiftUpCommand.h"
#include "OpenGripCommand.h"
#include "ToggleGripCommand.h"
#include "AutoDriveCommand.h"
#include "StallCommand.h"
#include "../ConfigKeys.h"
#include "../Config/ConfigInstanceMgr.h"

static const double Auto1RS_MoveLeftDistanceDefault = 60;

Autonomous_1RS_Command::Autonomous_1RS_Command()
{
	ConfigMgr *configMgr = ConfigInstanceMgr::getInstance();

	AddSequential(new CloseGripCommand());
	AddSequential(new StallCommand(0.1));
	AddSequential(new LiftUpCommand());
	AddSequential(new StallCommand(0.5));
	AddSequential(new AutoDriveCommand(DriveLeft, configMgr->getDoubleVal(ConfigKeys::Auto1RS_MoveLeftDistance_Key, Auto1RS_MoveLeftDistanceDefault)));
	AddSequential(new StallCommand(0.5));
	AddSequential(new DropDownCommand());
	AddSequential(new StallCommand(0.5));
	AddSequential(new OpenGripCommand());
}
