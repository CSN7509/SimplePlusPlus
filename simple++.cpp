#include "simple++.h"
//下一步 : 定义var类，用于批量生成、编辑单行非线性变量，同样有apply()，


bool voidVariable=false,generalVariables=true,aircraftLoaded=false,mainTimerGenerated=false,emptyGV=true;
short deleteLineNumberGV=-1,deleteLineNumberAS=-1,deleteLineNumberTH=-1;
inline vector<string> globalVariablesName,globalVariablesFormula;//[0]纵列表示name，[1]纵列formula，横行表示 name | formula，
string filePath;
//目前只支持操作单一飞机，后面会修复

ditch::ditch():step(5),frequency(20) {

}

ditch::~ditch() = default;

string ditch::interpreter(unsigned short species) { //0 为主计时器 1为副计时器 2为副计时器控制器 3为状态机
    step=floor(100/frequency);
    switch (species) {
        case 0://命名为_mainTimer，至少在本机上运行，Time的最小变动数位为10ms，低于10ms一般不动，因其原单位为s，乘100后单位变为10ms
            return "floor(Time*100)";//该值为100时，时间为1s
        case 1://副计时器命名为_name_subTimer，故副计时器控制器命名为_name_subTimer_controller 副计时器控制器为0的时归零 为1时正常计时 为2时暂停
            return "_" + name + "_subTimer_controller = 1 ? (_mainTimer % " + to_string(step) + " = 0 ? " + "_" + name + "_subTimer+1 : _" + name + "_subTimer) : (_" + name + "_subTimer_controller = 0 ? 0 : _" + name + "_subTimer)";
        case 2://控制器在计时器到达脚本尽头时归零，或在填写pause变量后暂停
            return "_" + name + "_subTimer >= " + to_string(formula.size()) + " ? 0 : (" + pause +" ? 2 : 1)" ;
        case 3://状态机+(_name_subTimer=0 ? 1 : 0)*formula[0]+(_name_subTimer=1 ? 1 : 0)*formula[1]+(_name_subTimer=2 ? 1 : 0)*formula[2]+...+(_name_subTimer=n ? 1 : 0)*formula[n]
            string state;
            for (unsigned short i=0;i<formula.size();i++)
                state+="+((_"+name+"_subTimer = " + to_string(i) + " ? 1 : 0) * ("+formula[i]+"))";
            state.erase(0,1);
            return state;
    }
}


bool ditch::apply() {
    if (name[0] == ' ' || name.empty()) {
        cerr<<"[错误] 不接受开头存在空格的字符串或空的字符串作为槽名称"<<endl<<"[ERR] STRING with a SPACE on TOP or Empty STRING is NOT ACCEPTED as a DITCH NAME"<<endl;
        return false;
    }if (!aircraftLoaded) {
        cerr<<"[错误] Aircraft 未装载"<<endl<<"[ERR] Aircraft NOT LOADED."<<endl;
        return false;
    }if (frequency>60)
        clog<<"[警告] 频率高于模拟帧率(60Hz)会导致脚本运行不正常"<<endl<<"[WRN] It's not recommended to set frequency bigger than simulation FPS that the script will not run well."<<endl;
    //1.生成副计时器，如_name_subTimer(主计时器在saveAircraft()里面直接写进xml ),根据formula.size()决定最大执行step数,根据name.frequency决定每个step间隔时间
    //2.生成状态机，如 name
    if (!mainTimerGenerated) {//生成主计时器
        cout<<"[日志] ["<<name<<"]生成主计时器..."<<endl<<"[LOG] ["<<name<<"]Generating Main Timer..."<<endl;
        globalVariablesName.push_back("_mainTimer");
        globalVariablesFormula.push_back(interpreter(0));
        mainTimerGenerated=true;
    }
    cout<<"[日志] ["<<name<<"]生成副计时器..."<<endl<<"[LOG] ["<<name<<"]Generating Sub-Timer..."<<endl;
    globalVariablesName.push_back("_"+name+"_subTimer");//生成副计时器
    globalVariablesFormula.push_back(interpreter(1));

    cout<<"[日志] ["<<name<<"]生成副计时器控制器..."<<endl<<"[LOG] ["<<name<<"]Generating Sub-Timer Controller..."<<endl;
    globalVariablesName.push_back("_"+name+"_subTimer_controller");//生成副计时器控制器
    globalVariablesFormula.push_back(interpreter(2));

    cout<<"[日志] ["<<name<<"]生成状态机..."<<endl<<"[LOG] ["<<name<<"]Generating State Machine..."<<endl;
    globalVariablesName.push_back(name);//生成状态机
    globalVariablesFormula.push_back(interpreter(3));


    cout<<endl<<"[OK] ["<<name<<"]applied."<<endl<<endl;
    return true;
}



string getDefaultPath() {
    char path[MAX_PATH];
    SHGetFolderPathA(nullptr, CSIDL_LOCAL_APPDATA, nullptr, 0, path);//实际存储在localow
    string realPath=string(path);
    realPath.replace(realPath.find("Local"), 5, "LocalLow");
    return string(realPath) + R"(\Jundroo\SimplePlanes\AircraftDesigns\)";
}

string resolvePath(const string& source) {
    if (source.findout('/') || source.findout(':') || source.findout('\\'))
        return source;
    if (source.findout(".xml"))
        return getDefaultPath()+source;
    return getDefaultPath()+source+".xml";
}

