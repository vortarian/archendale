#include <util/SequenceGenerator.h>
#include <io/OTDF.h>
#include <io/ITDF.h>
#include <exception/Exception.h>

#include <iostream>
#include <fstream>

using namespace archendale;
using namespace std;

const string seqOne = "SequenceOne";
const string seqTwo = "SequenceTwo";

bool testSequence(void)
{
	int oneCounter, twoCounter;
	oneCounter = twoCounter = 0;
	{
		SequenceGenerator seqGen;
		seqGen.addSequence(seqOne);
		seqGen.addSequence(seqTwo);

		for(oneCounter = 0; oneCounter < 50; oneCounter++)
		{
			if(oneCounter  != seqGen.getNext(seqOne))
			{
				cerr << "(oneCounter != seqGen.getNext(seqOne))" << endl;
				return false;
			} // if
		} // for

		for(twoCounter = 0; twoCounter < 50; twoCounter++)
		{
			if(twoCounter != seqGen.getNext(seqTwo))
			{
				cerr << "(twoCounter != seqGen.getNext(seqTwo))" << endl;
				return false;
			} // if
		} // for

		ofstream ostr("seqGenSaveFile.txt", ios::trunc);
		OTDF otdf(ostr);
		otdf << seqGen;
	}

	// Now, try loading from the file	
	
	{
		SequenceGenerator seqGen;
		ifstream istr("seqGenSaveFile.txt");
		ITDF itdf(istr);
		itdf >> seqGen;

		int i = oneCounter;
		for(oneCounter; oneCounter < i + 50; oneCounter++)
		{
			if(oneCounter  != seqGen.getNext(seqOne))
			{
				cerr << "(oneCounter != seqGen.getNext(seqOne))" << endl;
				return false;
			} // if
		} // for
		
		i = twoCounter;
		for(twoCounter; twoCounter < i + 50; twoCounter++)
		{
			if(twoCounter != seqGen.getNext(seqTwo))
			{
				cerr << "(twoCounter != seqGen.getNext(seqTwo))" << endl;
				return false;
			} // if
		} // for

		// Should work just fine
		seqGen.removeSequence(seqTwo);
	
		// Now, fail on purpose
		try
		{
			seqGen.removeSequence(seqTwo);
			Exception exp("ObjectNotFound Exception was not thrown, test failed");
			throw exp;
		} catch (ObjectNotFoundException exp)
		{
			// expected, do nothing
		} // try
	}		
	return true;	
} // testSequence

int main(void)
{
	try
	{
		// create the file
		{
			ofstream touch("seqGenSaveFile.txt");
		}
		if(testSequence())
		{
			cerr << "Test Succeeded" << endl;
		} else
		{
			cerr << "Test Failed" << endl;
			return -1;
		} // if
	} catch (Exception& exp)
	{
		cerr << "Caught Unknown Exception! exp.why:" << exp.why() << endl;
		cerr << "Test Failed" << endl;
		return -1;
	} catch (...)
	{
		cerr << "Caught Unknown Exception!" << endl;
		cerr << "Test Failed" << endl;
		return -1;
	} // try
	return 0;
} // main
