#include <iostream>
#include <dlfcn.h>

using namespace std;

int main()
{
    // 打开动态链接库 
    void *handle = dlopen("./libTest.so", RTLD_LAZY);
    if (0 == handle)
    {
        cout << "dlopen error" << endl;
        return 0;
    }

    // 映射动态链接库的函数
    typedef void (*Fun)();

    Fun f1 = (Fun)dlsym(handle, "printSC");

    // 映射失败
    if (0 == f1)
    {
        cout << "f1 error" << endl;
        char *str = dlerror();
        cout << str << endl;
        return 0;
    }

    // 调用
    (*f1)();

    // 卸载动态链接库
    dlclose(handle);

    return 0;
}