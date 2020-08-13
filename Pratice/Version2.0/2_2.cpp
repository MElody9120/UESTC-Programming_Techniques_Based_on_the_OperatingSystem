#include <iostream>
#include <dlfcn.h>
#include <dirent.h>
#include <string>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

using namespace std;

bool printPlugin(DIR *pDir);    // 输出给定目录下的所有插件

int main()
{
    // 用于打开目录
    DIR *pDir;

    // 打开目录
    pDir = opendir("./plugin");
    if (pDir == NULL)
    {
        cout << "Open dir error!" << endl;
        return 0;
    }

    // 更改工作目录至plugin/下
    chdir("./plugin/");

    // 逐个输出plugin/下的插件
    if (printPlugin(pDir) == false)
    {
        cout << "Print plugin error!" << endl;
    }

    // 切换目录回上一级目录（这里不重要）
    chdir("../");

    // 关闭目录
    if ((closedir(pDir)) == -1)
    {
        cout << "Close dir error!" << endl;
        return 0;
    }

    return 0;
}

bool printPlugin(DIR *pDir)
{
    // 用于打开目录项
    struct dirent *pDirent;

    while ((pDirent = readdir(pDir)) != NULL)
    {
        // 忽略当前目录和父目录
        if ((strcmp(pDirent->d_name, ".")) == 0 || (strcmp(pDirent->d_name, "..")) == 0)
        {
            continue;
        }

        // 打开动态链接库
        string str = "./";
        str += (string)(pDirent->d_name);
        void *handle = dlopen(&str[0], RTLD_LAZY);

        // 如果打开失败
        if (0 == handle)
        {
            cout << "dlopen error: " << dlerror() << endl;
            return false;
        }

        // 映射动态链接库的函数
        typedef void (*Fun)();

        Fun f1 = (Fun)dlsym(handle, "printSC");

        // 如果映射失败
        if (0 == f1)
        {
            cout << "f1 error" << endl;
            char *str = dlerror();
            cout << str << endl;
            return false;
        }

        // 调用
        (*f1)();

        // 卸载动态链接库
        dlclose(handle);
    }

    return true;
}