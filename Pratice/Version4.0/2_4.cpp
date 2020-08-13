#include "pluginController.h"
#include "pluginCounter.h"
#include <string.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

int main(int argc, char *argv[])
{
    // 检查参数 
    if (argc != 2)
    {
        cout << "Please input correct argc!" << endl;
        return 0;
    }
    
    // 实例化一个插件控制器
    pct_t pc;
    
    // 初始化插件控制器
    if (pc.InitController() == false)
    {
        cout << "Init plugin controller error!" << endl;
        return 0;
    }   

    // 执行help()
    if (strcmp(argv[1], "help") == 0)
    {
        if (pc.ProcessHelp() == false)
        {
            cout << "ProcessHelp() error!" << endl;
            return 0;
        }
    }
    // 根据ID选择对应插件进行print
    else
    {
        int FuncID = atoi(argv[1]); // 转换整型

        pc.ProcessPrint(FuncID);
    }

    // 卸载所有的动态库
    pc.UninitController();
    
    return 0;
}
