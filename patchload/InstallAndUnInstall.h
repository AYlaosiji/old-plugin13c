class InstallAndUnInstall
{
	struct Others
	{
		std::string path;
		HMODULE phandle;
		FARPROC installaddr;
		FARPROC uninstalladdr;
	};

	static std::list<Others> otherlist;

	static void InstallOthers()
	{
		long hFile = 0;
		struct _finddata_t fileInfo;
		char SubModulePath[_MAX_PATH] = "";
		std::string SubModulePathString;
		std::string pathName;

		_getcwd(SubModulePath, MAX_PATH);
		if (SubModulePath[strlen(SubModulePath)] != '\\')
			strcat(SubModulePath, "\\");
		//strcat(SubModulePath, "PatchloadSubModule");
		SubModulePathString= SubModulePath;

		if ((hFile = _findfirst(pathName.assign(SubModulePathString).append("\\*").c_str(), &fileInfo)) == -1)
			return;

		if ((hFile = _findfirst(pathName.assign(SubModulePathString).append("\\*").c_str(), &fileInfo)) == -1)
			return;

		do 
		{
			std::string filePath =  fileInfo.name;
			std::string::size_type filePos = filePath.rfind('.');
			if (filePos != std::string::npos)
				++filePos;
			else
				filePos = 0;
			std::string ext = filePath.substr(filePos);
			//这里将所有的dll扔进容器里面加载
			if (ext == "cppd")
			{
				filePath = SubModulePathString + "\\" + filePath;
				HMODULE phandle = LoadLibraryA(filePath.c_str());
				if (phandle)
				{
					FARPROC pInstall = GetProcAddress(phandle, "Install");
					FARPROC pUnInstall = GetProcAddress(phandle, "UnInstall");
					Others dll = { filePath ,phandle, pInstall ,pUnInstall };
					otherlist.push_back(dll);
				}
				else
				{
					MessageBoxA(NULL, filePath.c_str(), "Error Load", MB_OK);
					exit(EXIT_SUCCESS);
				}

			}
		} 
		while (_findnext(hFile, &fileInfo) == 0);

		_findclose(hFile);

		for (std::list<Others>::iterator it = otherlist.begin(); it != otherlist.end(); it++)
		{
			if(it->installaddr)(it->installaddr)();
		}
	
		return;
	}

	static void UnInstallOthers()
	{
		for (std::list<Others>::iterator it = otherlist.begin(); it != otherlist.end(); it++)
		{
			if(it->uninstalladdr)(it->uninstalladdr)();
			FreeLibrary(it->phandle);
		}
		otherlist.clear();
	}
public:
	static void Install()
	{
		
#ifdef LOADCONFIGGLOBAL
		if (!cfgload::Init())
		{
			MessageBox(NULL, "Bag Config", "Bag Config", MB_OK);
			exit(EXIT_SUCCESS);
		}
		cfgJson.load("patchload_sj.json");
#define MODULES_CONFIGLOAD
#include "Modules.h"
#undef MODULES_CONFIGLOAD

#endif
		
		LoadD2::Init();
		LoadD2::Hook();

#ifdef AllMOUDLEINSTALL
#define MODULES_INSTALL
#include"Modules.h"
#undef MODULES_INSTALL
#endif
		InstallOthers();
		LoadD2::UnHook();

	}

	static void UnInstall()
	{
#ifdef AllMOUDLEINSTALL
#define MODULES_UNINSTALL
#include"Modules.h"
#undef MODULES_UNINSTALL
#endif
		UnInstallOthers();
	}
};
