/*
 ============================================================================
 Name        : OranProgLang.c
 Author      :
 Version     :
 Copyright   : Your copyright notice
 Description : Rules from problem 1:
 	 	 	 	 A-->aB|b|cBB
 	 	 	 	 B-->aB|bA|cBb
 	 	 	 	 C-->aaA|b|caB
 ============================================================================
 */

/* front.c - a lexical analyzer system for simple
             arithmetic expressions */
#include <stdio.h>
#include <ctype.h>

/* Global declarations */ /* Variables */
int charClass;
char lexeme [100];
char nextChar;
int lexLen;
int token;
int nextToken;
FILE *in_fp, *fopen();

/* Function declarations */
void addChar();
void getChar();
void getNonBlank();
int lex();
void A();
void error();

/* Character classes */
#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99

/* Token codes */
#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26


/* main driver */
main() {
/* Open the input data file and process its contents */
	if ((in_fp = fopen("1_8.in", "r")) == NULL)
		printf("ERROR - cannot open 1_8.in \n");
	else {
		getChar();
//		do {
//			lex();
//		} while (nextToken != EOF);
		A();
	}
}

/*****************************************************/
/* addChar - a function to add nextChar to lexeme */
void addChar() {
	if (lexLen <= 98) {
		lexeme[lexLen++] = nextChar;
		lexeme[lexLen] = 0;
	}
	else
		printf("Error - lexeme is too long \n");
}

/*****************************************************/
/* getChar - a function to get the next character of input and determine its character class */
void getChar() {
	if ((nextChar = getc(in_fp)) != EOF) {
		if (isalpha(nextChar) && islower(nextChar))
			charClass = LETTER;
		else charClass = UNKNOWN;
	}
	else
		charClass = EOF;
}

/*****************************************************/
/* getNonBlank - a function to call getChar until it returns a non-whitespace character */
void getNonBlank() {
	while (isspace(nextChar))
		getChar();
}

/******************************************************/
/* lex - a simple lexical analyzer for arithmetic expressions */
int lex() {
	lexLen = 0;
	getNonBlank();
	switch (charClass) {
		/* Parse identifiers */
		case LETTER:
			addChar();
			getChar();
			while (charClass == LETTER || charClass == DIGIT) {
				addChar();
				getChar();
			}
			nextToken = IDENT;
			break;
		/* Parse integer literals */
		case DIGIT:
			addChar();
			getChar();
			while (charClass == DIGIT) {
				addChar();
				getChar();
			}
			nextToken = INT_LIT;
			break;
		/* Parentheses and operators */
		case UNKNOWN:
			lookup(nextChar);
			getChar();
			break;
		/* EOF */
		case EOF:
			nextToken = EOF;
			lexeme[0] = 'E';
			lexeme[1] = 'O';
			lexeme[2] = 'F';
			lexeme[3] = 0;
			break;
	} /* End of switch */

￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼    printf("Next token is: %d, Next lexeme is %s\n", nextToken, lexeme);
	return nextToken;
} /* End of function lex */

void A(){
	pringtf("Enter <A>");

	/* Determine which RHS A-->aB|b|cBB */
	if(nextToken == 'a'){ //A-->aB
		/* get the next token */
		lex();
		B();
	}
	else if(nextToken == 'b'){ //A-->b
		lex();
	}
	else if(nextToken == 'c'){ //A-->cBB
		lex();
		B();
		B();
	}
	else
		error();

	pringtf("Exit <A>");
}

void B(){
	pringtf("Enter <B>");

	/* Determine which RHS   B-->aB|bA|cBb */
	if(nextToken == 'a'){ //B-->aB
		/* get the next token */
		lex();
		B();
	}
	else if(nextToken == 'b'){ //B-->bA
		lex();
		A();
	}
	else if(nextToken == 'c'){ //B-->cBb
		lex();
		B();
		if(nextToken == 'b')
			lex();
		else
			error();
	}
	else
		error();

	pringtf("Exit <B>");
}


void C(){
	pringtf("Enter <C>");

	/* Determine which RHS   C-->aaA|b|caB */
	if(nextToken == 'a'){   //C-->aaA
		/* get the next token */
		lex();
		if(nextToken == 'a')
			lex();
		else
			error();
		A();
	}
	else if(nextToken == 'b'){ //C-->b
		lex();
	}
	else if(nextToken == 'c'){ //C-->caB
		lex();
		if(nextToken == 'a')
			lex();
		else
			error();
		B();
	}
	else
		error();

	pringtf("Exit <C>");
}
