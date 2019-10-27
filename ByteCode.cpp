#include "ByteCode.h"
#include <iostream>
#include <fstream>

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
    std::vector<uint8_t> contents((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());

    for(auto i: contents) {
        int value = i;
        std::cout << "data: " << value << std::endl;
    }

    std::cout << "file size: " << contents.size() << std::endl;
}

ByteCode::ByteCode(char* argv) {
    vector<unsigned char> memory_local = Read_In(argv);

    while (memory[pc] != HALT) {
        switch ((unsigned char)memory[pc])
        {
            case CMPE:{ CMPE_func(); //cmpe
                break;
            }
            case 136:{ //cmplt
                if(rstack[sp] == rstack[sp-1]){
                    rstack[sp] = 1;}
                else{
                    rstack[sp] = 0;}
                break;
            }

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
    rstack[sp-1] = rstack[sp-1] == rstack[sp];
    sp--;
    rstack.pop_back();
    pc++;
}

void ByteCode::CMPLT_func(){}