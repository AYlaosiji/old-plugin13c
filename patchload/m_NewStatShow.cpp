#include "pch.h"
#ifdef MODULES_NEWSTATSHOW

//void* newStatsInterfaceImages = NULL;
//void* statsBackgroundImages = NULL;

D2DrawCell newStatsInterfaceImages("Sources\\SJ_PATH\\EmptyPage");
D2DrawCell statsBackgroundImages("Sources\\SJ_PATH\\StatsBackground");


void __stdcall printCustomPage()
{
	if ((selectedPage > 0) && (selectedPage <= lastPage))
		printNewStatsPageTwo(selectedPage);
	////else if (selectedPage == lastPage + 1)
	////	printRunewordsPage();
	//else if (selectedPage == lastPage + 2)
		//printNewStatsPage();
	else
		D2Client::D2PrintStatsPage();
}

DWORD __stdcall mouseCustomPageLeftDown(sWinMessage* msg)
{
	if ((selectedPage > 0) && (selectedPage <= lastPage))
		return mouseNewStatsPageTwoLeftDown(msg);
	//else if (selectedPage == lastPage + 1)
	//	return mouseRunewordsPageLeftDown(msg);
	//else if (selectedPage == lastPage + 2)
	//	return mouseNewStatsPageLeftDown(msg);
	else
		return -1;
}
//
DWORD __stdcall mouseCustomPageLeftUp(sWinMessage* msg)
{
	if ((selectedPage > 0) && (selectedPage <= lastPage))
		return mouseNewStatsPageTwoLeftUp(msg);
	//else if (selectedPage == lastPage + 1)
	//	return mouseRunewordsPageLeftUp(msg);
	//else if (selectedPage == lastPage + 2)
	//	return mouseNewStatsPageLeftUp(msg);
	else
		return -1;
}

__declspec(naked) void caller_DontPrintBorder_111()
{
	__asm 
	{
		MOV ECX, bDontPrintBorder
		TEST ECX, ECX
		JE printBorder
		MOV bDontPrintBorder, 0
		ADD DWORD PTR SS : [ESP] , 0xBC
		RETN
		printBorder :
		MOV ECX, 0x12
			RETN
	}
}

__declspec(naked) void caller_mouseCustomPageLeftDown_111()
{
	__asm {
		PUSH EAX
		PUSH ESI
		CALL mouseCustomPageLeftDown
		TEST EAX, EAX
		POP EAX
		JE end_mouseNewPageLDown
		JG continue_mouseNewPageLDown
		LEA ECX, DWORD PTR DS : [EAX + 0x80]
		RETN
		continue_mouseNewPageLDown :
		POP EAX
			ADD EAX, 0x143
			PUSH EDI
			JMP EAX
			RETN
			end_mouseNewPageLDown :
		ADD ESP, 4
			POP ESI
			POP EBP
			POP EBX
			RETN 4
	}
}

__declspec(naked) void caller_mouseCustomPageLeftUp_111()
{
	__asm 
	{
		PUSH EBP
		CALL mouseCustomPageLeftUp
		TEST EAX, EAX
		JE end_mouseNewPageLUp
		JG continue_mouseNewPageLUp
		MOV EAX, DWORD PTR DS : [D2Client::ptWindowStartX]
		MOV EAX, DWORD PTR DS : [EAX]
		RETN
		continue_mouseNewPageLUp :
		ADD DWORD PTR SS : [ESP] , 0x2C4
			RETN
			end_mouseNewPageLUp :
		ADD ESP, 4
			POP EDI
			POP ESI
			POP EBP
			POP EBX
			ADD ESP, 8
			RETN 4

	}
}


BOOL m_NewStatShow_NewStatShowIsOn = FALSE;


void m_NewStatShow_LoadCfg()
{
	m_NewStatShow_NewStatShowIsOn = cfgload::GetModuleCfgBool("New Stat Show", "New Stats Show IsOn");

	cJSON* cfgtemp=NULL;
	cfgtemp=cfgload::GetModuleCfg("New Stat Show", "Extra Stats Show List");
	if (cfgtemp && cfgtemp->type == cJSON_Array)
	{
		for (int i = 0; i < cJSON_GetArraySize(cfgtemp); i++)
		{
			cJSON* Object = cJSON_GetArrayItem(cfgtemp, i);
			if (Object && Object->type == cJSON_Object)
			{
				cJSON* Object2 = NULL;
				Object2 = cJSON_GetObjectItem(Object, "enabled");
				if (Object2 && Object2->type == cJSON_String)
					statsInterface[i].enabled = atoi(Object2->valuestring);
				Object2 = cJSON_GetObjectItem(Object, "page");
				if (Object2 && Object2->type == cJSON_String)
					statsInterface[i].page = atoi(Object2->valuestring);
				Object2 = cJSON_GetObjectItem(Object, "x");
				if (Object2 && Object2->type == cJSON_String)
					statsInterface[i].x = atoi(Object2->valuestring);
				Object2 = cJSON_GetObjectItem(Object, "y");
				if (Object2 && Object2->type == cJSON_String)
					statsInterface[i].y = atoi(Object2->valuestring);
				Object2 = cJSON_GetObjectItem(Object, "color");
				if (Object2 && Object2->type == cJSON_String)
					statsInterface[i].color = atoi(Object2->valuestring);
				Object2 = cJSON_GetObjectItem(Object, "font");
				if (Object2 && Object2->type == cJSON_String)
					statsInterface[i].font = atoi(Object2->valuestring);
				Object2 = cJSON_GetObjectItem(Object, "statID");
				if (Object2 && Object2->type == cJSON_String)
					statsInterface[i].statsID = atoi(Object2->valuestring);

			}
		}
	}

	lastPage = 0;
	for (size_t i = 0; i < nbStatsInterface; i++)
		if (statsInterface[i].page > lastPage)
			lastPage = statsInterface[i].page;

}

