#include "Autonomous_3SS_Command.h"
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

static const double Auto3SS_MoveRightDistance1_Default = 150;
//static const double Auto3SS_MoveRightDistance2_Default = 60;
static const double Auto3SS_MoveForwardDistance1_Default = 85;
static const double Auto3SS_MoveForwardDistance2_Default = 82;
//static const double Auto3SS_MoveLeftDistance1_Default = 60;

Autonomous_3SS_Command::Autonomous_3SS_Command()
{
	ConfigMgr *configMgr = ConfigInstanceMgr::getInstance();
	AddSequential(new CloseGripCommand());
	AddSequential(new StallCommand(0.6));
	AddSequential(new LiftUpCommand());
	AddSequential(new StallCommand(0.5));//change this one to account for another robot
	AddSequential(new AutoDriveCommand(DriveForward, configMgr->getDoubleVal(ConfigKeys::Auto3SS_MoveForwardDistanceKey1, Auto3SS_MoveForwardDistance1_Default)));
	AddSequential(new StallCommand(0.5));
	AddSequential(new DropDownCommand());
	AddSequential(new StallCommand(0.3));
	AddSequential(new OpenGripCommand());
	AddSequential(new StallCommand(0.5));
	AddSequential(new CloseGripCommand());
	AddSequential(new StallCommand(0.6));
	AddSequential(new LiftUpCommand());
	AddSequential(new StallCommand(0.5));
	AddSequential(new AutoDriveCommand(DriveForward, configMgr->getDoubleVal(ConfigKeys::Auto3SS_MoveForwardDistanceKey2, Auto3SS_MoveForwardDistance2_Default)));
	AddSequential(new StallCommand(0.5));
	AddSequential(new DropDownCommand());
	AddSequential(new StallCommand(0.3));
	AddSequential(new OpenGripCommand());
	AddSequential(new StallCommand(0.7));
	AddSequential(new CloseGripCommand());
	AddSequential(new StallCommand(0.6));
	AddSequential(new LiftUpCommand());
	AddSequential(new StallCommand(0.5));
	AddSequential(new AutoDriveCommand(DriveRight, configMgr->getDoubleVal(ConfigKeys::Auto3SS_MoveRightDistanceKey1, Auto3SS_MoveRightDistance1_Default)));
	AddSequential(new StallCommand(0.5));
	AddSequential(new DropDownCommand());
	AddSequential(new StallCommand(0.5));
	AddSequential(new OpenGripCommand());
	AddSequential(new StallCommand(0.5));
	AddSequential(new AutoDriveCommand(DriveBack,24));



}
