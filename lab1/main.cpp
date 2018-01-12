#include <iostream>
#include "InIParser.h"

int main() {
    try{
        InIParser parser("lab01_input_correct_09.ini");
        parser.LetTheCarnageBegins();
        parser.TestPrint();
        cout<<parser.getFloatValue("DEMODS","BufferLenSeconds")<<endl;
        cout<<parser.getIntValue("COMMON","ListenTcpPort")<<endl;
        cout<<parser.getStrValue("DEMODS","FileName")<<endl;
        cout<<parser.getFloatValue("1","1")<<endl;
    }catch(exc_io& e){
        cout<<e.what();
    }catch(exc_param& e){
        cout<<e.what();
    }
    return 0;
}