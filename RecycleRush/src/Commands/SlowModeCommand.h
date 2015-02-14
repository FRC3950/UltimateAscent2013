#ifndef SlowModeCommand_H
#define SlowModeCommand_H

#include "Commands/Command.h"
#include "WPILib.h"



class SlowModeCommand: public Command
{
public:
	SlowModeCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

	bool IsEnabled() const { return m_slowModeEnabled; }
private:
	bool m_slowModeEnabled;
};

#endif
