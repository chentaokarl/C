/*
 ============================================================================
 Name        : Programming1_8.c
 Author      : Chen Tao (Karl)
 Description : Rules from problem 1:
 	 	 	 	 A-->aB|b|cBB
 	 	 	 	 B-->bA|aBD (fixed the original rule B-->aB|bA|aBb)
 	 	 	 	 D-->¦Å|b (¦Å is empty string)
 	 	 	 	 C-->aaA|b|caB
 ============================================================================
 */

/* front.c - a lexical analyzer system for simple
             arithmetic expressions */
#include <stdio.h>
#include <ctype.h>

/* Global declarations */ /* Variables */
int charClass;
char nextChar;
FILE *in_fp, *fopen();

/* Function declarations */
void getChar();     //get next char from file
void getNonBlank(); //get next non blank char
int lex(); 			//judge if the char is legal
void A();			//parse rule A-->aB|b|cBB
void B();			//parse rule B-->bA|aBD
void C();			//parse rule C-->aaA|b|caB
void D();			//parse rule D-->¦Å|b (¦Å is empty string. fixed the original rule B-->aB|bA|aBb)
void error(char[]); //print detail error message to user

/* Character classes */
#define LETTER 0
#define UNKNOWN 99

/* main driver */
main() {
/* Open the input data file and process its contents */
	if ((in_fp = fopen("1_8.in", "r")) == NULL)
		printf("ERROR - cannot open 1_8.in \n");
	else {
		getChar();
		A();
	}
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
void lex() {
	getNonBlank();
	switch (charClass) {
		case LETTER:
			break;
		case UNKNOWN:
			error("Only lower case letter can be parsed. Cannot parse " + nextChar);
			while (charClass != LETTER)
				getChar();
			break;
		/* EOF */
		case EOF:
			nextChar = EOF;
			break;
	} /* End of switch */

    printf("Next char is %s\n", nextChar);
} /* End of function lex */

/*****************************************************/
void A(){
	printf("Enter <A>");

	/* Determine which RHS A-->aB|b|cBB */
	if(nextChar == 'a'){ //A-->aB
		/* get the next token */
		lex();
		B();
	}
	else if(nextChar == 'b'){ //A-->b
		lex();
	}
	else if(nextChar == 'c'){ //A-->cBB
		lex();
		B();
		B();
	}
	else
		error("For rule A-->aB|b|cBB, input should started with 'a', 'b' or 'c'. ");

	printf("Exit <A>");
}

/*****************************************************/
void B(){
	printf("Enter <B>");

	/* Determine which RHS   B-->bA|aBD */
	if(nextChar == 'a'){ //B-->aBD
		/* get the next token */
		lex();
		B();
		D();
	}
	else if(nextChar == 'b'){ //B-->bA
		lex();
		A();
	}
	else
		error("For rule B-->aB|bA|cBb, input should started with 'a', 'b' or 'c'. ");

	printf("Exit <B>");
}


/*****************************************************/
void C(){
	printf("Enter <C>");

	/* Determine which RHS   C-->aaA|b|caB */
	if(nextChar == 'a'){   //C-->aaA
		/* get the next token */
		lex();
		if(nextChar == 'a')
			lex();
		else
			error("For rule C--aaA, input should started with 'aa'. ");
		A();
	}
	else if(nextChar == 'b'){ //C-->b
		lex();
	}
	else if(nextChar == 'c'){ //C-->caB
		lex();
		if(nextChar == 'a')
			lex();
		else
			error("For rule C--caB, input should started with 'ca'. ");
		B();
	}
	else
		error("For rule C-->aaA|b|caB, input should started with 'a', 'b' or 'c'. ");

	pringtf("Exit <C>");
}

/*****************************************************/
void D(){
	printf("Enter <D>");

		/* Determine which RHS   D-->¦Å|b (¦Å is empty string) */
		if(nextChar == EOF){ //D--¦Å

		}
		else if(nextChar == 'b'){ //D-->b
			lex();
		}
		else
			error("For rule D-->¦Å|b, input should be 'b' or empty ");

		pringtf("Exit <D>");
}

void error(char errorMessage[]){
	printf("Error occurred when with input char: %s, message: %s", nextChar, errorMessage);
}


