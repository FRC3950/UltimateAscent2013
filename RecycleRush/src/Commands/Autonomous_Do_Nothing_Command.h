#ifndef Autonomous_Do_Nothing_Command_H
#define Autonomous_Do_Nothing_Command_H

#include <WPILib.h>

class Autonomous_Do_Nothing_Command: public Command
{
public:
	Autonomous_Do_Nothing_Command();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
