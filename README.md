# UESTC-Progtamming_Techniques_Based_On_The_OperatingSystem
---
OH!~~~~~ OH ~ (:D

## 实验部分
Test1

讨论O_APPEND 对 lseek 函数的影响，在设置O_APPEND标志后，lseek 函数的对读写文件是否能像没有设置标志时一样修改

---
Test2

打印指定目录下所有的子目录与文件名的名称，并且不断递归访问子目录，显示子目录附属的目录与文件的名称

---
Test3

实现  `ls -l` 的基本功能，能够完成输出文件类型、9个权限位信息、文件大小、文件名称等功能


## 实训部分

Test1

对象序列化实验。

序列化对象，即将变量从内存中转换为可存储式或可传输的形式的过程

该实验需要根据不同的实现要求，编写不同的软件版本，具体版本描述与功能需求如下

 版本1
 >将一个类的一个对象序列化到文件
 
 版本2
 >将一个类的多个对象序列化到文件
 
 版本3
 >将两个类的多个对象序列化到文件
 
 版本4
 >按照面向对象的方法，解决多个类的多个对象序列化到文件的问题
 
 ---
 Test2
 
 插件框架化实验
 
 能够实现对接口的操作和编程，学习动态链接库的使用和复习IO操作
 
 该实验需要根据不同的实现要求，编写不同的软件版本，具体版本描述与功能需求如下
 
 版本1
 >使用动态链接库实现打印功能
 
为了便于操作，使用了Makefile，可使用make或使用编译命令完成编译工作，所使用的命令如下所示
```
    make 2_1 / g++ 2_1.cpp -ldl -o 2_1
    make HW / g++ Hello_World.cpp -fpic -shared -o LibHW.so 
            / mv libHW.so libTest.so
    ./2_1
    make HC / g++ Hello_China.cpp -fpic -shared -o LibHC.so
            / mv libHC.so libTest.so
    ./2_1
```
 ---
 版本2
 >遍历指定目录，在目录里获取动态链接库实现打印功能
 
 所用到的编译命令如下所示
 ```
    g++ 2_2,cpp -ldl -o test
    ./test
 ```
 ---
 版本3
 >在版本二的基础上，实现一次调用一种功能
 
 为了便于操作，使用了Makefile，可使用make或使用编译命令完成编译工作，所使用的命令如下所示
```
    make /g++ -o 2_3 2_3.cpp pluginCounter.cpp pluginCounter.h -ldl
    ./2_3 help
    ./2_3 1
    ./2_3 2
    ./2_3 3
```
---
版本4
>讲三个导出函数都放在一个类中，让插件外部获取该类的对象

为了便于操作，使用了Makefile，可使用make或使用编译命令完成编译工作，所使用的命令如下所示
```
    make / g++ -o 2_4.cpp pluginCounter.cpp pluginController.cpp -ldl -g -o 2_4
    ./2_4 help
    ./2_4 1
    ./2_4 2
```
