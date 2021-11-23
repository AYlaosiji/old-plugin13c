class PATCHLOAD_API D2Win : public Library<D2Win>
{

	static void SetFunctions();

public:
	static void Init();

public:
	typedef DWORD(__fastcall* TD2GetPixelLen) (LPWSTR s);
	static TD2GetPixelLen D2GetPixelLen;

	typedef void(__fastcall* TD2PrintPopup) (LPWSTR s, DWORD x, DWORD y, DWORD color, DWORD center);
	static TD2PrintPopup D2PrintPopup;

	typedef CellFile* (__fastcall* TD2LoadCellFile) (const char* szFile, int Type);
	static TD2LoadCellFile D2LoadCellFile;

	typedef void(__fastcall* TD2PrintString) (wchar_t* pString, int nXpos, int nYpos, int nColour, int nTransTbl);
	static TD2PrintString D2PrintString;

	typedef int(__fastcall* TD2SetFontSize) (int nFont);
	static TD2SetFontSize D2SetFontSize;

	typedef void(__fastcall* TD2DisplayBlendedText) (wchar_t* pString,int nXpos,int nYpos,int nColour,DWORD bCentered,int BlendMode);
	static TD2DisplayBlendedText D2DisplayBlendedText;

	typedef void* (__stdcall* TD2CreateTextBox) (DWORD* data);
	static TD2CreateTextBox D2CreateTextBox;

    typedef void (__fastcall* TD2PrintLineOnTextBox) (void* screen, char* s, DWORD color);
	static TD2PrintLineOnTextBox D2PrintLineOnTextBox;
};