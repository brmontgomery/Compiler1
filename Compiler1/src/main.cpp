#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>

#include "Utils.h"


//{--------------------------------------------------------------}
//{ Constant Declarations }
TextIO io;

//{--------------------------------------------------------------}
//{ Forward Declarations }
void Expression();


//{--------------------------------------------------------------}
//{ Match a Specific Input Character }
void Match(char x) {
	if (io.Look == x) {
		io.GetChar();
	}
	else {
		io.Expected("\'" + x + '\'');
	}
}


//{--------------------------------------------------------------}
//{ Recognize an Alpha Character }
bool IsAlpha(char c) {
	return std::isalpha(c);
}


//{--------------------------------------------------------------}
//{ Recognize a Decimal Digit }
bool IsDigit(char c) {
	return std::isdigit(c);
}


//{--------------------------------------------------------------}
//{ Recognize an Addop }
bool IsAddop(char c) {
	return (c == '+' || c == '-');
}


//{--------------------------------------------------------------}
//{ Get an Identifier }
char GetName() {
	if (!IsAlpha(io.Look)) {
		io.Expected("Name");
	}

	char returnChar = std::toupper(io.Look);
	io.GetChar();
	return returnChar;
}


//{--------------------------------------------------------------}
//{ Get a Number }
char GetNum() {
	if (!IsDigit(io.Look)) {
		io.Expected("Integer");
	}

	char returnChar = io.Look;
	io.GetChar();
	return returnChar;
}


//{-------------------------------------------------------------- - }
//{ Parse and Translate an Identifier }

void Ident() {
	char Name = GetName();
	if (io.Look == '(') {
		Match('(');
		Match(')');
		io.EmitLn("BSR " + Name);
	}
	else {
		io.EmitLn(std::string("MOVE ") + Name + std::string("(PC), D0"));
	}
}


//{--------------------------------------------------------------}
//{ Change an Expression to Assembly }
void Factor() {
	if (io.Look == '(') {
		Match('(');
		Expression();
		Match(')');
	}
	else if (IsAlpha(io.Look)) {
		Ident();
	}
	else {
		io.EmitLn(std::string("MOVE #") + GetNum() + std::string(", D0"));
	}
}


//{--------------------------------------------------------------}
//{ Recognize and Translate a Multiply }

void Multiply() {
	Match('*');
	Factor();
	io.EmitLn("MULS (SP)+, D0");
}


//{------------------------------------------------------------ - }
//{ Recognize and Translate a Divide }

void Divide() {
	Match('/');
	Factor();
	io.EmitLn("MOVE (SP)+,D1");
	io.EmitLn("DIVS D1,D0");
}


//{-------------------------------------------------------------- - }
//{ Parse and Translate a Math Term }

void Term() {
	Factor();
	while (io.Look == '*' || io.Look == '/') {
		io.EmitLn("MOVE D0,-(SP)");
		switch (io.Look) {
			case '*': 
				Multiply();
				break;
			case '/': 
				Divide();
				break;
			default:
				io.Expected("Mulop");
		}
	}
}


//{--------------------------------------------------------------}
//{ Recognize and Translate an Add }
void Add() {
	Match('+');
	Term();
	io.EmitLn("ADD (SP)+,D0");
}


//{------------------------------------------------------------ - }
//{ Recognize and Translate a Subtract }
void Subtract() {
	Match('-');
	Term();
	io.EmitLn("SUB (SP)+,D0");
	io.EmitLn("NEG D0");
}

//{-------------------------------------------------------------- - }
//{ Parse and Translate an Expression }
void Expression() {
	if (IsAddop(io.Look)) {
		io.EmitLn("CLR D0");
	}
	else {
		Term();
		while (IsAddop(io.Look)) {
			io.EmitLn("MOVE D0, -(SP)");
			switch (io.Look) {
			case '+':
				Add();
				break;
			case '-':
				Subtract();
				break;
			default:
				io.Expected("Addop");
			}
		}
	}
}

//{--------------------------------------------------------------}
//{ Parse and Translate an Assignment Statement }

void Assignment() {
	char Name = GetName();
	Match('=');
	Expression();
	io.EmitLn(std::string("LEA ") + Name + std::string("(PC),A0"));
	io.EmitLn("MOVE D0, (A0)");
}


//{--------------------------------------------------------------}
//{ Initialize }
void Init() {
	io.GetLine();
}

//{--------------------------------------------------------------}
//{ Main Program }
int main() {
	Init();
	Assignment();
	if (io.Look != '\r' && io.Look != '\n' && io.Look != '\0') {
		io.Expected("Newline");
	}
	return 0;
}
//{--------------------------------------------------------------}