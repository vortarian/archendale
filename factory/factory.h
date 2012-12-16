
#ifndef Factory_H
#define Factory_H

#include <map>

#include <factory/factory.h>
#include <factory/exception.h>

/*
	Factory interface to be used for automatic class registration, and dynamic building.
	A given class must inherit from Command (if it wishes to use the generic interface,
	otherwise, it can use a generic interface, and cast it's return value as necessary
	
	Required:
		The Factory must have the registerClass("name", functionPointer) called 
		to be used.  A convience template has been set up, which will register
		any class with a static factory member function called newInstance, which returns
		a pointer to the desired object.  To use, here is the format, with an example
		following:
			FactoryRegistrar<CLASS_TO_REGISTER> CommandTest::CFR("NAME_TO_USE_FOR_LOOKUP_OF_CLASS");
			CLASS_TO_REGISTER = (CLASS_TO_REGISTER*) Factory::getInstance("NAME_TO_USE_FOR_LOOKUP_OF_CLASS");
			... use class ...
	
	Example of use:
		#include <iostream>

		#include <factory/factory.h>

		using namespace archendale;
		using namespace std;

		class CommandTest 
		{
		public:
			void execute() 
			{ 
				cout << "Hello Factory" << endl; 
			} // execute 
			static Command* newInstance() { return new CommandTest; }
		private:
			static FactoryRegistrar<CommandTest> CFR;
		}; // CommandTest

		FactoryRegistrar<CommandTest> CommandTest::CFR("CommandTest");

		void main(void)
		{
			Command* cmd = (Command*) Factory::createInstance("CommandTest");
			cmd->execute(cgi);
			delete cmd;
		} // main
*/

using std::map;

namespace archendale
{
	class Factory
	{
	private:
		static map<string, void*> m_classMap;
		static map<string, void*> m_functionMap;

		// Factory:
		// Do not allow instatiation
		Factory();

		// Factory:
		// Do not allow instatiation
		Factory(const Factory&);

		// ~Factory:
		// Do not allow instatiation
		virtual ~Factory();

	public:
		// createInstance
		// 	Return the instance of a class by the given name
		//	Throw ClassNotFoundException if the class does not exist
		static void* createInstance(const string&);
		
		// getFunction
		// 	Return the instance of a class by the given name
		//	Throw FunctionNotFoundException if the class does not exist
		static void* getFunction(const string&);
		
		// registerClass
		//	Used to register a class to be created by the 
		//	Factory.  The class must pass a pointer to
		//	a cloning funciton Command, and a string to be used for 
		//	the key.  The Command pointer will be used to call the 
		//	the dispatch command for each object
		static void registerClass(string, void*);
		
		// registerFunction
		//	Used to register a function to be stored by the 
		//	Factory.  
		static void registerFunction(string, void*);
		
	}; // Factory
	
	template<class T> class FactoryRegistrar 
	{
	public:
		FactoryRegistrar(string className) 
		{ 
			void *pFunc = (void*) &T::newInstance;
			Factory::registerClass(className, pFunc ); 
		} // FactoryRegistrar
	}; // FactoryRegistrar

} // namespace archendale
#endif // Factory_H
