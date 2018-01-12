//
// Created by  ermakoy on 21.09.17.
//

#include "InIParser.h"
using namespace std;

void InIParser::ParseIt(string correct) {
    if (correct[0] == '[') {
        section.clear();
        for (int i = 1; i < correct.find(']'); ++i) {
            section += correct[i];
        }
    } else {
        unsigned long equality = correct.find('=');
        if (equality != -1) {
            string ParamName, ParamValue;
            ParamName = correct.substr(0, equality);
            ParamValue = correct.substr(equality + 1, correct.length() - equality);
            storage[section][ParamName] = ParamValue;
        } else {
            return;
        }
    }
}

string InIParser::DeleteCommentary(string buf) const {
    string correctBuf;
    unsigned long separator = buf.find(';');
    if (separator == -1) separator = buf.length();
    for (int i = 0; i < separator; ++i) {
        if (buf[i] != ' ' and buf[i] != '\r') correctBuf += buf[i];
    }
    return correctBuf;
}

void InIParser::LetTheCarnageBegins() {
    while (!fin.eof()) {
        string buf;
        getline(fin, buf);
        buf = DeleteCommentary(buf);
        if (buf.length() != 0) {
            ParseIt(buf);
        }
    }
    fin.close();
}

InIParser::InIParser(string filename) throw(exc_io) {
    fin.open(filename);
    if (!fin.good()) throw exc_io();
}

InIParser::~InIParser() {

}

void InIParser::TestPrint() {
    for (auto &s : storage) {
        cout << "[" << s.first << "]" << endl;
        for (auto &p : s.second) {
            cout << p.first << "=" << p.second << endl;
        }
        cout << endl;
    }
}

string InIParser::getStrValue(const string &section_name, const string &param) const throw(exc_param) {
    if (!section_name_exist(section_name)) {
        throw ("section");
    } else if (!param_exist(section_name, param)) {
        throw ("param");
    }
    return storage[section_name][param];
}

int InIParser::getIntValue(const string &section_name, const string &param) const throw(exc_param) {
    return stoi(getStrValue(section_name, param));
}

float InIParser::getFloatValue(string section_name, string param) const throw(exc_param) {
    return stof(getStrValue(section_name, param));
}

bool InIParser::section_name_exist(string section_name) const throw(exc_param) {
    bool is_section_name = true;
    if (storage.find(section_name) == storage.end()) {
        is_section_name = false;
        throw exc_param();
    }
    return is_section_name;
}

bool InIParser::param_exist(string section_name, string param) const throw(exc_param) {
    if (section_name_exist(section_name) && storage[section_name].find(param) != storage[section_name].end())
        return true;
    else {
        throw exc_param();
    }
}