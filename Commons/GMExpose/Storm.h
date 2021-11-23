class PATCHLOAD_API  Storm : public Library<Storm>
{
	static void SetFunctions();

public:
	static void Init();

public:
	typedef DWORD(__stdcall* TD2StormMPQOpenFile)(DWORD zero, LPCSTR fileName, DWORD dwSearchScope, void** buffer);
	static TD2StormMPQOpenFile D2StormMPQOpenFile;

	typedef DWORD(__stdcall* TD2Storm503)(DWORD, DWORD, DWORD);
	static TD2Storm503 D2Storm503;

	typedef DWORD(__stdcall* TD2FreeWinMessage)(sWinMessage* msg);
	static TD2FreeWinMessage D2FreeWinMessage;

	static void D2FreeMessage(sWinMessage* msg);
};