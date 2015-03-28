#include "Autonomous_1TSS_Command.h"
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

static const double Auto1TS_MoveLeftDistanceDefault = 150;
static const double Auto1TS_MoveForwardDistanceDefault = 30;

Autonomous_1TSS_Command::Autonomous_1TSS_Command()
{
	ConfigMgr *configMgr = ConfigInstanceMgr::getInstance();

	AddSequential(new CloseGripCommand());
	AddSequential(new StallCommand(0.5));
	AddSequential(new LiftUpCommand());
	AddSequential(new StallCommand(0.5));
	AddSequential(new AutoDriveCommand(DriveForward, configMgr->getDoubleVal(ConfigKeys::Auto1TS_MoveForwardDistance_Key, Auto1TS_MoveForwardDistanceDefault)));
	AddSequential(new StallCommand(0.5));
	AddSequential(new DropDownCommand());
	AddSequential(new StallCommand(0.5));
	AddSequential(new OpenGripCommand());
	AddSequential(new StallCommand(0.7));
	AddSequential(new CloseGripCommand());
	AddSequential(new StallCommand(0.5));
	AddSequential(new LiftUpCommand());
}
