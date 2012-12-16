
#include <iostream>
#include <exception/exception.h>

using archendale::Exception;

void throwException(void)
{
	Exception exp("plain Exception : " __FILE__);	
	throw exp;
} // throwException

void throwNestedException() 
{
	try
	{
		throwException();
	} catch (Exception exp) 
	{
		Exception nexp("nested exception : " __FILE__);
		nexp.setNestedException(exp);	
		throw nexp;
	} // try
} // throwNestedException

void testExceptions(void)
{
	try
	{
		throwException();
	} catch (Exception exp)
	{
		std::cout << "Caught Exception from throwException - why: " << exp.why() << std::endl;
		if(exp.hasNested()) std::cout << "It has a nested exception (BAD)" << std::endl;
		else std::cout << "It does not have a nested exception (GOOD)" << std::endl;
	} // try

	try
	{
		throwNestedException();
	} catch (Exception nexp)
	{
		std::cout << "Caught Exception from throwException - why: " << nexp.why() << std::endl;
		if(nexp.hasNested()) std::cout << "It has a nested exception (GOOD)" << std::endl;
		else std::cout << "It does not have a nested exception (BAD)" << std::endl;
		std::cout << "Nested Exception says - why: " << nexp.getNestedException().why() << std::endl;
	} // try
} // testExceptions

int main(void)
{
	std::cout << "----------Output should be:------------\n" 
		<< "Caught Exception from throwException - why: plain Exception" << std::endl
		<< "It does not have a nested exception (GOOD)" << std::endl
		<< "Caught Exception from throwException - why: nested exception" << std::endl
		<< "It has a nested exception (GOOD)" << std::endl
		<< "Nested Exception says - why: plain Exception" << std::endl;
	std::cout << "--------------Running Test--------------" << std::endl;
	testExceptions();
	return 0;
} // main
