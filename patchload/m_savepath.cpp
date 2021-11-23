/*=================================================================
	File created by Yohann NICOLAS.
	Add support 1.13d by L'Autour.

	Changing the current save path.

=================================================================*/

#include"pch.h"
#ifdef MODULES_SAVEPATH

#define FCT_ASM(N) __declspec(naked) void N() {__asm{

bool m_SavePath_IsOn = false;
char *savePath = NULL;

void m_SavePath_LoadCfg()
{
}

FCT_ASM( changeSavePath )
	PUSH EDI
	PUSH EDX
	PUSH ESI
	MOV EDI,DWORD PTR DS:[savePath]
	XOR AL,AL
	CLD
	OR ECX,0xFFFFFFFF
	REPNE SCAS BYTE PTR ES:[EDI]
	NOT ECX
	SUB EDI,ECX
	XCHG EDI,ESI
	CMP BYTE PTR [ESI+1],':'
	JE END_CHANGESP
//RELATIVE_PATH:
	MOV EDX,ECX
	OR ECX,0xFFFFFFFF
	REPNE SCAS BYTE PTR ES:[EDI]
	DEC EDI
	CMP BYTE PTR [EDI-1],'\\'
	JE NEXT
	MOV BYTE PTR [EDI],'\\'
	INC EDI
NEXT:
	MOV ECX,EDX
END_CHANGESP:
	REP MOVS BYTE PTR ES:[EDI],BYTE PTR DS:[ESI]
	POP ESI
	POP EDX
	POP EDI
	PUSH ESI
	CALL EBP
	CMP EAX,-1
	RETN
}}

FCT_ASM( changeSavePath_111 )
	PUSH EAX
	PUSH EDI
	PUSH EDX
	PUSH ESI
	MOV EDI,DWORD PTR DS:[savePath]
	XOR AL,AL
	CLD
	OR ECX,0xFFFFFFFF
	REPNE SCAS BYTE PTR ES:[EDI]
	NOT ECX
	SUB EDI,ECX
	XCHG EDI,ESI
	CMP BYTE PTR [ESI+1],':'
	JE END_CHANGESP
//RELATIVE_PATH:
	MOV EDX,ECX
	OR ECX,0xFFFFFFFF
	REPNE SCAS BYTE PTR ES:[EDI]
	DEC EDI
	CMP BYTE PTR [EDI-1],'\\'
	JE NEXT
	MOV BYTE PTR [EDI],'\\'
	INC EDI
NEXT:
	MOV ECX,EDX
END_CHANGESP:
	REP MOVS BYTE PTR ES:[EDI],BYTE PTR DS:[ESI]
	POP ESI
	POP EDX
	POP EDI
	POP EAX
	CMP EAX,-1
	JE DONOT_JMP
	ADD DWORD PTR SS:[ESP],5
DONOT_JMP:
	RETN
}}

FCT_ASM ( forCreateSavePath )
	PUSH EDI
	MOV EDI,DWORD PTR DS:[savePath]
	MOV ECX,EDI
	CMP BYTE PTR DS:[EDI+1],':'
	JNZ END_CREATESP
	PUSH ESI
	XOR AL,AL
	CLD
	OR ECX,0xFFFFFFFF
	REPNE SCAS BYTE PTR ES:[EDI]
	NOT ECX
	SUB EDI,ECX
	XCHG EDI,ESI
	REP MOVS BYTE PTR ES:[EDI],BYTE PTR DS:[ESI]
	POP ESI
END_CREATESP:
	POP EDI
	MOV DWORD PTR SS:[ESP+8],ECX
	JMP Storm::D2Storm503
}}

