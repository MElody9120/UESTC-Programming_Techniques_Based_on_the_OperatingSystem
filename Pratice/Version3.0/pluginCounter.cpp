#include <iostream>
#include <dirent.h>
#include <string.h>
#include <dlfcn.h>
#include "pluginCounter.h"

pluginCounter::pluginCounter() {}
pluginCounter::~pluginCounter() {}

bool pc_t::getPluginINFO()
{
    DIR *dp;
    struct dirent *dirp;

    // 打开plugin/
    dp = opendir("./plugin/");
    if (dp == 0)
    {
        cout << "open dir error!" << endl;
        return false;
    }

    // 遍历plugin/下所有的文件
    while ((dirp = readdir(dp)) != NULL)
    {
        // 忽略"."和".."两个文件
        if ((strcmp(dirp->d_name, ".")) == 0 || (strcmp(dirp->d_name, "..")) == 0)
        {
            continue;
        }

        // 获取插件路径
        string str = "./plugin/";
        str += dirp->d_name;
        vStrNames.push_back(str);

        /* 通过调用动态库里的getID()来获取插件ID */
        // 打开动态库
        void *handle = dlopen(&str[0], RTLD_LAZY);
        if (handle == 0)
        {
            cout << "dlopen error in pc!" << endl;
            return 0;
        }

        // 映射函数
        typedef int (*FUNC_GETID)();
        FUNC_GETID dl_getid = (FUNC_GETID)dlsym(handle, "getID");
        if (dl_getid == 0)
        {
            cout << "dlsym error!" << endl;
            return 0;
        }

        int Func_ID = (dl_getid)(); // 调用函数
        vIntID.push_back(Func_ID);
        dlclose(handle);
    }

    // 关闭目录
    closedir(dp);

    return true;
}

vector<string> pc_t::getVNames()
{
    return vStrNames;
}

vector<int> pc_t::getVID()
{
    return vIntID;
}
