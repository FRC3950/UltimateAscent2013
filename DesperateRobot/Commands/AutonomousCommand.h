#ifndef AUTONOMOUS_COMMAND_H
#define AUTONOMOUS_COMMAND_H

#include "Commands/CommandGroup.h"
#include "AutoMoveForward.h"
#include "LaunchAngle.h"
#include "Fire.h"
#include "OpenClaw.h"




/**
 *
 *
 * @author ExampleAuthor
 */
class AutonomousCommand: public CommandGroup {
public:	
	AutonomousCommand();
};

#endif
