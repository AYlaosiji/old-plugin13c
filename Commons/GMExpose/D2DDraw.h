class PATCHLOAD_API D2DDraw : public Library<D2DDraw>
{
	static void SetFunctions();
public:
	static void Init();

	static int* WindowWidth;
	static int* WindowHeight;
};