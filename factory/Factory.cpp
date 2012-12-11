
#include <factory/Factory.h>

namespace archendale
{
	map<string, void*> Factory::m_classMap;
	map<string, void*> Factory::m_functionMap;
	
	// Factory:
	//
	Factory::Factory()
	{
	} // Factory

	// Factory:
	//
	Factory::Factory(const Factory& in)
	{
	} // Factory

	// ~Factory:
	//
	Factory::~Factory()
	{
	} // ~Factory

	// createInstance:
	//
	void* Factory::getFunction(const string& functionName)
	{
		void* pFunc = 0;
		pFunc = m_functionMap[functionName];
		if(0 == pFunc) 
		{
			FunctionNotFoundException exp(functionName);
			throw exp;
		} // if	
		return pFunc;
	} // getFunction

	// createInstance:
	//
	void* Factory::createInstance(const string& className)
	{
		void* (*pFunc)(void) = 0;
		pFunc = (void* (*)(void)) m_classMap[className];
		if(0 == pFunc) 
		{
			ClassNotFoundException exp(className);
			throw exp;
		} // if	
		return pFunc();
	} // createInstance

	// registerClass:
	//
	void Factory::registerClass(string className, void* pFunc)
	{
		m_classMap[className] = pFunc;
	} // registerClass

	// registerFunction:
	//
	void Factory::registerFunction(string functionName, void* pFunc)
	{
		m_functionMap[functionName] = pFunc;
	} // registerFunction

} // namespace archendale
