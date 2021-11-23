class PATCHLOAD_API Fog : public Library<D2Lang>
{
	static void SetFunctions();

public:
	static void Init();

public:
	typedef void(__fastcall* TD2FogAssert)(const char* ptMessage, CHAR* pLocation, DWORD line);
	static TD2FogAssert D2FogAssert;

	typedef void* (__fastcall* TD2FogMemAlloc) (DWORD dwMemSize, LPCSTR lpszErrFile, DWORD ErrLine, DWORD Zero);
	static TD2FogMemAlloc D2FogMemAlloc;

	typedef void*(__fastcall* TD2FogMemDeAlloc) (void* ptMemLoc, LPCSTR lpszErrFile, DWORD ErrLine, DWORD Zero);
	static TD2FogMemDeAlloc D2FogMemDeAlloc;

	typedef void* (__fastcall* TD2AllocMem) (DWORD, DWORD dwMemSize, LPCSTR lpszErrFile, DWORD ErrLine, DWORD Zero);
	static TD2AllocMem D2AllocMem;

	typedef void* (__fastcall* TD2FreeMem) (DWORD, void* ptMemLoc, LPCSTR lpszErrFile, DWORD ErrLine, DWORD Zero);
	static TD2FreeMem D2FreeMem;

	typedef void (__fastcall* TD2FogGetSavePath) (char* ptPath, DWORD maxsize);
	static TD2FogGetSavePath D2FogGetSavePath;

	typedef void(__stdcall* TD2EncodeValue)(saveBitField* data, DWORD value, DWORD bitSize);
	static TD2EncodeValue D2EncodeValue;

	typedef void(__stdcall* TD2DecodeValue)(saveBitField* data, DWORD readingSize);
	static TD2DecodeValue D2DecodeValue;

	typedef void* (__stdcall* TD2Fog10212) (DWORD unknow);
	static TD2Fog10212 D2Fog10212;

	typedef int (__stdcall* TD2GetInstructionPointer)();
	static TD2GetInstructionPointer D2GetInstructionPointer;

	//该Assert不依赖任何库
	static void D2Assert(BOOL pCondition, CHAR* pMessage, CHAR* file, DWORD pLineNbr);
};