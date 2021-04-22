#include <cstdlib>
#include <iostream>
#include <iomanip>
#include "SetLimits.h"
#include "SyntacticalAnalyzer.h"

using namespace std;

int main (int argc, char * argv[])
{
	

	if (argc < 2)
	{
		printf ("format: proj1 <filename>\n");
		exit (1);
	}
	cout << "Using --> " << argv[1] << endl;
	SetLimits ();
	cout << "SetLimits done..." << endl;
	SyntacticalAnalyzer parser (argv[1]);

	return 0;
}
