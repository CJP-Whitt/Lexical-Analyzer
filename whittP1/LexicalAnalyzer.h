#ifndef LEX_H
	#define LEX_H
#endif

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

enum token_type { NONE = -1, EOF_T = 100, IDENT_T, NUMLIT_T, STRLIT_T, LISTOP_T, CONS_T, IF_T,
	COND_T, ELSE_T, DISPLAY_T, NEWLINE_T, AND_T, OR_T, NOT_T, DEFINE_T, LET_T, NUMBERP_T,
	LISTP_T, ZEROP_T, NULLP_T, STRINGP_T, PLUS_T, MINUS_T, DIV_T, MULT_T, MODULO_T, ROUND_T,
	EQUALTO_T, GT_T, LT_T, GTE_T, LTE_T, LPAREN_T, RPAREN_T, LBRACK_T, RBRACK_T, SQUOTE_T, ERROR_T,
	NUM_TOKENS };



class LexicalAnalyzer 
{
    public:
		LexicalAnalyzer (char * filename);
		~LexicalAnalyzer ();
		token_type GetToken ();
		string GetTokenName (token_type t) const;
		string GetLexeme () const;
		void ReportError (const string & msg);
		int index_of(const string arr[], int arrSize, string key);
		int index_of_transition(int alphaSize, char key); // Helper function for finding col of trans table from alphabet
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
		const string predicates[5] = {"number", "zero", "list", "null", "string"};
		const string keywords[11] = {"cons", "if", "cond", "else", "display", "newline", "and", "or", "not", "define", "let"};
		const string token_names[NUM_TOKENS] = {"EOF_T", "IDENT_T", "NUMLIT_T", "STRLIT_T", "LISTOP_T", "CONS_T", "IF_T",
			"COND_T", "ELSE_T", "DISPLAY_T", "NEWLINE_T", "AND_T", "OR_T", "NOT_T", "DEFINE_T", "LET_T", "NUMBERP_T",
			"LISTP_T", "ZEROP_T", "NULLP_T", "STRINGP_T", "PLUS_T", "MINUS_T", "DIV_T", "MULT_T", "MODULO_T", "ROUND_T",
			"EQUALTO_T", "GT_T", "LT_T", "GTE_T", "LTE_T", "LPAREN_T", "RPAREN_T", "LBRACK_T", "RBRACK_T", "SQUOTE_T", "ERROR_T"};

