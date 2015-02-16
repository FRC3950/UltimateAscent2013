#ifndef Autonomous_1CS2_Command_H
#define Autonomous_1CS2_Command_H

#include "Commands/CommandGroup.h"
#include "WPILib.h"

class ConfigMgr;

class Autonomous_1CS2_Command: public CommandGroup
{
public:
	Autonomous_1CS2_Command();

private:
	void AddPickUpAndMoveContanerSequence(ConfigMgr *configMgr);
};

#endif
