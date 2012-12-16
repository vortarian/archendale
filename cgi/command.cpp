
#include <exception/exception.h>
#include <cgi/command.h>

namespace archendale
{
	// CGICommand:
	//
	command::command()
	{
	} // CGICommand
 
	// CGICommand:
	//
	command::command(const command& in)
	{
	} // CGICommand

	// ~CGICommand:
	//
	command::~command()
	{
	} // ~CGICommand

	// newInstance:
	//
	command* command::newInstance()
	{
		NotImplementedException exp;
		throw exp;
	} // newInstance
	
} // namespace archendale
