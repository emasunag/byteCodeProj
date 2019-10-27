//
// Created by Ethan Masunaga and daryl on 10/21/19.
//
#include <iostream>
#include <vector>
using namespace std;

enum data_types{INT, CHAR, SHORT, FLOAT};
enum values{
    CMPE =132,
    CMPLT =136,
    CMPGT =140,
    JMP =36,
    JMPC = 40,
    CALL = 44,
    RET =48,
    PUSHC =68,
    PUSHS = 69,
    PUSHI = 70,
    PUSHF = 71,
    PUSHVC =72,
    PUSHVS =73,
    PUSHVI =74,
    PUSHVF =75,
    POPM = 76,
    POPV = 80,
    POPA = 77,
    PEEKC = 84,
    PEEKS = 85,
    PEEKI = 86,
    PEEKF = 87,
    POKEC = 88,
    POKES = 89,
    POKEI = 90,
    POKEF = 91,
    SWP = 94,
    ADD = 100,
    SUB = 104,
    MUL = 108,
    DIV = 112,
    PRINTC = 144,
    PRINTS = 145,
    PRINTI = 146,
    PRINTF = 147,
    HALT = 0

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
    void CMPE_func();
    void CMPLT_func();
    void CMPGT_func();
    void JMP_func();
    void JMPC_func();
    void CALL_func();
    void RET_func();
    void PUSHC_func();
    void PUSHS_func();
    void PUSHI_func();
    void PUSHF_func();
    void PUSHVC_func();
    void PUSHVS_func();
    void PUSHVI_func();
    void PUSHVF_func();
    void POPM_func();
    void POPV_func();
    void POPA();
    void PEEKC();
    void PEEKS();
    void PEEKI();
    void PEEKF();
    void SWP();
    void ADD();
    void SUB();
    void MUL();
    void DIV();
    void PRINTC();
    void PRINTS();
    void PRINTI();
    void PRINTF();
    void HALT();



};


