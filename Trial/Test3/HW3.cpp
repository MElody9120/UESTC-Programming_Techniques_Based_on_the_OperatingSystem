#include <fcntl.h>
#include <iostream>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>

using namespace std;

// 输出指定文件信息函数
int outputLs(string str_name);

int main(int argc, char* argv[])
{
    string open_dir;
    string str2;

    switch (argc){
     // 缺省文件名 默认当前目录
    case 1:             
        open_dir = "./";
        break;

    case 2:                
     // 带文件名 第一个参数
        str2 = (string)argv[1];
        outputLs(str2);     
        return 0;      
        break;

    default:
        cout << "Input error!" << endl;
        return 0;
        break;
    }

     // 如果是当前目录
    DIR *dir = opendir(open_dir.c_str());
    
    if(dir == 0){
        cout << "No this directory!" << endl;
        return 0;
    }

     // 循环遍历当前目录文件
    for(;;){
        struct dirent *pentry = readdir(dir);
        if(pentry == 0)
            break;

        // 特殊文件. .. 处理
        if(strcmp(pentry->d_name, ".") == 0) 
            continue;

        if(strcmp(pentry->d_name, "..") == 0)
            continue;

        string str1 = pentry->d_name;         
        //cout << str1 << endl;     // test
        outputLs(str1);  
    }

    closedir(dir);
    return 0;
}

int outputLs(string str_name){
    struct stat status;
    int ret = stat(str_name.c_str(), &status);

    if(ret == -1){
        cout << "No this file!" << endl;
        return 0;
    }
    
    char perms[11] = {0};
    // 存储文件类型和访问权限

    // 判断文件类型
    switch(status.st_mode & S_IFMT){
        case S_IFLNK: // 链接文档
            perms[0] = 'l'; 
            break;
        case S_IFDIR:   // 目录
            perms[0] = 'd'; 
            break;
        case S_IFREG:   // 文件
            perms[0] = '-'; 
            break;
        case S_IFBLK: // 可供储存的接口设备
            perms[0] = 'b'; 
            break;
        case S_IFCHR:   // 串行端口设备
            perms[0] = 'c'; 
            break;
        case S_IFSOCK:  // sock文件
            perms[0] = 's'; 
            break;
        case S_IFIFO:   // 命令管道文件
            perms[0] = 'p'; 
            break;
        default:   // UNDEFINE
            perms[0] = '?'; 
            break;
    }

    // 所有人权限
    perms[1] = (status.st_mode & S_IRUSR) ? 'r' : '-';
    perms[2] = (status.st_mode & S_IWUSR) ? 'w' : '-';
    perms[3] = (status.st_mode & S_IXUSR) ? 'x' : '-';
    
    // 所有组权限
    perms[4] = (status.st_mode & S_IRGRP) ? 'r' : '-';
    perms[5] = (status.st_mode & S_IWGRP) ? 'w' : '-';
    perms[6] = (status.st_mode & S_IXGRP) ? 'x' : '-';
    
    // 其他人权限
    perms[7] = (status.st_mode & S_IROTH) ? 'r' : '-'; 
    perms[8] = (status.st_mode & S_IWOTH) ? 'w' : '-';
    perms[9] = (status.st_mode & S_IXOTH) ? 'x' : '-';

     // 硬链接计数
    int linkNum = status.st_nlink;
    
    // 文件所有者
    char* fileUser = getpwuid(status.st_uid)->pw_name;
    
    // 文件所属组
    char* fileGrp = getgrgid(status.st_gid)->gr_name;
    
    // 文件大小
    int fileSize = (int)status.st_size;
    
    // 修改时间
    char* time = ctime(&status.st_mtime);                 
    char mtime[512] = {0};
    strncpy(mtime, time, strlen(time)-1);

     // 格式化输出
    cout << perms << " " ;               
    cout << linkNum << " ";
    cout << fileUser << " ";
    cout << fileGrp << " ";
    cout << fileSize << " ";
    cout << mtime << " ";
    cout << str_name <<  endl; 

    return 0;
}