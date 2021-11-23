class PATCHLOAD_API D2Gfx : public Library<D2Gfx>
{
	static void SetFunctions();

public:

	static void Init();

public:
	typedef DWORD(__stdcall* TD2GetResolution) ();
	static TD2GetResolution D2GetResolution;

	typedef void(__stdcall* TD2DrawLine)(int nXposStart, int nYposStart, int nXposEnd, int nYposEnd, int nPaletteIndex, int nTransTbl);
	static TD2DrawLine D2DrawLine;

	typedef void(__stdcall* TD2FillArea)(DWORD x1, DWORD y1, DWORD x2, DWORD y2, DWORD color, DWORD transTbl);
	static TD2FillArea D2FillArea;

	typedef void(__stdcall* TD2DrawImage)(sDrawImageInfo* pData, DWORD nXpos, DWORD nYpos, DWORD nGamma, DWORD nDrawType, BYTE* pPalette);
	//"Draw modes Types List"
//; 0 -> 25 % opacity
//	; 1 -> 50 % opacity
//	; 2 -> 75 % opacity
//	; 3->Color blend 1 (Transparent + Highlight)
//	; 4->Color Blend 2 (Makes image pure black)
//	; 5->Normal Draw
//	; 6->Color Blend 3 (Screen + Transparent)
//	; 7->Highlight
	static TD2DrawImage D2DrawImage;

	typedef void(__stdcall* TD2DrawVerticalCropImage)(sDrawImageInfo* pData, int nXpos, int nYpos, DWORD nGamma, int nSize, int nDrawType);
	static TD2DrawVerticalCropImage D2DrawVerticalCropImage;

	typedef int(__stdcall* TD2GetRenderMode)();
	static TD2GetRenderMode D2GetRenderMode;
	
	static DWORD* WindowWidth;
	static DWORD* WindowHeight;
};