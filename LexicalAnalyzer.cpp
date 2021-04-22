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
	
	cout << "Created Debug file, open for writing" << endl;
	debugFile.open(dbfile_str, ofstream::out); // Open & create and write debug file
	
	
	// Try to open input file
	input.open(filename_str, ifstream::in);
	if(!input.is_open()){
	    cout << "Error: Input file " << filename << "couldn't be opened" << endl;
		cout << "Terminating" << endl;
		exit(-1);
	}
	
	listingFile.open(listfile_str , ofstream::out); // Open & create and write listing file
	tokenFile.open(tokenfile_str, ofstream::out); // Open & create and write token file
	listingFile << "Input file: " << filename_str << endl;
	debugFile << "Using filenanme: " << filename_str << endl;

	linenum = 0;
	pos = 1;
	line = " "; // Initialized to start while loop in GetToken
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
	// This function will find the next lexeme in the input file and return
	// the token_type value associated with that lexeme
	debugFile << "GetToken : Getting Token...starting from Ln: " << linenum << ", Ch: " << pos << endl;

	int col;
	lexeme = "";
	int state = 1;

	if (pos >= line.length()){
		line = " ";
		pos = 1;
	}
			

	// Skip spaces and get newline if necessary
	while (line.empty() || isspace(line[pos-1])){
		debugFile << "\tSkipping whitespace..." << endl;

		pos++;
		if (pos-1 >= line.length()){
			if (input.eof()){
				debugFile << "\tToken processed --> " << GetTokenName(EOF_T) << endl << endl;
				tokenFile << setw(20) << left << GetTokenName(EOF_T);
				return EOF_T;
			}
			debugFile << "\tReached end of line...getting new line" << endl;
			getline(input, line);
			linenum++;
			pos = 1;

			if(!input.eof()){
				listingFile << "\t" << linenum << ": " << line << endl;
			}else{
				debugFile << "\tToken processed --> " << GetTokenName(EOF_T) << endl << endl;
				tokenFile << setw(20) << left << GetTokenName(EOF_T);
				return EOF_T;
			}

			
			
			if (input.fail()){
				debugFile << "\tError grabbing line " << linenum << ". Input failed returning NONE token." << endl;
				cout << "Error: Unknown GetToken() issue occured. Input failed...Terminating" << endl;
				// exit(-1);
			}
		}
	}

	// Get next token char by char
	debugFile << "\tScanning chars..." << endl;
	while (state > 0 && pos-1 < line.length()) { // Traverse state transition table
		debugFile << "\t(" << state << ")";
		col = index_of_transition((sizeof(alphabet)/sizeof(alphabet[0])), line[pos-1]);
		state = trans_table[state][col+1];
		lexeme += line[pos-1];
		debugFile << " --> (" << state << ") on \"" << line[pos-1] << "\", Lexeme: \"" << lexeme << "\"" << endl;
		pos++;
		if (state >= 100){
			debugFile << "\tTerminating state on " << GetTokenName(token_type(state)) << endl;
			break;
		}
	}

	if(state < 100){ // If dfa terminated on non final state
		state = trans_table[state][23]; // Get state on other transition since end of line
		lexeme += ' ';
		if(state < 100){ // If still not terminated state, must be missing quote
			ReportError(lexeme);
			errors++;
			debugFile << "\tNo end \" found... " << endl;
			debugFile << "\tToken processed --> " << GetTokenName(ERROR_T) << endl << endl;
			tokenFile << setw(20) << left << GetTokenName(ERROR_T) << setw(20) << left << GetLexeme() << endl;
			state = ERROR_T;
		}
		
		debugFile << "\tTerminating state on " << GetTokenName(token_type(state)) << endl;	
	}

	switch (state){
		case int(IDENT_T):{
			pos--; // Go back one char to see what broke the ident string

			
			/* Check predicate case */
			debugFile << "\t\tChecking for predicates..." << endl;
			if(line[pos-1] == '?'){ // If the ident broke on a question mark, check the ident string.
				int pred_index = index_of(predicates, int(sizeof(predicates)/sizeof(predicates[0])), lexeme.substr(0, lexeme.length()-1)); // Is it a predicate string?
				if(pred_index != -1){ // If it is leave ? in lexeme and reincrement pos
					pos++; 
					debugFile << "\tToken processed --> " << GetTokenName(token_type(116 + pred_index)) << endl << endl;
					tokenFile << setw(20) << left << GetTokenName(token_type(116 + pred_index)) << setw(20) << left << GetLexeme() << endl;
					return token_type(116 + pred_index); // Get corresponding precicate token type
				}
			}

			/* Check Keywords + (modulo/round) case */
			lexeme.pop_back();
			int keyword_index = index_of(keywords, int(sizeof(keywords)/sizeof(keywords[0])), lexeme);
			debugFile << "\t\tChecking \"" << lexeme << "\" for reserved words...Index = " << keyword_index << endl;
			if(keyword_index != -1){ // If it is a keyword then find which one and return
				debugFile << "\tToken processed --> " << GetTokenName(token_type(105 + keyword_index)) << endl << endl;
				tokenFile << setw(20) << left << GetTokenName(token_type(105 + keyword_index)) << setw(20) << left << GetLexeme() << endl;
				return token_type(105 + keyword_index); // Get corresponding precicate token type
			}
			else if(lexeme == "modulo"){
				debugFile << "\tToken processed --> " << GetTokenName(MODULO_T) << endl << endl;
				tokenFile << setw(20) << left << GetTokenName(MODULO_T) << setw(20) << left << GetLexeme() << endl;
				return MODULO_T;
			}
			else if(lexeme == "round"){
				debugFile << "\tToken processed --> " << GetTokenName(ROUND_T) << endl << endl;
				tokenFile << setw(20) << left << GetTokenName(ROUND_T) << setw(20) << left << GetLexeme() << endl;
				return ROUND_T;
			}

			debugFile << "\tToken is normal IDENT_T" << endl;
			break;
		}
		
		case int(NUMLIT_T):{
			pos--;
			lexeme.pop_back();
			debugFile << "\tToken processed --> " << GetTokenName(NUMLIT_T) << endl << endl;
			tokenFile << setw(20) << left << GetTokenName(NUMLIT_T) << setw(20) << left << GetLexeme() << endl;
			return NUMLIT_T;
		}

		case int(LISTOP_T):{
			pos--;
			lexeme.pop_back();
			debugFile << "\tToken processed --> " << GetTokenName(LISTOP_T) << endl << endl;
			tokenFile << setw(20) << left << GetTokenName(LISTOP_T) << setw(20) << left<< GetLexeme() << endl;
			return LISTOP_T;
		}

		case int(GT_T):{
			pos--;
			lexeme.pop_back();
			debugFile << "\tToken processed --> " << GetTokenName(GT_T) << endl << endl;
			tokenFile << setw(20) << left << GetTokenName(GT_T) << setw(20) << left << GetLexeme() << endl;
			return GT_T;
		}

		case int(LT_T):{
			pos--;
			lexeme.pop_back();
			debugFile << "\tToken processed --> " << GetTokenName(LT_T) << endl << endl;
			tokenFile << setw(20) << left << GetTokenName(LT_T) << setw(20) << left << GetLexeme() << endl;
			return LT_T;
		}

		case int(PLUS_T):{
			pos--;
			lexeme.pop_back();
			debugFile << "\tToken processed --> " << GetTokenName(PLUS_T) << endl << endl;
			tokenFile << setw(20) << left << GetTokenName(PLUS_T) << setw(20) << left << GetLexeme() << endl;
			return PLUS_T;
		}

		case int(MINUS_T):{
			pos--;
			lexeme.pop_back();
			debugFile << "\tToken processed --> " << GetTokenName(MINUS_T) << endl << endl;
			tokenFile << setw(20) << left << GetTokenName(MINUS_T) << setw(20) << left << GetLexeme() << endl;
			return MINUS_T;
		}

		case int(ERROR_T):{
			if(lexeme[0] == '.'){
				pos--;
				lexeme.pop_back();
			}

			debugFile << "\tToken processed --> " << GetTokenName(ERROR_T) << endl << endl;
			tokenFile << setw(20) << left << GetTokenName(ERROR_T) << setw(20) << left << GetLexeme() << endl;
			ReportError(lexeme);
			errors++;
			return ERROR_T;
		}
		
		default: {// For last char on a line case
			break;
		}
	}


	/* Non special case (tokens terminated with character that lead to final state) */
	debugFile << "\tToken processed --> " << GetTokenName(token_type(state%100)) << endl << endl;
	tokenFile << setw(20) << left << GetTokenName(token_type(state%100)) << setw(20) << left << GetLexeme() << endl;
	return token_type(state%100);
}

