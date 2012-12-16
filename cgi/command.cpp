
#include <exception/exception.h>
#include <cgi/command.h>

namespace archendale
{
	// CGICommand:
	//
	CGICommand::CGICommand()
	{
	} // CGICommand
 
	// CGICommand:
	//
	CGICommand::CGICommand(const CGICommand& in)
	{
	} // CGICommand

	// ~CGICommand:
	//
	CGICommand::~CGICommand()
	{
	} // ~CGICommand

	// newInstance:
	//
	CGICommand* CGICommand::newInstance()
	{
		NotImplementedException exp;
		throw exp;
	} // newInstance
	
} // namespace archendale
