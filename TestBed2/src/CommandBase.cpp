#include "CommandBase.h"
#include "Commands/Scheduler.h"

CommandBase::CommandBase(char const *name) :
		Command(name)
{
}

CommandBase::CommandBase() :
		Command()
{

}

/*
void CommandBase::init()
{
}
*/

