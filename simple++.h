#ifndef SIMPLE___LIBRARY_H
#define SIMPLE___LIBRARY_H

#include <iostream>
#include <fstream>
#include <functional>
#include <windows.h>
#include <sstream>
#include <shlobj.h>
#include <cmath>

using namespace std;

#define findout(text) find(text) != string::npos //发现
#define REPLACE false
#define CREATE true


void hello();
class ditch {
private:
    unsigned short step;
    string interpreter(unsigned short species);
    string variableXml;
public:
    ditch();
    ~ditch();
    //string interpreter(unsigned short species);//记得扔回private，测试的时候暂时拿出来
    string name,pause="0";
    unsigned short frequency;
    vector<string> formula;
    bool apply();

};

bool loadAircraft(const string& filename),saveAircraft(bool replaceOrCreate);

string resolvePath(const string& source),getDefaultPath();

#endif // SIMPLE___LIBRARY_H