#include "Autonomous_1CS2_Command.h"

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

static const double Auto1CS2_MoveLeftDistance_Default = 60;
static const double Auto1CS2_MoveBackDistance_Default = 60;
static const double Auto1CS2_MoveRightDistance1_Default = 60;
static const double Auto1CS2_MoveForwardDistance_Default = 60;
static const double Auto1CS2_MoveRightDistance2_Default = 60;

Autonomous_1CS2_Command::Autonomous_1CS2_Command()
{
	ConfigMgr *configMgr = ConfigInstanceMgr::getInstance();
	AddPickUpAndMoveContanerSequence(configMgr);
	AddSequential(new StallCommand(0.5));
	AddSequential(new AutoDriveCommand(DriveBack, configMgr->getDoubleVal(ConfigKeys::Auto1CS2_MoveBackDistanceKey, Auto1CS2_MoveBackDistance_Default)));
	AddSequential(new StallCommand(0.5));
	AddSequential(new AutoDriveCommand(DriveRight, configMgr->getDoubleVal(ConfigKeys::Auto1CS2_MoveRightDistanceKey1, Auto1CS2_MoveRightDistance1_Default)));
	AddSequential(new StallCommand(0.5));
	AddSequential(new AutoDriveCommand(DriveForward, configMgr->getDoubleVal(ConfigKeys::Auto1CS2_MoveForwardDistanceKey, Auto1CS2_MoveForwardDistance_Default)));
	AddSequential(new StallCommand(0.5));
	AddSequential(new AutoDriveCommand(DriveRight, configMgr->getDoubleVal(ConfigKeys::Auto1CS2_MoveRightDistanceKey2, Auto1CS2_MoveRightDistance2_Default)));
	AddSequential(new StallCommand(0.5));
	AddPickUpAndMoveContanerSequence(configMgr);
}
void Autonomous_1CS2_Command::AddPickUpAndMoveContanerSequence(ConfigMgr *configMgr) {
	AddSequential(new CloseGripCommand());
	AddSequential(new StallCommand(0.5));
	AddSequential(new LiftUpCommand());
	AddSequential(new StallCommand(0.5));
	AddSequential(new AutoDriveCommand(DriveLeft, configMgr->getDoubleVal(ConfigKeys::Auto1CS2_MoveLeftDistanceKey, Auto1CS2_MoveLeftDistance_Default)));
	AddSequential(new StallCommand(0.5));
	AddSequential(new DropDownCommand());
	AddSequential(new StallCommand(0.5));
	AddSequential(new OpenGripCommand());
}
