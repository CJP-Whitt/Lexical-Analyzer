#include <iomanip>
#include <cstdlib>
#include <map>
#include "LexicalAnalyzer.h"

using namespace std;



LexicalAnalyzer::LexicalAnalyzer (char * filename)
{
	// This function will initialize the lexical analyzer class
	string filename_str = filename;
	string listfile_str = filename_str + ".lst";
	string tokenfile_str = filename_str + ".p1";
	string dbfile_str = filename_str + ".dbg";
	
	debugFile.open(dbfile_str, ios::out); // Open & create and write debug file
	
	// Try to open input file
	input.open(filename_str, ifstream::in);
	if(!input.is_open()){
	    cout << "Error: Input file " << filename << "couldn't be opened" << endl;
		cout << "Terminating" << endl;
		exit(-1);
	}
	else {
		listingFile << "Input file: " << filename_str << endl;
		debugFile << "Using filenanme: " << filename_str << endl;
	}

	listingFile.open(listfile_str , ios::out); // Open & create and write listing file
	tokenFile.open(tokenfile_str, ios::out); // Open & create and write token file

	/***** START Tokenizer Loop *****/
	line = "";
	linenum = 0;
	while (input.good()) {
		
		if (pos > line.length()) { // Check if more input needs to be grabbed
			if (getline(input, line)) { // Try to grab another line
				linenum++;
				listingFile << "\t" << linenum << ": " << line.substr(0, line.length() - 2) << endl;
			}
		}

		token = GetToken(); // Get next token

		if (token == ERROR_T) { // Error token print condition
			debugFile << "Error at " << line << ", " << pos - 1 << ": Invalid character found: " << GetLexeme() << endl;
			listingFile << "Error at " << line << ", " << pos - 1 << ": Invalid character found: " << GetLexeme() << endl;
			errors++;
		}
		else if (token == NONE) { // NONE token leads to error
			debugFile << "Invalid token found --> " << GetTokenName(token) << ", " << GetLexeme() << "> on Ln: " << line << "Ch: " << pos - GetLexeme().length() << endl;
		}
		else { // Anyother token just print it.
			tokenFile << GetTokenName(token) << "\t" << GetLexeme() << endl; // Write tuple to .p1 file
			debugFile << "Found token --> <" << GetTokenName(token) << ", " << GetLexeme() << "> on Ln: " << line << "Ch: " << pos - GetLexeme().length() << endl;
		}

	}
	/***** END Tokenizer Loop *****/

	this->~LexicalAnalyzer();
}

LexicalAnalyzer::~LexicalAnalyzer ()
{
	// This function will complete the execution of the lexical analyzer class
	listingFile << errors << " errors found in input file" << endl;
	debugFile << "Lexical Analyzer finished. " << errors << " errors recorded." << endl;
	
	input.close();
	listingFile.close();
	tokenFile.close();
	debugFile.close();
}	

token_type LexicalAnalyzer::GetToken ()
{
	// This function will find the next lexeme int the input file and return
	// the token_type value associated with that lexeme
	lexeme = "";
	if (input.eof()) { // Check for end of file
		token = EOF_T;
		return token;
	}


	
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
	listingFile << "Error at " << linenum << "," << pos << ": Invalid character found: " << msg << endl;
	debugFile << "Error at " << linenum << "," << pos << ": Invalid character found: " << msg << endl;
}

void LexicalAnalyzer::ReadTransitionTable(string filename) {
	ifstream csvFile(filename, ios::in);
	int num;

	while (csvFile.good()) {
		
	}




	csvFile.close();
}
