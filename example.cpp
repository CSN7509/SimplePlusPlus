#include "simple++.h"

int main() {
    loadAircraft("Aircraft");
    ditch myDitch;
    myDitch.name="Ditch";
    myDitch.formula={
        "IAS > 3.6 ? 1 : 0",
        "sin(PitchAngle)",
        "clamp01(RollRate)",
        "VerticalG",
        "114514"
    };
    myDitch.apply();
    saveAircraft(CREATE);
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

