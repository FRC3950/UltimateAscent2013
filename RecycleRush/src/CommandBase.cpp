#include "CommandBase.h"
#include "Commands/Scheduler.h"

// Initialize a single static instance of all of your subsystems to NULL
OI* CommandBase::oi = NULL;

CommandBase::CommandBase(char const *name) :
		Command(name)
{
}

CommandBase::CommandBase() :
		Command()
{

}

void CommandBase::init()
{
}
