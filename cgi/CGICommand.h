
#ifndef CGICommand_H
#define CGICommand_H

#include <string>
#include <cgi/CGI.h>

using std::string;

namespace archendale
{
	class CGICommand
	{
	public:
		// CGICommand:
		//
		CGICommand();

		// CGICommand:
		//
		CGICommand(const CGICommand&);

		// ~CGICommand:
		//
		virtual ~CGICommand();
	
		// execute:
		//
		//
		virtual void execute(CGI&) = 0;
		
		// newInstance
		//	Returns a pointer to a new instance of this class
		CGICommand* newInstance();

	private:
	}; // CGICommand
} // namespace archendale

#endif // CGICommand_H
