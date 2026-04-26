#include "simple++.h"

int main() {
    loadAircraft("Simple++"); //打开Aircraft
    ditch myDitch;//创建一个信号槽
    myDitch.name="Ditch";//给信号槽命名
//    var var1;
    myDitch.formula={ //给信号槽写脚本
        "IAS > 3.6 ? 1 : 0",
        "sin(PitchAngle)",
        "clamp01(RollRate)",
        "VerticalG",
        "114514",
//        var1.assignment(1),
        _(GET,"",""),
        _(IF,"11","1"),
        _(IFELSE,"","",""),
    };
    myDitch.apply();//应用变化
    saveAircraft(CREATE);//保存更改
    ditch myDitch2[234];
    myDitch.F={"1"};
    return 0;
}


// #include "simple++.h"
//
// int main() {
//     ditch procedure;
//     procedure.name = "p1";
//     if (procedure.apply());
//     cout<<resolvePath("114514")<<endl;
//     loadAircraft("Aircraft");
//
//     int frequency=100;
//     int step = 100/frequency;
//     string name="123";
//     procedure.frequency=20;
//    // procedure.pause = "114514";
//     procedure.formula={
//     "1","2","3","4","5","6","7","8","9",
//     };
//     if (procedure.apply());
//
//     vector<int> p;
//     p.push_back(114514);
//     printf("%d",p[0]);
//     saveAircraft(CREATE);
// }
//

