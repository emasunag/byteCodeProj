//
// Created by Ethan Masunaga and daryl on 10/21/19.
//

#include <iostream>

int main(int argc, char **argv) {

    // rstack = vector that contains data items
    int sp = -1; //top of runtime stack

    //fpstack = first element in function stack frame
    int fpsp = -1; //top of frame stack

    int pc = 0; //contains address of next instruction
    //mem = array of bytes

    //Input refers to program memory
    //Run till we reach halt which is opcode (8 0's)
    //Runtime stack has all the variables in a vector
    //
    std::vector<unsigned int> memory; //initialize an empty vector of unsigned ints as memory
    std::vector //need one for rstack
    ifstream test_file(argv[1]); //open file to read

    if(!test_file)
    {
        std::cout << "File Failed to Open " <<endl;
    }
    test_file.seekg(ios::end);
    len = is.tellg(); //get length of file
    test_file.seekg (0, ios::beg); //go back to beginning of file

    test_file.read(memory,length);
    test_file.close()




}