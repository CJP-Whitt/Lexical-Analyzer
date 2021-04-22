#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include "SyntacticalAnalyzer.h"

using namespace std;

SyntacticalAnalyzer::SyntacticalAnalyzer (char * filename)
{
	cout << "SyntacticalAnalyzer using --> " << filename << endl;
	lex = new LexicalAnalyzer (filename);
	cout << "Created Lexical Analyzer" << endl;
	token_type t;
	while ((t = lex->GetToken()) != EOF_T)
	{
		
	}

	cout << "Lexical Analyzer Finished" << endl;

}

SyntacticalAnalyzer::~SyntacticalAnalyzer ()
{
	delete lex;
}
