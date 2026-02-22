#include "simple++.h"

int main() {
    loadAircraft("Aircraft"); //打开Aircraft
    ditch myDitch;//创建一个信号槽
    myDitch.name="Ditch";//给信号槽命名
    myDitch.formula={ //给信号槽写脚本
        "IAS > 3.6 ? 1 : 0",
        "sin(PitchAngle)",
        "clamp01(RollRate)",
        "VerticalG",
        "114514"
    };
    myDitch.apply();//应用变化
    saveAircraft(CREATE);//保存更改
    return 0;
}
