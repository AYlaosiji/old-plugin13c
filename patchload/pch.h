#ifndef PCH_H
#define PCH_H
#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NON_CONFORMING_SWPRINTFS

#define PATCHLOAD_EXPORT
#include "..\Commons\D2Patchload.h"

//待替换开始————————————————————————————————
#define D2SERVER
extern D2Json cfgJson;
#include "..\include\Cfg_Load.h"
#include <vector>
#define MODULES_H
#include "Modules.h"
#undef MODULES_H
//控制了老版的配置读取
#define LOADCONFIGGLOBAL
//控制了所有模块的加载
#define AllMOUDLEINSTALL
//待替换结束————————————————————————————————

#include "InstallAndUnInstall.h"//可能是要仍在最后

#endif //PCH_H