bool loadAircraft(const string& filename) {
    const string path = resolvePath(filename);
    cout<<"[日志] 文件储存在 "<<path<<endl<<"[LOG] File stored at "<<path<<endl;
    ifstream file(path.c_str());

    if (!file.is_open()) {
        cerr<<"[错误] 文件打开失败"<<endl<<"[ERR] FAILED to OPEN FILE"<<endl;
        return false;
    }

    string line;
    bool legalAircraft[5]={false};
    cout<<"[日志] 正在验证文件完整性..."<<endl<<"[LOG] Verifying file integrity..."<<endl;
    for (short lineNum=0;getline(file,line);++lineNum) {
        if (line.findout("<Aircraft name=")) {
            legalAircraft[0] = true;
            cout<<"[日志] 找到<Aircraft>标签于第 "<<lineNum<<"行"<<endl<<"[LOG] <Aircraft> label was found in line"<<lineNum<<endl;
        }
        if (line.findout("</Aircraft>")) {
            legalAircraft[1] = true;
            cout<<"[日志] 找到</Aircraft>标签于第 "<<lineNum<<"行"<<endl<<"[LOG] </Aircraft> label was found in line"<<lineNum<<endl;
        }
        if (line.findout("<Variables")) {
            legalAircraft[2] = true;
            cout<<"[日志] 找到<Variables>标签于第 "<<lineNum<<"行"<<endl<<"[LOG] <Variables> label was found in line"<<lineNum<<endl;
            if (line.findout("<Variables />")) {
                if (generalVariables && lineNum<=5){  //在找到的第一个做标记，这个是全局变量，其他的都是组件自己的，先不做标记，这些都放后面做
                    voidVariable=true;
                    deleteLineNumberGV=lineNum;//要在save()的时候清除这一行，改为  <Variables>，最后在apply()里面翻译完的一堆变量的最末尾加入</Variables>
                    generalVariables=false;
                    cout<<"[日志] 发现全局Variable Settings "<<endl<<"[LOG] Global Variable Setting Found."<<endl;
                }
                cout<<"[日志] 该Aircraft的Variable Settings为空 "<<endl<<"[LOG] The variable settings of this aircraft is empty."<<endl;
            }else {
                //cout<<"[日志] 正在记录原有变量位置"<<endl<<"[LOG] Marking the position of original variables"<<endl;
                cerr<<"[错误] 暂不支持Variable Settings不为空的Aircraft"<<endl<<"[ERR] Aircraft with EMPTY Variable Settings is temporarily NOT SUPPORTED."<<endl;
                emptyGV=false;
                //这个部分以后再做,Nya~
                return false;
            }
        }
        if (line.findout("<Assembly>")) {
            legalAircraft[3] = true;
            cout<<"[日志] 找到<Assembly>标签于第 "<<lineNum<<"行"<<endl<<"[LOG] <Assembly> label was found in line"<<lineNum<<endl;
        }
        if (line.findout("<Theme")) {
            legalAircraft[4] = true;
            cout<<"[日志] 找到<Theme>标签于第 "<<lineNum<<"行"<<endl<<"[LOG] <Theme> label was found in line"<<lineNum<<endl;
        }
    }
    //[0]、[1]文件无效 [2]无法写脚本 [3]无法改结构 [4]无法改主题，初期只做到写脚本就行
    bool legal=true;
    for (bool i : legalAircraft) legal*=i; //    for (unsigned short i=0;i<sizeof(legalAircraft)/sizeof(legalAircraft[0]);++i) legal*=legalAircraft[i];
    file.close();
    if (!legal) {
        cerr<<"[错误] 文件标签缺失"<<endl<<"[ERR] This file is LACK of important labels."<<endl;
        return false;
    }
    filePath=path;
    cout<<endl<<"[OK] 文件加载成功" <<path<<endl<<endl;
    aircraftLoaded=true;
    return true;
}

bool saveAircraft(bool replaceOrCreate) {//true为创建新文件，false为覆盖旧文件
    if (replaceOrCreate) {
        if (filePath.empty()) {
            cerr<<"[错误] Aircraft 未装载"<<endl<<"[ERR] Aircraft NOT LOADED."<<endl;
            return false;
        }
        ifstream inputFile(filePath);
        string newFilePath=filePath;
        newFilePath.replace(filePath.find(".xml"),4,"_fix.xml");
        ofstream outputFile(newFilePath);
        vector<string> lines;
        if (!inputFile.is_open()) {
            cerr<<"[错误] 输入流开启失败"<<endl<<"[ERR] Could NOT launch INPUT STREAM."<<endl;
            return false;
        }if (!outputFile.is_open()) {
            cerr<<"[错误] 输出流开启失败"<<endl<<"[ERR] Could NOT launch OUTPUT STREAM."<<endl;
            return false;
        }
        string iptLine; //边读边写↓ <Setter variable=name function=formula priority="0" />
        for (unsigned short lineN=0;getline(inputFile,iptLine);++lineN) {//for (string iptLine;getline(inputFile,iptLine);lines.push_back(iptLine));
            if (lineN==deleteLineNumberGV) {//反正不为空的话值为-1
                outputFile<<"  <Variables>"<<endl;
                cout<<"[日志] 正在写入全局变量..."<<endl<<"[LOG] Writing to global variable..."<<endl;
                for (unsigned short i=0;i<globalVariablesFormula.size();++i)
                    outputFile<<"<Setter variable=\""<<globalVariablesName[i]<<"\" function=\""<<globalVariablesFormula[i]<<"\" priority=\"0\" />"<<endl;
                outputFile<<"</Variables>"<<endl;
                continue;
            }outputFile<<iptLine<<endl;
            //暂时不需要下面的非空写入
            // if ((iptLine.findout("<Variables") || inGV) && !(iptLine.findout("</Variables>"))) {
            //     inGV=true;
            //     if (emptyGV) {
            //
            //         inGV=false;
            //     }
            //     else
            //         ;//判定是否存在于前五行
            //}
        }
    }else {
        //暂不支持覆盖
    }
    return true;
}

void hello() {
    std::cout << "Hello, World!" << std::endl;
}