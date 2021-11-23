#define MODULES_UPDATESERVERCLIENT

#pragma pack(1)
struct Dmgmisc
{
	BYTE color;
	BYTE bPlayerFlag;
	WORD WorldMonsterPercent;
};

struct DmgPack
{
	union
	{
		Dmgmisc dmgmisc;
		DWORD dwdmgmisc;
	};
};
#pragma pack()

void m_UpdateServerClient_LoadCfg();
void m_UpdateServerClient_Install();
void m_UpdateServerClient_UnInstall();

//以下函数导出给其他模块用

void updateClient(UnitAny* ptChar, DWORD mFunc, DWORD p1, DWORD p2, DWORD p3);
void updateClient(UnitAny* ptChar, DWORD mFunc, char* msg);
void updateAllClient(GameStruct* pGame, DWORD mFunc, DWORD p1, DWORD p2, DWORD p3);
__inline void updateServer(WORD p) { D2Client::D2SendToServer3(0x3A, p); };