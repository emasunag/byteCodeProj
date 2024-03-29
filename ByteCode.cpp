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
        switch ((int)memory_local[pc])
        {
            case CMPE:{ CMPE_func(); //cmpe
                break;
            }
            case CMPLT:{ CMPLT_func(); break;}
            case CMPGT:{ CMPGT_func(); break;}

        }
        pc++;

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
    rstack[sp-1].dtype = INT;
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
    rstack[sp-1].dtype = INT;
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
    rstack[sp-1].dtype = INT;
    sp--;
    rstack.pop_back();
    pc++;
}

//__________________CONTROL FLOW FUNCTIONS__________________

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

//__________________STACK MANIPULATION BYTE FUNCTIONS__________________

void ByteCode::PUSHC_func(){
    data test;
    test.char_val = memory[pc+1];
    test.dtype = CHAR;
    rstack.push_back(test);
    pc += 2;
}

void ByteCode::PUSHS_func(){
    data test;
    unsigned char bytes[2] = {memory[pc+1],memory[pc+2]};
    short val;
    memcpy(&val,bytes,2);
    test.short_val = val;
    test.dtype = SHORT;
    rstack.push_back(test);
    pc += 2;
}

void ByteCode::PUSHI_func(){
    data test;
    unsigned char bytes[4] = {memory[pc+1],memory[pc+2],memory[pc+3],memory[pc+4]};
    int val;
    memcpy(&val,bytes,4);
    test.int_val = val;
    test.dtype = INT;
    rstack.push_back(test);
    pc+=2;
}

void ByteCode::PUSHF_func(){
    data test;
    unsigned char bytes[4] = {memory[pc+1],memory[pc+2],memory[pc+3],memory[pc+4]};
    float val;
    memcpy(bytes,&val,4);
    test.float_val = val;
    test.dtype = FLOAT;
    rstack.push_back(test);
    pc+=2;
}
void ByteCode::PUSHVC_func() {
    rstack.push_back(rstack[fpstack[fpsp]+rstack[sp].char_val+1]);
    pc++;
}
void ByteCode::PUSHVI_func() {
    rstack.push_back(rstack[fpstack[fpsp]+rstack[sp].int_val+1]);
    pc++;
}
void ByteCode::PUSHVF_func() {
    rstack.push_back(rstack[fpstack[fpsp]+rstack[sp].float_val+1]);
    pc++;
}
void ByteCode::POPM_func() {
    sp -= rstack[sp]+1;

}

void ByteCode::SWP(){
    data temp = rstack[sp];
    rstack[sp] = rstack[sp-1];
    rstack[sp-1] = temp;
    pc++;
}

//__________________ARITHMETIC FUNCTIONS__________________

void ByteCode::ADD(){
    if (rstack[sp].dtype == FLOAT){
        rstack[sp-1].float_val = rstack[sp-1].float_val + rstack[sp].float_val;
    }
    else if (rstack[sp].dtype == INT){
        rstack[sp-1].int_val = rstack[sp-1].int_val + rstack[sp].int_val;
    }
    else if (rstack[sp].dtype == CHAR){
        rstack[sp-1].char_val = rstack[sp-1].char_val + rstack[sp].char_val;
    }
    else if (rstack[sp].dtype == SHORT){
        rstack[sp-1].short_val = rstack[sp-1].short_val + rstack[sp].short_val;
    }
    sp--;
}
void ByteCode::SUB(){
    if (rstack[sp].dtype == FLOAT){
        rstack[sp-1].float_val = rstack[sp-1].float_val - rstack[sp].float_val;
    }
    else if (rstack[sp].dtype == INT){
        rstack[sp-1].int_val = rstack[sp-1].int_val - rstack[sp].int_val;
    }
    else if (rstack[sp].dtype == CHAR){
        rstack[sp-1].char_val = rstack[sp-1].char_val - rstack[sp].char_val;
    }
    else if (rstack[sp].dtype == SHORT){
        rstack[sp-1].short_val = rstack[sp-1].short_val - rstack[sp].short_val;
    }
    sp--;
}
void ByteCode::MUL(){
    if (rstack[sp].dtype == FLOAT){
        rstack[sp-1].float_val = rstack[sp-1].float_val * rstack[sp].float_val;
    }
    else if (rstack[sp].dtype == INT){
        rstack[sp-1].int_val = rstack[sp-1].int_val * rstack[sp].int_val;
    }
    else if (rstack[sp].dtype == CHAR){
        rstack[sp-1].char_val = rstack[sp-1].char_val * rstack[sp].char_val;
    }
    else if (rstack[sp].dtype == SHORT){
        rstack[sp-1].short_val = rstack[sp-1].short_val * rstack[sp].short_val;
    }
    sp--;
}
void ByteCode::DIV(){
    if (rstack[sp].dtype == FLOAT){
        rstack[sp-1].float_val = rstack[sp-1].float_val / rstack[sp].float_val;
    }
    else if (rstack[sp].dtype == INT){
        rstack[sp-1].int_val = rstack[sp-1].int_val / rstack[sp].int_val;
    }
    else if (rstack[sp].dtype == CHAR){
        rstack[sp-1].char_val = rstack[sp-1].char_val / rstack[sp].char_val;
    }
    else if (rstack[sp].dtype == SHORT){
        rstack[sp-1].short_val = rstack[sp-1].short_val / rstack[sp].short_val;
    }
    sp--;
}

//__________________SPECIAL FUNCTIONS__________________

void ByteCode::PRINTC(){
    std::cout << rstack[sp--].char_val << std::endl;
}
void ByteCode::PRINTS(){
    std::cout << rstack[sp--].short_val << std::endl;
}
void ByteCode::PRINTI(){
    std::cout << rstack[sp--].int_val << std::endl;
}
void ByteCode::PRINTF(){
    std::cout << rstack[sp--].float_val << std::endl;
}
void ByteCode::HALT(){
    // Print pc, sp, rstack, fpsp, fpstack.
    std::cout << "PC: " << pc << std::endl;
    std::cout << "SP: " << sp << std::endl;
    std::cout << "Runtime Stack: " << std::endl;
    if(sp == -1){
        std::cout << "empty" << std::endl;
    }
    else{
        for (int i = sp; i >= 0; i--){
            std::cout << rstack[i].dtype << std::endl;
        }
    }

    std::cout << "FP SP: " << fpsp << std::endl;
    std::cout << "Frame Pointer Stack: " << std::endl;
    if(fpsp == -1){
        std::cout << "empty" << std::endl;
    }
    else{
        for (int i = fpsp; i >= 0; i--){
            std::cout << fpstack[i] << std::endl;
        }
    }
}
