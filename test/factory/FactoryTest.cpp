#include <iostream>
#include <string>

#include <factory/factory.h>

using namespace archendale;
using namespace std;

class CommandTest 
{
public:
	void execute() 
	{ 
		cout << "Hello Factory Test Succeeded" << endl; 
	} // execute 
	static CommandTest* newInstance() { return new CommandTest; }
private:
	static FactoryRegistrar<CommandTest> CFR;
}; // CommandTest

FactoryRegistrar<CommandTest> CommandTest::CFR("CommandTest");

void functor(void)
{
	cout << "Functor Test Succeeded" << endl;
} // functor

int main(void)
{
	factory::registerFunction(string("functor"), (void*) functor);

	void (*func)(void) = (void (*)(void)) factory::getFunction("functor");
	func();

	CommandTest* cmd = (CommandTest*) factory::createInstance("CommandTest");
	cmd = (CommandTest*) factory::createInstance("CommandTest");
	cmd->execute();
	delete cmd;

	// Now test that the exception gets thrown
	try
	{
		cmd = (CommandTest*) factory::createInstance("BogusClass");
		cout << "No Exception caught, test FAILED" << endl;
	} catch (ClassNotFoundException exp)
	{
		cout << "Exception caught, test succeeded" << endl;
	} // try
	return 0;
} // main
