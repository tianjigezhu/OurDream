#ifndef _MEND_DEFINES_H_
#define _MEND_DEFINES_H_

// 脚本文件中元素属性长度
#define SCRIPTSTAGEELENAME 32
#define SCRIPTSTAGEELEPATH 100
#define SCRIPTSTAGEPATH 100

// 脚本语法名字长度
#define SCRIPTGRAMANAME 20

#ifdef _UNICODE
// 脚本语法文件名
#define SCRIPTGRAMEFILE L"G:/git/OurGame/OurDream/2D游戏/2D类仙剑1游戏/文档/ScriptGrama.txt"
// 初始脚本路径定义
#define SCRIPTFILEPATH L""
#else
#define SCRIPTGRAMEFILE "G:/git/OurGame/OurDream/2D游戏/2D类仙剑1游戏/文档/ScriptGrama.txt"
// 初始脚本路径定义
#define SCRIPTFILEPATH ""
#endif



// 初始化内存管理模块时分配的内存大小，单位MB
#define MEMORYSIZE  100	

#define _MEND_DEBUG_

#endif