
#include <iostream>
#include <Exception/Exception.h>

using archendale::Exception;

void throwException(void)
{
	Exception exp("plain Exception");	
	throw exp;
} // throwException

void throwNestedException() 
{
	try
	{
		throwException();
	} catch (Exception exp) 
	{
		Exception nexp("nested exception");
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
		cout << "Caught Exception from throwException - why: " << exp.why() << endl;
		if(exp.hasNested()) cout << "It has a nested exception (BAD)" << endl;
		else cout << "It does not have a nested exception (GOOD)" << endl;
	} // try

	try
	{
		throwNestedException();
	} catch (Exception nexp)
	{
		cout << "Caught Exception from throwException - why: " << nexp.why() << endl;
		if(nexp.hasNested()) cout << "It has a nested exception (GOOD)" << endl;
		else cout << "It does not have a nested exception (BAD)" << endl;
		cout << "Nested Exception says - why: " << nexp.getNestedException().why() << endl;
	} // try
} // testExceptions

void main(void)
{
	cout << "----------Output should be:------------\n" 
		<< "Caught Exception from throwException - why: plain Exception" << endl
		<< "It does not have a nested exception (GOOD)" << endl
		<< "Caught Exception from throwException - why: nested exception" << endl
		<< "It has a nested exception (GOOD)" << endl
		<< "Nested Exception says - why: plain Exception" << endl;
	cout << "--------------Running Test--------------" << endl;
	testExceptions();
} // main
