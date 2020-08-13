#include <dlfcn.h>
#include <string>
#include <vector>
#include <iostream>
#include "IPrintPlugin.h"
#include "pluginCounter.h"
#include "pluginController.h"

using namespace std;

pluginController::pluginController(/* args */)
{
}

pluginController::~pluginController()
{
}

bool pct_t::InitController(void)
{
    pc_t plugin_counter;                // 实例化一个插件路径遍历器
    vector<string> vStrPluginNames;     // 实例化一个容器用于存放所有插件的路径
    plugin_counter.getPluginINFO();     // 获取plugin/下所有的插件路径

    // 目录若为空则返回错误
    vStrPluginNames = plugin_counter.getVNames();
    if (vStrPluginNames.empty())
    {
        cout << "Get plugin path error!" << endl;
        return false;
    }

    // 遍历所有动态链接库
    for (unsigned int i = 0; i < vStrPluginNames.size(); i++)
    {
        // 定义映射函数
        typedef int (*PLUGIN_CREATE)(ipp_t**);
        PLUGIN_CREATE CreateProc;

        ipp_t *pPlugin = NULL;

        // 打开动态链接库
        void *handle = dlopen(vStrPluginNames[i].c_str(), RTLD_LAZY);

        // 打开正确
        if (handle != NULL)
        {
            v_pluginHandle.push_back(handle);  // 存入句柄

            CreateProc = (PLUGIN_CREATE)dlsym(handle, "createObj");  // 映射函数

            // 映射成功
            if (CreateProc != NULL)
            {
                (CreateProc)(&pPlugin);  // 创建cpp_t（插件类）

                if (pPlugin != NULL)
                {
                    v_plugin.push_back(pPlugin); // 存入插件
                }
            }
        }
        // 打开失败
        else
        {
            cout << "dlopen() error info: " << dlerror() << endl; // 输出错误信息
            return false;
        }
        
        
    }
    
    return true;
}

bool pct_t::UninitController(void)
{
    // 逐一关闭动态链接库
    for (unsigned int i = 0; i < v_pluginHandle.size(); i++)
    {
        dlclose(v_pluginHandle[i]);
    }

    return true;
}

bool pct_t::ProcessPrint(int FuncID)
{
    // 遍历动态链接库，FuncID匹配上就输出
    for (unsigned int i = 0; i < v_plugin.size(); i++)
    {
        if (v_plugin[i]->getID() == FuncID)
        {
            v_plugin[i]->printSC();
            break;
        }       
    }
    
    return true;
}

bool pct_t::ProcessHelp(void)
{
    // 遍历动态链接库输出help()
    for (unsigned int i = 0; i < v_plugin.size(); i++)
    {
        v_plugin[i]->help(); 
    }

    return true;
}