void m_NewStatShow_Install()
{
	DWORD offset;
	if (m_NewStatShow_NewStatShowIsOn)
	{
		extraHiddenPage = 1;
		//if (selectMainPageOnOpenning)
		//{
		//	mem_seek R7(D2Client, 0000, 0000, 0000, 4B79E, 8F73E, 55E0E, 65F5E, C41FE);
		//	memt_byte(0x83, 0xE8);	// CALL caller_resetSelectedPage
		//	MEMT_REF4(0x1F7426F8, caller_resetSelectedPageByToolBar);
		//	mem_seek R7(D2Client, 0000, 0000, 0000, 1E55A, 6A8FA, A31DA, 3C5EA, 3E39A);
		//	memt_byte(0x55, 0xE8);	// CALL caller_resetSelectedPage
		//	MEMT_REF4(0xD53BED33, caller_resetSelectedPageByKey);
		//}
		//加载按钮
		offset = D2Client::GetAddress(0xBDC16);
		Memory::SetCursor(offset);
		Memory::ChangeByte(0x5F, 0xE9);
		Memory::ChangeCallA(0x815B5D5E, (DWORD)caller_printStatsPageBtns_111);

		//鼠标按下
		offset = D2Client::GetAddress(0xBCDC8);
		Memory::SetCursor(offset);
		Memory::ChangeByte(0xA1, 0xE8);
		Memory::ChangeCallA((DWORD)D2Client::ptPlayerClient, (DWORD)caller_statsPageMouseDown);

		//鼠标抬起
		offset = D2Client::GetAddress(0xBDE33);
		Memory::SetCursor(offset);
		Memory::ChangeByte(0xA1, 0xE8);
		Memory::ChangeCallA((DWORD)D2Client::ptPlayerClient, (DWORD)caller_statsPageMouseUp);

		//自定义界面
		offset = D2Client::GetAddress(0xC3B49);
		Memory::SetCursor(offset);
		Memory::ChangeCallC((DWORD)D2Client::D2PrintStatsPage, (DWORD)printCustomPage);

		// Don't print Border
		offset = D2Client::GetAddress(0x271C6);
		Memory::SetCursor(offset);
		Memory::ChangeByte(0xB9, 0xE8);
		Memory::ChangeCallA(0x00000012, (DWORD)caller_DontPrintBorder_111);

		// Manage mouse down (Play sound)
		offset = D2Client::GetAddress(0xBCD36);
		Memory::SetCursor(offset);
		Memory::ChangeByte(0x8D, 0xE8);
		Memory::ChangeCallA(0x00008088, (DWORD)caller_mouseCustomPageLeftDown_111);
		Memory::ChangeByte(0x00, 0x90);

		// Manage mouse up
		offset = D2Client::GetAddress(0xBDCB9);
		Memory::SetCursor(offset);
		Memory::ChangeByte(0xA1, 0xE8);
		Memory::ChangeCallA((DWORD)D2Client::ptWindowStartX, (DWORD)caller_mouseCustomPageLeftUp_111);
	}


		
	

}

void m_NewStatShow_UnInstall()
{

}

void m_NewStatShow_LoadImage()
{
	if (m_NewStatShow_NewStatShowIsOn)
	{
		newStatsInterfaceImages.loadFileSafely();
		statsBackgroundImages.loadFileSafely();
		//loadImagesFile(&newStatsInterfaceImages, "EmptyPage");
		//loadImagesFile(&statsBackgroundImages, "StatsBackground");
	}
}

void m_NewStatShow_FreeImage()
{
	if (m_NewStatShow_NewStatShowIsOn)
	{
		newStatsInterfaceImages.unloadFileSafely();
		statsBackgroundImages.unloadFileSafely();
		//freeImagesFile(newStatsInterfaceImages); newStatsInterfaceImages = NULL;
		//freeImagesFile(statsBackgroundImages); statsBackgroundImages = NULL;
	}
}
#endif

