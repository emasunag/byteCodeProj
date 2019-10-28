#include "ByteCode.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>

ByteCode::~ByteCode() {}

// rstack = vector that contains data items
//fpstack = first element in function stack frame
//Input refers to program memory
//Run till we reach halt which is opcode (8 0's)
//Runtime stack has all the variables in a vector
//
vector<unsigned char> ByteCode::Read_In(const char* argv){
    //makes vector of mem
    std::ifstream stream(argv, std::ios::in | std::ios::binary);
    std::vector<uint8_t> memory((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());

    return memory;
//    for(auto i: memory) {
//        int value = i;
//        std::cout << "data: " << value << std::endl;
//    }
//
//    std::cout << "file size: " << contents.size() << std::endl;
}

ByteCode::ByteCode(char* argv) {
    vector<unsigned char> memory_local = Read_In(argv);
    //memory = memory_local;
    for(auto i: memory_local) {
        int value = i;
        std::cout << "data: " << value << std::endl;
    }

    std::cout << "file size: " << memory_local.size() << std::endl;

    while (memory_local[pc] != 00) {
        switch ((unsigned char)memory_local[pc])
        {
            case CMPE:{ CMPE_func(); //cmpe
                break;
            }
            case CMPLT:{ CMPLT_func(); break;}
            case CMPGT:{ CMPGT_func(); break;}

        }

    }

}

void ByteCode::CMPE_func(){
    if (rstack[sp].dtype == FLOAT && rstack[sp-1].dtype ==FLOAT)
    {
        rstack[sp-1].int_val = rstack[sp-1].float_val == rstack[sp].float_val;
    }
    if (rstack[sp].dtype == SHORT && rstack[sp-1].dtype ==SHORT)
    {
        rstack[sp-1].int_val = rstack[sp-1].short_val == rstack[sp].short_val;
    }
    if (rstack[sp].dtype == CHAR && rstack[sp-1].dtype ==CHAR)
    {
        rstack[sp-1].int_val = rstack[sp-1].char_val == rstack[sp].char_val;
    }
    if (rstack[sp].dtype == INT && rstack[sp-1].dtype ==INT)
    {
        rstack[sp-1].int_val = rstack[sp-1].int_val == rstack[sp].int_val;
    }
    sp--;
    rstack.pop_back();
    pc++;
}

void ByteCode::CMPLT_func(){
    if (rstack[sp].dtype == FLOAT && rstack[sp-1].dtype ==FLOAT)
    {
        rstack[sp-1].int_val = rstack[sp-1].float_val < rstack[sp].float_val;
    }
    if (rstack[sp].dtype == SHORT && rstack[sp-1].dtype ==SHORT)
    {
        rstack[sp-1].int_val = rstack[sp-1].short_val < rstack[sp].short_val;
    }
    if (rstack[sp].dtype == CHAR && rstack[sp-1].dtype ==CHAR)
    {
        rstack[sp-1].int_val = rstack[sp-1].char_val < rstack[sp].char_val;
    }
    if (rstack[sp].dtype == INT && rstack[sp-1].dtype ==INT)
    {
        rstack[sp-1].int_val = rstack[sp-1].int_val < rstack[sp].int_val;
    }
    sp--;
    rstack.pop_back();
    pc++;
}

void ByteCode::CMPGT_func(){
    if (rstack[sp].dtype == FLOAT && rstack[sp-1].dtype ==FLOAT)
    {
        rstack[sp-1].int_val = rstack[sp-1].float_val > rstack[sp].float_val;
    }
    if (rstack[sp].dtype == SHORT && rstack[sp-1].dtype ==SHORT)
    {
        rstack[sp-1].int_val = rstack[sp-1].short_val > rstack[sp].short_val;
    }
    if (rstack[sp].dtype == CHAR && rstack[sp-1].dtype ==CHAR)
    {
        rstack[sp-1].int_val = rstack[sp-1].char_val > rstack[sp].char_val;
    }
    if (rstack[sp].dtype == INT && rstack[sp-1].dtype ==INT)
    {
        rstack[sp-1].int_val = rstack[sp-1].int_val > rstack[sp].int_val;
    }
    sp--;
    rstack.pop_back();
    pc++;
}





void ByteCode::PUSHC_func(){
    data test;
    test.char_val = memory[pc+1];
    test.dtype = CHAR;
    rstack.push_back(test);
    pc += 2;
}

void ByteCode::PUSHS_func(){
    data test;
    unsigned char bytes[2] = {memory[1],memory[2]};
    short valx;
    memcpy(bytes,&valx,2);
    test.short_val = valx;
    test.dtype = SHORT;
    rstack.push_back(test);
    pc += 2;
}

//void ByteCode::PUSHVC_func() {
//    rstack[sp] = rstack[fpstack[fpsp]+rstack[sp]+1];
//}

void ByteCode::JMP_func(){
    pc = rstack[sp];
    sp--;
}
void ByteCode::JMPC_func(){
    if (rstack[sp-1].int_val == 1) {
        pc = rstack[sp];
    }
    else {
        pc++;
    }
    sp -= 2;
}
void ByteCode::CALL_func(){
    fpstack[++fpsp] = (sp - rstack[sp].int_val) - 1;  // subtract off argument stack entries
    sp--;
    pc = rstack[sp--]; //set the PC to the address of the label to be jumped to
}
void ByteCode::RET_func(){

}