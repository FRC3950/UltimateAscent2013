#include "Autonomous_3SS_Command.h"
#include "ToggleLiftSolenoidCommand.h"
#include "CloseGripCommand.h"
#include "DropDownCommand.h"
#include "LiftUpCommand.h"
#include "OpenGripCommand.h"
#include "ToggleGripCommand.h"
#include "AutoDriveCommand.h"
#include "../ConfigKeys.h"
#include "../Config/ConfigInstanceMgr.h"

static const double Auto3SS_MoveRightDistance1_Default = 60;
static const double Auto3SS_MoveRightDistance2_Default = 60;
static const double Auto3SS_MoveForwardDistance1_Default = 60;
static const double Auto3SS_MoveForwardDistance2_Default = 60;
static const double Auto3SS_MoveLeftDistance1_Default = 60;

Autonomous_3SS_Command::Autonomous_3SS_Command()
{
	ConfigMgr *configMgr = ConfigInstanceMgr::getInstance();
	for (int i = 0; i < 2; i++){
		AddSequential(new CloseGripCommand());
		AddSequential(new LiftUpCommand());
		AddSequential(new AutoDriveCommand(DriveRight,configMgr->getDoubleVal(ConfigKeys::Auto3SS_MoveRightDistanceKey1, Auto3SS_MoveRightDistance1_Default)));
		AddSequential(new AutoDriveCommand(DriveForward,configMgr->getDoubleVal(ConfigKeys::Auto3SS_MoveForwardDistanceKey1, Auto3SS_MoveForwardDistance1_Default)));
		AddSequential(new AutoDriveCommand(DriveLeft,configMgr->getDoubleVal(ConfigKeys::Auto3SS_MoveLeftDistanceKey1, Auto3SS_MoveLeftDistance1_Default)));
		AddSequential(new AutoDriveCommand(DriveForward, configMgr->getDoubleVal(ConfigKeys::Auto3SS_MoveForwardDistanceKey2,Auto3SS_MoveForwardDistance2_Default)));
		AddSequential(new DropDownCommand());
		AddSequential(new OpenGripCommand());
	}
	AddSequential(new CloseGripCommand());
	AddSequential(new LiftUpCommand());
	AddSequential(new AutoDriveCommand(DriveRight,configMgr->getDoubleVal(ConfigKeys::Auto3SS_MoveRightDistanceKey2, Auto3SS_MoveRightDistance2_Default)));
	AddSequential(new DropDownCommand());
	AddSequential(new OpenGripCommand());


}
