//
// Created by Ethan Masunaga and daryl on 10/21/19.
//
#include <iostream>
#include <vector>
using namespace std;

enum data_types{INT, CHAR, SHORT, FLOAT};
enum values{
    CMPE =132,
    PUSHC =68,
    PUSHS = 69,
    PUSHI = 70,
    PUSHF = 71;


};

struct data{
    data_types dtype;
    int int_val;
    char char_val;
    short short_val;
    float float_val;

};
class ByteCode {
public:
    int sp = -1; //top of runtime stack
    int fpsp = -1; //top of frame stack
    int pc = 0; //contains address of next instruction
    vector<unsigned char> memory;
    vector<data> rstack;
    ByteCode(char*);
    virtual ~ByteCode();
    vector<unsigned char> Read_In(const char* argv);
    void ByteCode::CMPE_func();


};


