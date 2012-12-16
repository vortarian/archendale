
#include <factory/factory.h>

namespace archendale
{
	map<string, void*> factory::m_classMap;
	map<string, void*> factory::m_functionMap;
	
	// Factory:
	//
	factory::factory()
	{
	} // Factory

	// Factory:
	//
	factory::factory(const factory& in)
	{
	} // Factory

	// ~Factory:
	//
	factory::~factory()
	{
	} // ~Factory

	// createInstance:
	//
	void* factory::getFunction(const string& functionName)
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
	void* factory::createInstance(const string& className)
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
	void factory::registerClass(string className, void* pFunc)
	{
		m_classMap[className] = pFunc;
	} // registerClass

	// registerFunction:
	//
	void factory::registerFunction(string functionName, void* pFunc)
	{
		m_functionMap[functionName] = pFunc;
	} // registerFunction

} // namespace archendale
