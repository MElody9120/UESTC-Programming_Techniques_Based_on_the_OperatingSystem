#include <iostream>

using namespace std;

const int FUNC_ID = 1;      // 插件ID

extern "C" void printSC()   // 打印 "Hello China!"
{
    cout << "Hello China!" << endl;
}

extern "C" void help()      // 打印帮助信息
{
    cout << "Function ID: " << FUNC_ID << " - This function is used to print HC" << endl;
}

extern "C" int getID()      // 返回插件ID
{
    return FUNC_ID;
}