		const string alphabet[24] = { "ws","a","c","d","r","alpha","digit",".","(",")","[","]","+","-","*","/","'","=","<",">","?","_","\"","other" };
		const int trans_table[16][25] = {
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
			{0,1,8,6,8,8,8,10,9,LPAREN_T,RPAREN_T,LBRACK_T,RBRACK_T,2,3,MULT_T,DIV_T,SQUOTE_T,EQUALTO_T,5,4,ERROR_T,ERROR_T,7,ERROR_T},
			{0,PLUS_T,PLUS_T,PLUS_T,PLUS_T,PLUS_T,PLUS_T,10,9,PLUS_T,PLUS_T,PLUS_T,PLUS_T,PLUS_T,PLUS_T,PLUS_T,PLUS_T,PLUS_T,PLUS_T,PLUS_T,PLUS_T,PLUS_T,PLUS_T,PLUS_T,PLUS_T},
			{0,MINUS_T,MINUS_T,MINUS_T,MINUS_T,MINUS_T,MINUS_T,10,9,MINUS_T,MINUS_T,MINUS_T,MINUS_T,MINUS_T,MINUS_T,MINUS_T,MINUS_T,MINUS_T,MINUS_T,MINUS_T,MINUS_T,MINUS_T,MINUS_T,MINUS_T,MINUS_T},
			{0,GT_T,GT_T,GT_T,GT_T,GT_T,GT_T,GT_T,GT_T,GT_T,GT_T,GT_T,GT_T,GT_T,GT_T,GT_T,GT_T,GT_T,GTE_T,GT_T,GT_T,GT_T,GT_T,GT_T,GT_T},
			{0,LT_T,LT_T,LT_T,LT_T,LT_T,LT_T,LT_T,LT_T,LT_T,LT_T,LT_T,LT_T,LT_T,LT_T,LT_T,LT_T,LT_T,LTE_T,LT_T,LT_T,LT_T,LT_T,LT_T,LT_T},
			{0,IDENT_T,12,8,11,8,8,8,IDENT_T,IDENT_T,IDENT_T,IDENT_T,IDENT_T,IDENT_T,IDENT_T,IDENT_T,IDENT_T,IDENT_T,IDENT_T,IDENT_T,IDENT_T,IDENT_T,8,IDENT_T,IDENT_T},
			{0,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,STRLIT_T,7},
			{0,IDENT_T,8,8,8,8,8,8,IDENT_T,IDENT_T,IDENT_T,IDENT_T,IDENT_T,IDENT_T,IDENT_T,IDENT_T,IDENT_T,IDENT_T,IDENT_T,IDENT_T,IDENT_T,IDENT_T,8,IDENT_T,IDENT_T},
			{0,ERROR_T,ERROR_T,ERROR_T,ERROR_T,ERROR_T,ERROR_T,13,ERROR_T,ERROR_T,ERROR_T,ERROR_T,ERROR_T,ERROR_T,ERROR_T,ERROR_T,ERROR_T,ERROR_T,ERROR_T,ERROR_T,ERROR_T,ERROR_T,ERROR_T,ERROR_T,ERROR_T},
			{0,NUMLIT_T,NUMLIT_T,NUMLIT_T,NUMLIT_T,NUMLIT_T,NUMLIT_T,10,13,NUMLIT_T,NUMLIT_T,NUMLIT_T,NUMLIT_T,NUMLIT_T,NUMLIT_T,NUMLIT_T,NUMLIT_T,NUMLIT_T,NUMLIT_T,NUMLIT_T,NUMLIT_T,NUMLIT_T,NUMLIT_T,NUMLIT_T,NUMLIT_T},
			{0,IDENT_T,14,8,11,15,8,8,IDENT_T,IDENT_T,IDENT_T,IDENT_T,IDENT_T,IDENT_T,IDENT_T,IDENT_T,IDENT_T,IDENT_T,IDENT_T,IDENT_T,IDENT_T,IDENT_T,8,IDENT_T,IDENT_T},
			{0,IDENT_T,8,8,12,15,8,8,IDENT_T,IDENT_T,IDENT_T,IDENT_T,IDENT_T,IDENT_T,IDENT_T,IDENT_T,IDENT_T,IDENT_T,IDENT_T,IDENT_T,IDENT_T,IDENT_T,8,IDENT_T,IDENT_T},
			{0,NUMLIT_T,NUMLIT_T,NUMLIT_T,NUMLIT_T,NUMLIT_T,NUMLIT_T,13,NUMLIT_T,NUMLIT_T,NUMLIT_T,NUMLIT_T,NUMLIT_T,NUMLIT_T,NUMLIT_T,NUMLIT_T,NUMLIT_T,NUMLIT_T,NUMLIT_T,NUMLIT_T,NUMLIT_T,NUMLIT_T,NUMLIT_T,NUMLIT_T,NUMLIT_T},
			{0,IDENT_T,8,8,8,15,8,8,IDENT_T,IDENT_T,IDENT_T,IDENT_T,IDENT_T,IDENT_T,IDENT_T,IDENT_T,IDENT_T,IDENT_T,IDENT_T,IDENT_T,IDENT_T,IDENT_T,8,IDENT_T,IDENT_T},
			{0,LISTOP_T,8,8,8,8,8,8,LISTOP_T,LISTOP_T,LISTOP_T,LISTOP_T,LISTOP_T,LISTOP_T,LISTOP_T,LISTOP_T,LISTOP_T,LISTOP_T,LISTOP_T,LISTOP_T,LISTOP_T,LISTOP_T,8,LISTOP_T,LISTOP_T}
		};
		
		
};
	
