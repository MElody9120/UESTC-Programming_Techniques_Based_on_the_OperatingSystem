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
    }

    // 关闭目录
    closedir(dp);

    return true;
}

vector<string> pc_t::getVNames()
{
    return vStrNames;
}