string LexicalAnalyzer::GetTokenName (token_type t) const
{
	// The GetTokenName function returns a string containing the name of the
	// token passed to it. 
	if(t == NONE)
		return "";
	
	return token_names[int(t)%100];
}

string LexicalAnalyzer::GetLexeme () const
{
	// This function will return the lexeme found by the most recent call to 
	// the get_token function
	return lexeme;
}

void LexicalAnalyzer::ReportError (const string & msg)
{
	// This function will be called to write an error message to a file
	listingFile << "Error at " << linenum << "," << pos-1 << ": Invalid character(s) found: " << msg << endl;
	debugFile << "Error at " << linenum << "," << pos-1 << ": Invalid character(s) found: " << msg << endl;
}

int LexicalAnalyzer::index_of(const string arr[], int arrSize, string key){
	for(int i=0; i < arrSize; i++){
		if(arr[i] == key){
			return i;
		}
	}

	return -1;
}

int LexicalAnalyzer::index_of_transition(int alphabetSize, char key){
	// This funciton is called to get the corresponding col for a given char from the line.
	// The col represents the input on the trans table.
	string key_str;
	key_str += key;

	for(int i = 0; i < alphabetSize; i++){
		if(key_str == alphabet[i]){
			return i;
		}
	}

	if(isspace(key)){
		return 0;
	}else if(isalpha(key)){
		return 5;
	}else if(isdigit(key)){
		return 6;
	}else
		return 23; // Unknown
}
