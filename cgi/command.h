
#ifndef CGICommand_H
#define CGICommand_H

#include <string>
#include <cgi/cgi.h>

using std::string;

namespace archendale
{
	class command
	{
	public:
		// CGICommand:
		//
		command();

		// CGICommand:
		//
		command(const command&);

		// ~CGICommand:
		//
		virtual ~command();
	
		// execute:
		//
		//
		virtual void execute(cgi&) = 0;
		
		// newInstance
		//	Returns a pointer to a new instance of this class
		command* newInstance();

	private:
	}; // CGICommand
} // namespace archendale

#endif // CGICommand_H
