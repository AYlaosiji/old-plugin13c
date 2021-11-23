#include"pch.h"
#ifdef MODULES_MULTIPAGES
#define BUFFER_SIZE 0x4000
#define FILE_VERSION 0x3130			//"01"
#define FILE_EXTENDED 0x4D545343	//"CSTM"

BYTE* readExtendedSaveFile(char* name, DWORD* size)//WORKS
{
	char filename[512];
	BYTE* data;
	Fog::D2Assert(!name, "Bad file name (NULL)", __FILE__, __LINE__);
	if (GetModuleHandle("d2server"))
	{
		sprintf(filename, m_UpdateServerClient_ServerSavePath);
	}else
	Fog::D2FogGetSavePath(filename, 512 - 5);
	strncat(filename, name, 512 - strlen(filename) - 5);
	strcat(filename, ".d2x");


	FILE* file = fopen(filename, "rb");
	if (file)
	{
		fseek(file, 0, SEEK_END);
		*size = ftell(file);
		fseek(file, 0, SEEK_SET);
		data = (BYTE*)Fog::D2FogMemAlloc(*size, __FILE__, __LINE__, 0);
		DWORD nbRead = fread(data, 1, *size, file);
		fclose(file);
		Fog::D2Assert(nbRead != *size, "nbRead from extented save file != size", __FILE__, __LINE__);
	}
	else 
	{
		DWORD maxSize = 100;
		data = (BYTE*)Fog::D2FogMemAlloc(maxSize, __FILE__, __LINE__, 0);
		*size = 14;
		*((DWORD*)&data[0]) = FILE_EXTENDED; //"CSTM"
		*((WORD*)&data[4]) = FILE_VERSION;
		//*((DWORD*)&data[6]) = nbPlayersCommandByDefault - 1;
		*((DWORD*)&data[10]) = 0;// number of stash
	}
	return data;
}

int loadExtendedSaveFile(UnitAny* ptChar, BYTE data[], DWORD maxSize)//WORKS
{
	if (!ptChar || !PCPY || !data) return 0;

	DWORD curSize = 0;

	if (*(DWORD*)&data[curSize] != FILE_EXTENDED)
	{
		return 9;
	}
	curSize += 4;

	if (*(WORD*)&data[curSize] != FILE_VERSION)
	{
		return 9;
	}
	curSize += 2;
	//nbPlayersCommand = (*(BYTE*)&data[curSize]) + 1;
	curSize += 1;
	curSize += 3;
	UnitAny* pCursorItemSave = D2Common::D2GetCursorItem(ptChar->ptInventory);
	Fog::D2Assert(!ptChar->ptPlayerData || !ptChar->ptPlayerData->name, "!ptChar->ptPlayerData || !ptChar->ptPlayerData->name", __FILE__, __LINE__);

	int ret  = loadStashList(ptChar, data, maxSize, &curSize, false);
	PCPY->selfStashIsOpened = true;

	loadExStash(ptChar, data, maxSize, curSize);
	loadExPet(ptChar, data, maxSize, curSize);
	UnitAny* pCursorItemCheck = D2Common::D2GetCursorItem(ptChar->ptInventory);
	if (pCursorItemCheck == NULL && pCursorItemSave)
	{
		//加载手上的物品
		loadExCursor(ptChar, data, maxSize, curSize);
	}
	else if (pCursorItemCheck && pCursorItemSave)
	{
	}
	else if (!pCursorItemCheck && !pCursorItemSave)
	{
	}
	else if (pCursorItemCheck && !pCursorItemSave)
	{
	}
	return ret;
}

void writeExtendedSaveFile(char* name, BYTE* data, DWORD size)
{
	char szTempName[MAX_PATH];
	char szSaveName[MAX_PATH];

	//Get temporary savefile name.
	if (GetModuleHandle("d2server"))
	{
		sprintf(szTempName, m_UpdateServerClient_ServerSavePath);
	}
	else
	Fog::D2FogGetSavePath(szTempName, MAX_PATH);
	strcat(szTempName, name);
	strcat(szTempName, ".d2~");
	//LogMsg("玩家%s : 写入临时文件 : %s(writeExtendedSaveFile)", name, szTempName);

	//Write data in savefile.
	FILE* customSaveFile = fopen(szTempName, "wb+");
	fwrite(data, size, 1, customSaveFile);
	fclose(customSaveFile);

	//Get real savefile name.
	if (GetModuleHandle("d2server"))
	{
		sprintf(szSaveName, m_UpdateServerClient_ServerSavePath);
	}
	else
	Fog::D2FogGetSavePath(szSaveName, MAX_PATH);

	strcat(szSaveName, name);
	strcat(szSaveName, ".d2x");
	//LogMsg("玩家%s : 保存额外文件 : %s(writeExtendedSaveFile)", name, szSaveName);

	DeleteFile(szSaveName);
	if (!MoveFile(szTempName, szSaveName))
	{
		Fog::D2Assert(1, "Could not create the extended save file", __FILE__, __LINE__);
	}
}

void saveExtendedSaveFile(UnitAny* ptChar, BYTE** data, DWORD* maxSize, DWORD* curSize)
{
	*(DWORD*)(*data + *curSize) = FILE_EXTENDED; //"CSTM"
	*curSize += 4;
	*(WORD*)(*data + *curSize) = FILE_VERSION;
	*curSize += 2;
	//*(DWORD*)(*data + *curSize) = (BYTE)(nbPlayersCommand - 1);
	*curSize += 4;

	Fog::D2Assert(!ptChar->ptPlayerData || !ptChar->ptPlayerData->name,"!ptChar->ptPlayerData || !ptChar->ptPlayerData->name",__FILE__, __LINE__);

	saveStashList(ptChar, PCPY->selfStash, data, maxSize, curSize);


	saveExStash(ptChar, data, maxSize, curSize);
	saveExPet(ptChar, data, maxSize, curSize);
	saveExCursor(ptChar, data, maxSize, curSize);
}

void backupExtendedSaveFile(char* name)
{
	char szBackupName[MAX_PATH];
	char szSaveName[MAX_PATH];

	if (GetModuleHandle("d2server"))
	{
		sprintf(szSaveName, m_UpdateServerClient_ServerSavePath);
	}
	else
	Fog::D2FogGetSavePath(szSaveName, MAX_PATH);
	strcat(szSaveName, name);
	strcat(szSaveName, ".d2x");

	if (GetModuleHandle("d2server"))
	{
		sprintf(szBackupName, m_UpdateServerClient_ServerSavePath);
	}
	else
	Fog::D2FogGetSavePath(szBackupName, MAX_PATH);
	strcat(szBackupName, name);
	strcat(szBackupName, ".d2x.backup");

	CopyFile(szSaveName, szBackupName, true);
}
#endif