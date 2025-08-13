#pragma once
#include <iostream>
#include <string>

class TextIO {
public:
    std::string line;
    char Look;

    //{--------------------------------------------------------------}
    //{ Port of Pascal's WriteLn }
    void WriteLn() {
        std::cout << std::endl;
    }
    void WriteLn(int i) {
        std::cout << i << std::endl;
    }
    void priWriteLnnt(double  f) {
        std::cout << f << std::endl;
    }
    void WriteLn(char* c) {
        std::cout << c << std::endl;
    }
    void WriteLn(std::string s) {
        std::cout << s << std::endl;
    }
    void WriteLn(char c) {
        std::cout << c << std::endl;
    }


    //{--------------------------------------------------------------}
    //{ Read New Line From Input Stream }
    void GetLine() {
        std::cin >> line;
        GetChar();
    }


    //{--------------------------------------------------------------}
    //{ Read New Character From line }
    void GetChar() {
        Look = line[0];
        line.erase(0, 1);
    }


    //{--------------------------------------------------------------}
    //{ Get remaining line chars }
    int getLineLength() {
        return line.length();
    }

    //{--------------------------------------------------------------}
    //{ Report an Error }

    void Error(std::string s) {
        WriteLn();
        WriteLn(std::string('\G' + "Error: " + s + '.'));
    }


    //{--------------------------------------------------------------}
    //{ Report Error and Halt }

    void Abort(std::string s) {
        Error(s);
        std::exit(-1);
    }


    //{--------------------------------------------------------------}
    //{ Report What Was Expected }

    void Expected(std::string s) {
        Abort(std::string(s + " Expected"));
    }

    //{--------------------------------------------------------------}
    //{ Output a String with Tab }

    void Emit(std::string s) {
        WriteLn(std::string('\t' + s));
    }

    //{--------------------------------------------------------------}
    //{ Output a String with Tab and CRLF }

    void EmitLn(std::string s) {
        Emit(s);
        WriteLn();
    }
};