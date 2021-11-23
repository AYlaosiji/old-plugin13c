class PATCHLOAD_API D2Gdi : public Library<D2Gdi>
{
	static void SetFunctions();
public:
	static void Init();
	
	static int* ForegroundRenderWidth;
};