class PATCHLOAD_API D2Glide : public Library<D2Glide>
{
	static void SetFunctions();
public:
	static void Init();

	static int* WindowWidth;
	static int* WindowHeight;
	static BOOL* SpritesInited;
};