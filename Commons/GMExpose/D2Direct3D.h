class PATCHLOAD_API D2Direct3D : public Library<D2Direct3D>
{
	static void SetFunctions();
public:
	static void Init();

	static int* WindowWidth;
	static int* WindowHeight;
};