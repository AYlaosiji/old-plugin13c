
#include <windows.h>
#include <io.h>
#include <direct.h>			// _getcwd()
#include <time.h>
#include <iostream>

#include <list>//不要问我为什么用链表，我只看了数据结构的第一章
#include <string>

#ifdef PATCHLOAD_EXPORT
#define PATCHLOAD_API   __declspec (dllexport)
#else
#define PATCHLOAD_API   __declspec (dllimport)
#endif

#define PATCHLOADPLUGYNAME "PatchloadSubModule"

#include "..\Commons\GMExpose\d2constants.h"
#include "..\Commons\GMExpose\updatingConst.h"
#include "..\Commons\GMExpose\D2UnitStruct.h"
#include "..\Commons\GMExpose\d2BinFile.h"
#include "..\Commons\GMExpose\d2Struct.h"
#include "..\Commons\GMExpose\D2PKTStruct.h"

#include "..\Commons\GMExpose\LoadD2.h"

#include "..\Commons\GMExpose\D2Functions.h"


//下面给出一个CPP最简单实施的例子，编译成dll后改后缀为cppd，
//扔到PatchloadSubModule patchload会自动加载该模块
//以下内容请不要取消注释，仅仅给一个cpp的例子而已


//#include "..\Commons\D2Patchload.h"
//#pragma comment (lib , "..\\Commons\\patchload.lib" )
//#define PATCHLOADSUBNAME "Client Sample"
//
//D2Json config;bool IsOn = false;
//
//void loadconfig(){config.GetCfgBool(config.GetRoot(), "IsOn", &IsOn);}
//
//extern "C" _declspec (dllexport)void Install(){config.load(PATCHLOADPLUGYNAME"\\" PATCHLOADSUBNAME ".json");loadconfig();if (IsOn){/*编写你的模块安装*/}}
//
//extern "C" _declspec (dllexport)void UnInstall(){if (IsOn){/*编写你的模块的卸载*/}}
//
//BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) { return TRUE; }

