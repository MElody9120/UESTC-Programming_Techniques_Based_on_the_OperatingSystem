#include <dlfcn.h>
#include <string.h>
#include <iostream>
#include<stdlib.h>
#include "pluginCounter.h"

using namespace std;

int FuncID = 0;

void dl_help(vector<string> vStrNames);                         // 路径里所有动态库里执行help()
void dl_printSC(vector<string> vStrNames, vector<int> vIntID);  // 根据FuncID决定那个动态库执行printSC()

int main(int argc, char *argv[])
{
    // 检查参数
    if (argc != 2)
    {
        cout << "Please input correct argc!" << endl;
        return 0;
    }

    vector<string> vStrNames;  // 用于存放所有的插件路径
    vector<int> vIntID;        // 用于存放所有的插件ID
    pc_t pc;                   // 实例化一个插件遍历器

    // 获取plunin/里所有插件信息
    if (pc.getPluginINFO() == false)
    {
        cout << "Get plugin names error!" << endl;
        return 0;
    }

    vStrNames = pc.getVNames();
    vIntID = pc.getVID();

    // 执行help()
    if (strcmp(argv[1], "help") == 0)
    {
        dl_help(vStrNames);
    }
    // 根据ID选择对应插件进行print
    else
    {
        FuncID = atoi(argv[1]); // 转换整型
        dl_printSC(vStrNames, vIntID);
    }

    return 0;
}

// 路径里所有动态库里执行help()
void dl_help(vector<string> vStrNames)
{
    // 遍历所有插件执行help()
    for (int i = 0; i < vStrNames.size(); i++)
    {
        // 打开动态库
        void *handle = dlopen(vStrNames[i].c_str(), RTLD_LAZY);
        if (handle == 0)
        {
            cout << "dlopen error in help()!" << endl;
            return;
        }

        // 映射函数
        typedef void (*FUNC_HELP)();
        FUNC_HELP dl_help = (FUNC_HELP)dlsym(handle, "help");
        if (dl_help == 0)
        {
            cout << "dlsym error!" << endl;
            return;
        }

        // 执行函数
        (dl_help)();

        // 关闭动态库
        dlclose(handle);
    }
}

// 根据FuncID决定那个动态库执行printSC()
void dl_printSC(vector<string> vStrNames, vector<int> vIntID)
{
    // 遍历动态库
    for (int i = 0; i < vStrNames.size(); i++)
    {
        // 遇到要执行的动态库
        if (vIntID[i] == FuncID)
        {
            // 打开动态库
            void *handle = dlopen(vStrNames[i].c_str(), RTLD_LAZY);
            if (handle == 0)
            {
                cout << "dlopen error in printSC()!" << endl;
                return;
            }

            // 映射函数
            typedef void (*FUNC_PRINTSC)();
            FUNC_PRINTSC dl_printsc = (FUNC_PRINTSC)dlsym(handle, "printSC");
            if (dl_printsc == 0)
            {
                cout << "dlsym error!" << endl;
                return;
            }

            // 执行函数
            (dl_printsc)();

            // 关闭动态库
            dlclose(handle);
        }
    }
}
