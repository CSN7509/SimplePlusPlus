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

//saveAircraft()
#define REPLACE false
#define CREATE true

//logic

#define N name
#define F formula
#define FQ frequency
#define A assignment

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
//冷冻
// //想法1：每个var也会有一个简单的计时器(SubTimer)用于计算何时赋值，该计时器从模拟开始便开始计时，以最后一次赋值时刻的下一个时刻为结束点（自动处理），其中，对于frequency不同的情况下，需要进行换算。
// //想法2：每个var均以主计时器(Timer)为计时器，在模板var、ditch对锁存器var赋值时，传入与计时起点的最小差值（也就是此时Timer的值），随后以此最小差值为整数倍数寻找随后的赋值时刻（取模，参考状态机，但是只保留锁存功能）。
// //想法3(差点选中)：把赋值命令的时间点（由于为了方便，赋值命令在S++里面是写在ditch.formula里面的，但是由于funky tree不支持赋值，因此在FT赋值行将会使用上一时刻的输出值，而S++则会把该变量输出值所在SubTimer_Ditch时刻作为var的赋值触发器）
// //想法4(基于想法3)：在Ditch
// //注意，FT辅助变量均需要"_"前缀
// class var {
//     private:
//     string interpreter(unsigned short species);
//     string assignmentTrigger;
//     public:
//     var();
//     ~var();
//     string name;
//     string value;
//     //预计会在模板ditch、var的formula中嵌入但不在该模板ditch、var中给值（延续上一时刻的值），只会记录当前step并将此时模板ditch、var的值赋予这个var，考虑到sp最大精度只有八位，且一般数据不会太大，节省内存起见暂时采用short
//     string assignment(short value);//在此刻给锁存器var赋其他值
//     string assignment();//直接将模板ditch、var的值在此刻赋给锁存器var,等效myVar.assignment(myDitch.formula[n-1])
//     bool apply();
// };
#define CONTINUE 0
#define BROADCAST 1
#define GET 2
#define IF 3
#define IFELSE 4
string _(int operation),_(int operation,string formula1),_(int operation,string formula1,string formula2),_(int operation,string formula1,string formula2,string formula3);

bool loadAircraft(const string& filename),saveAircraft(bool replaceOrCreate);

string resolvePath(const string& source),getDefaultPath();

inline string If();


#endif // SIMPLE___LIBRARY_H