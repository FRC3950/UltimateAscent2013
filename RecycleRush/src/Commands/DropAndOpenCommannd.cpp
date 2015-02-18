#include "DropAndOpenCommannd.h"
#include "DropDownCommand.h"
#include "OpenGripCommand.h"
#include "StallCommand.h"

DropAndOpenCommannd::DropAndOpenCommannd()
{
	AddSequential(new DropDownCommand());
	AddSequential(new StallCommand(0.2));
	AddSequential(new OpenGripCommand());
}
