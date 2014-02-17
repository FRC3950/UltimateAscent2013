#include "AutonomousCommand.h"

AutonomousCommand::AutonomousCommand() {
	AddSequential(new AutoMoveForward());
	AddSequential(new LaunchAngle());
	AddSequential(new OpenClaw(true));
	AddSequential(new Fire());
}
	
