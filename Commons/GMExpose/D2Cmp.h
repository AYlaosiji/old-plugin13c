class  PATCHLOAD_API D2Cmp: public Library<D2Cmp>
{
	static void SetFunctions();
public:
	static void Init();
public:
	typedef int(__stdcall* TD2FreeImage)(void* image);
	static TD2FreeImage VD2FreeImage;
};