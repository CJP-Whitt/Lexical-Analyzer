#include <iomanip>
#include <cstdlib>
#include "LexicalAnalyzer.h"

using namespace std;

//enum token_type {NONE = -1, EOF_T = 0, IDENT_T = 1, NUMLIT_T, NUM_TOKENS};
static string token_names[] = {	"EOF_T", "IDENT_T", "NUMLIT_T": }; 

LexicalAnalyzer::LexicalAnalyzer (char * filename)
{
	// This function will initialize the lexical analyzer class
}

LexicalAnalyzer::~LexicalAnalyzer ()
{
	// This function will complete the execution of the lexical analyzer class
}

token_type LexicalAnalyzer::GetToken ()
{
	// This function will find the next lexeme int the input file and return
	// the token_type value associated with that lexeme
	return token;
}

string LexicalAnalyzer::GetTokenName (token_type t) const
{
	// The GetTokenName function returns a string containing the name of the
	// token passed to it. 
	return "";
}

string LexicalAnalyzer::GetLexeme () const
{
	// This function will return the lexeme found by the most recent call to 
	// the get_token function
	return "";
}

void LexicalAnalyzer::ReportError (const string & msg)
{
	// This function will be called to write an error message to a file
}
