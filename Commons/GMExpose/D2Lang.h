class PATCHLOAD_API D2Lang : public Library<D2Lang>
{
	static void SetFunctions();

public:
	static void Init();

public:
	typedef wchar_t* (__fastcall* TD2GetStringFromIndex)(WORD nLocaleTxtNo);
	static TD2GetStringFromIndex D2GetStringFromIndex;
};