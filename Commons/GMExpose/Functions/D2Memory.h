class PATCHLOAD_API Memory
{
private:
	static void mem_showbox(const char* pFormat, ...);

	static DWORD mem_seek(DWORD newPos);

	static void patchMemory1(BYTE value);

	static void patchMemory4(DWORD value);

	static BYTE getMemory1(LPVOID mempos);

	static DWORD getMemory4(LPVOID mempos);

	static void memt_byte(BYTE old, BYTE val);

	static bool testIfAlreadySet(DWORD current, DWORD wanted);

	static void testMemory4(DWORD old, DWORD found);

	static void memt_dword(DWORD old, DWORD val);

	static void memt_ref4(DWORD old, DWORD ref);

	static void memc_ref4(DWORD old, DWORD ref);

	static void memj_ref4(DWORD old, DWORD ref);

	static void memd_ref4(DWORD old, DWORD ref);

	static void* currentMemoryPos;
public:
	static void SetCursor(DWORD position);

	static void ChangeByte(BYTE oldValue, BYTE newValue);

	static void ChangeDword(DWORD oldValue, DWORD newValue);

	static void ChangeCallA(DWORD oldValue, DWORD newValue);

	static void ChangeCallB(DWORD oldValue, DWORD newValue);

	static void ChangeCallC(DWORD oldValue, DWORD newValue);

	static void ChangeCallD(DWORD oldValue, DWORD newValue);

};
