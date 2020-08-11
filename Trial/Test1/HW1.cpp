#include <fcntl.h>
#include <iostream>
#include <errno.h>
#include <unistd.h>

using namespace std;

int main()
{
    char buf[10];

    // 打开文件,设置为O_APPEND
    int fd = open("test1.txt", O_RDWR | O_APPEND); 
    if(fd == -1){
        cout << "open error" << endl;
        return 0;
    }

    off_t CurrenPosition;
    CurrenPosition = lseek(fd, 0, SEEK_CUR);     
    // 打开文件后，获取当前文件偏移量
    cout << "After open the file offset :" << CurrenPosition << endl;

    // 改变当前偏移量，+5
    if(lseek(fd, 5, SEEK_CUR) == -1){
        cout << "lseek error" << endl;
        return 0;
    }
    // 获取当前偏移量，判断是否可以改变偏移量
    CurrenPosition = lseek(fd, 0, SEEK_CUR);
    cout << "After change file offset:" << CurrenPosition << endl; 

     // 获取写入前的偏移量
    CurrenPosition = lseek(fd, 0, SEEK_CUR);
    cout << "Before write file offset:" << CurrenPosition << endl; 

    for(int i=0;i < 10;i++){
        buf[i] = 't';
    }
    // 写入10个数据
    if(write(fd, buf, 10) != 10){
        cout << "Write error!" << endl;
        return 0;
    }

    CurrenPosition = lseek(fd, 0, SEEK_CUR);  // 获取写入后的偏移量
    cout << "After write file offset:" << CurrenPosition << endl; 
     // 改变当前偏移量为5
    if(lseek(fd, 5, SEEK_SET) == -1){
        cout << "lseek error" << endl;
        return 0;
    }

    // 获取读取前偏移量
    CurrenPosition = lseek(fd, 0, SEEK_CUR);
    cout << "Before read file offset:" << CurrenPosition << endl; 

    // 读取3个字符
    if(read(fd, buf, 3) == -1){
        cout << "Read error!" << endl; //error warning
        return 0;
    }
     // 输出3个字符
    for(int i=0;i<3;i++){
        cout << buf[i] ;
    }
    cout << endl;

     // 获取读取后偏移量
    CurrenPosition = lseek(fd, 0, SEEK_CUR);
    cout << "After read file offset:" << CurrenPosition << endl; 

    // 关闭文件
    if(close(fd) == -1){
        cout << "close error" << endl;
    }

    return 0;
}
