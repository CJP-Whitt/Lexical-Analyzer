#ifndef LEX_H
#define LEX_H

#include <iostream>
#include <fstream>

using namespace std;

enum token_type {NONE = -1, EOF_T = 0, IDENT_T = 1, NUMLIT_T, NUM_TOKENS};

class LexicalAnalyzer 
{
    public:
	LexicalAnalyzer (char * filename);
	~LexicalAnalyzer ();
	token_type GetToken ();
	string GetTokenName (token_type t) const;
	string GetLexeme () const;
	void ReportError (const string & msg);
	ofstream debugFile;	// .dbg
    private:
	ifstream input; 	// .ss 
	ofstream listingFile;	// .lst
	ofstream tokenFile;	// .p1
	token_type token;
	string line;
	int linenum;
	int pos;
	string lexeme;
	int errors;
};
	
#endif