static void Install_ChangingSavePath()
{
    DWORD SavePathOffset = 0;

	D2String::LogMsg("Patch Fog for change the save path. (changingSavePath)");

	//6FF67F86   . 83F8 FF        CMP EAX,-1
	//6FF67F89   . 75 05          JNZ SHORT Fog.6FF67F90
    SavePathOffset = Fog::GetAddress(0x6FF67F86 - 0x6FF50000);
    Memory::SetCursor(SavePathOffset);
    Memory::ChangeByte(0x83, 0xE8);

    SavePathOffset = Fog::GetAddress(0x6FF67F87 - 0x6FF50000);
    Memory::SetCursor(SavePathOffset);
    Memory::ChangeCallA(0x0575FFF8, (DWORD)changeSavePath_111);

	//6FF67FA5   . E8 504EFFFF    CALL <JMP.&Storm.#503>
    SavePathOffset = Fog::GetAddress(0x6FF67FA6 - 0x6FF50000);
    Memory::SetCursor(SavePathOffset);
    Memory::ChangeCallB((DWORD)Storm::D2Storm503, (DWORD)forCreateSavePath);

	// Remove registry update
	//6FF6F0AA   . 56             PUSH ESI
	//6FF6F0AB   . 6A 00          PUSH 0
	//6FF6F0AD   . 68 D466F76F    PUSH Fog.6FF766D4                        ;  ASCII "Save Path"
	//6FF6F0B2   . 68 E066F76F    PUSH Fog.6FF766E0                        ;  ASCII "Diablo II"
	//6FF6F0B7   . E8 58DDFEFF    CALL <JMP.&Storm.#425>
    SavePathOffset = Fog::GetAddress(0x6FF67FAA - 0x6FF50000);
    Memory::SetCursor(SavePathOffset);
    Memory::ChangeByte(0x56, 0xEB);
    SavePathOffset = Fog::GetAddress(0x6FF67FAB - 0x6FF50000);
    Memory::SetCursor(SavePathOffset);
    Memory::ChangeByte(0x6A, 0x10);
    SavePathOffset = Fog::GetAddress(0x6FF67FAC - 0x6FF50000);
    Memory::SetCursor(SavePathOffset);
    Memory::ChangeByte(0x00, 0x90);
}

void m_SavePath_Install()
{
#define BUFSIZE 0x400
extern char szPluginPath[];
	char buffer[BUFSIZE];
    m_SavePath_IsOn = cfgload::GetModuleCfgBool("Save Path", "IsOn");
	cfgload::GetModuleCfgString("Save Path", "Path", buffer, BUFSIZE);
	GetCurrentDirectory(MAX_PATH, szPluginPath);
	if (m_SavePath_IsOn && 0 != buffer[0])
	{
		int curSize =  0;
		int start = 0;

		while (buffer[curSize])
			curSize++;

		if ( (curSize>0) && buffer[curSize-1] != (BYTE)'\\')
		{
			buffer[curSize++] = (BYTE)'\\';
			buffer[curSize]='\0';
		}
		while (buffer[start] == '\\')
			start++;

		if (!buffer[start])
		{
			m_SavePath_IsOn = false;
			D2String::LogMsg("active_changingSavePath\t\t= %u (no valid savePath)\n\n", m_SavePath_IsOn);
//			log_msg("\tsavePath\t\t\t= %s\n", savePath);
			return;
		}

		if (buffer[start+1]!=':')
		{
			char buf[MAX_PATH] = {0};
			strcpy(buf, szPluginPath);
            *(strrchr(buf, '\\') + 1) = '\0';
            strcat(buf, "Save\\");
			savePath = (char*)Fog::D2FogMemAlloc(strlen(buf) + curSize - start + 1,__FILE__,__LINE__,0);
			strcpy(savePath,buf);
			strcat(savePath,&buffer[start]);
		} else {
			savePath = (char*)Fog::D2FogMemAlloc(curSize-start+1,__FILE__,__LINE__,0);
			strcpy(savePath,&buffer[start]);
		}
		D2String::LogMsg("savePath= %s", savePath);
	}

    if (m_SavePath_IsOn == FALSE)return;
    if (0 == savePath[0]) return;
    Install_ChangingSavePath();
}

void m_SavePath_UnInstall()
{
}

#endif //MODULES_SAVEPATH
/*================================= END OF FILE =================================*/
