//
// Created by ermakoy on 21.09.17.
//

#ifndef LAB1FIX_INIPARSER_H
#define LAB1FIX_INIPARSER_H

#include <fstream>
#include <iostream>
#include <map>
#include "exeptions.h"

using namespace std;

class InIParser {
public:
    InIParser(string filename) throw(exc_io);

    ~InIParser();


    void LetTheCarnageBegins();

    void TestPrint();

    string getStrValue(const string &, const string &) const throw(exc_param);

    int getIntValue(const string &, const string &) const throw(exc_param);

    float getFloatValue(string, string) const throw(exc_param);

private:
    ifstream fin;
    map<string, map<string, string>> storage;
    string section;

    string DeleteCommentary(string) const;

    void ParseIt(string);


    bool section_name_exist(string) const throw(exc_param);

    bool param_exist(string, string) const throw(exc_param);
};

#endif //LAB1FIX_INIPARSER_H
