
#include <windows.h>
#include <io.h>
#include <direct.h>			// _getcwd()
#include <time.h>
#include <iostream>

#include <list>//��Ҫ����Ϊʲô��������ֻ�������ݽṹ�ĵ�һ��
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


//�������һ��CPP���ʵʩ�����ӣ������dll��ĺ�׺Ϊcppd��
//�ӵ�PatchloadSubModule patchload���Զ����ظ�ģ��
//���������벻Ҫȡ��ע�ͣ�������һ��cpp�����Ӷ���


//#include "..\Commons\D2Patchload.h"
//#pragma comment (lib , "..\\Commons\\patchload.lib" )
//#define PATCHLOADSUBNAME "Client Sample"
//
//D2Json config;bool IsOn = false;
//
//void loadconfig(){config.GetCfgBool(config.GetRoot(), "IsOn", &IsOn);}
//
//extern "C" _declspec (dllexport)void Install(){config.load(PATCHLOADPLUGYNAME"\\" PATCHLOADSUBNAME ".json");loadconfig();if (IsOn){/*��д���ģ�鰲װ*/}}
//
//extern "C" _declspec (dllexport)void UnInstall(){if (IsOn){/*��д���ģ���ж��*/}}
//
//BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) { return TRUE; }

