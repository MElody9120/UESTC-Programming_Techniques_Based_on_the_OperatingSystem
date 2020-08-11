#include <fcntl.h>
#include <iostream>
#include <dirent.h>
#include <string.h>

using namespace std;

// 递归读取函数
void recursiveRead(string str_name,int level);

int main(int argc,char* argv[])
{
    string open_dir;
    switch (argc) {
    // 缺省目录参数，默认 ./ 目录
    case 1:
        open_dir = ".";
        break;
    // 带参数：目录的路径
    case 2:
        open_dir = (string)argv[1];
        break;
     // 参数格式输入不正确，错误处理
    default:              
        cout << "Input error!" << endl;
        return 0;
        break;
    }
    // 打开目录
    DIR *dir = opendir(open_dir.c_str());    

    if(dir == 0)       {
        cout << "No this directory!" << endl;
        return 0;
    }
    cout << "|" << endl;

    // 循环读取目录
    for(;;){
        struct dirent *pentry = readdir(dir);
        // 空指针退出循环
        if(pentry == 0){
             break;
        }                             

        // 特殊文件处理
        if(strcmp(pentry->d_name,".") == 0){
            continue;
        }          

        if(strcmp(pentry->d_name,"..") == 0){
            continue;
        }

         // 如果是目录类型
        if(pentry->d_type == 4){
            string str = open_dir;
            str += "/";
            str += pentry->d_name;
            cout << "|-" ;
            cout << pentry->d_name << "(目录)" << endl;   
            // 调用递归函数，递归读取该目录下级目录
            recursiveRead(str, 1);
        }

        // 不是目录类型，输出文件名
        if(pentry->d_type != 4)  {
            cout << "|-" ;
            cout << pentry->d_name << endl;
        }

    }

    // 关闭文件
    closedir(dir);
    return 0;
}

void recursiveRead(string str_name,int level){
    //打开目录
    DIR *dir = opendir(str_name.c_str());      

    if(dir == 0)       {
        cout << "RecursiveRead error!" << endl;
    }

    cout << "|";
    for(int i=0;i<level;i++){
        cout << "  ";
    }
    cout << "|" << endl;

     // 循环读取目录
    for(;;){
        struct dirent *pentry = readdir(dir);
        // 空指针退出循环
        if(pentry == 0)                                  
            break;

        // 特殊文件处理
        if(strcmp(pentry->d_name,".") == 0)                 
            continue;

        if(strcmp(pentry->d_name,"..") == 0)
            continue;

        cout << "|";
        for(int i=0;i<level;i++){
            cout << "  ";
        }

        // 如果是目录类型
        if(pentry->d_type == 4){
            string str = str_name;
            str += "/";
            str += pentry->d_name;
            cout << "|-" ;
            cout << pentry->d_name << "(目录)" << endl;   
            recursiveRead(str, level+1);
            // 递归读取该目录下级目录
        }

        // 不是目录类型，输出文件名
        if(pentry->d_type != 4){
            cout << "|-" ;
            cout << pentry->d_name << endl;
        }

    }

    // 关闭文件
    closedir(dir);
}

