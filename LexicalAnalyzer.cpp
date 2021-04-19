#include <iomanip>
#include <cstdlib>
#include "LexicalAnalyzer.h"

using namespace std;

// Move to header file
enum token_type {NONE = -1, EOF_T = 0, IDENT_T = 100, NUMLIT_T, STRLIT_T, LISTOP_T, CONS_T, IF_T, COND_T, ELSE_T, DISPLAY_T, NEWLINE_T, AND_T, OR_T, NOT_T, DEFINE_T, LET_T, NUMBERP_T, LISTP_T, ZEROP_T, NULLP_T, STRINGP_T, PLUS_T, MINUS_T, DIV_T, MULT_T, MODULO_T, ROUND_T, EQUALTO_T, GT_T, LT_T, GTE_T, LTE_T, LPAREN_T, RPAREN_T, LBRACK_T, RBRACK_T, SQUOTE_T, ERROR_T, NUM_TOKENS};

static string token_names[] = {	"EOF_T", "IDENT_T", "NUMLIT_T": }; 

LexicalAnalyzer::LexicalAnalyzer (char * filename)
{
	// This function will initialize the lexical analyzer class
	string filename_str = filename;
	string listfile_str = filename_str + ".lst";
	string tokenfile_str = filename_str + ".p1";
	string dbfile_str = filename_str + ".dbg";
	
	// Try to open input file
	input.open(filename_str);
	if(!input){
	       	cout << "Error: Input file " << filename << "couldn't be opened" << endl;
		cout << "Terminating" << endl;
		exit(-1);
	}
	listingFile.open(listfile_str , ios::out);
	tokenFile.open(tokenfile_str, ios::out);
	debugFile.open(dbfile_str, ios::out);
	
	// Init position and error count vars
	errors = 0;
	linenum = 1;
	pos = 1;
	
	while(!input.eof()){
		line = input.getline();
		token = GetToken();
		
		
	}


}

LexicalAnalyzer::~LexicalAnalyzer ()
{
	// This function will complete the execution of the lexical analyzer class
	debugFile << "Lexical Analyzer finished. " << errors << " recorded." << endl;
	
	input.close();
	lsitingFile.close()
	tokenFile.close();
	debugFile.close();


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
