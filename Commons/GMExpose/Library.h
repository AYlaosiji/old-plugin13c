template <class Child>
class Library
{
public:
	static char* Name;
	static DWORD Offset;

	static DWORD LoadDiabloLibrary()
	{
		DWORD proposedOffset = (DWORD)GetModuleHandle(Name);
		if (proposedOffset == NULL)
			proposedOffset = (DWORD)LoadLibrary(Name);
		if (proposedOffset == NULL)
		{
			exit(-1);
		}
		return proposedOffset;
	}

	static void HookLibrary()
	{
		DWORD dw = 0;
		BYTE* offsetPESignature = Offset + *(BYTE**)((BYTE*)Offset + 0x3C);
		DWORD sizeOfCode = *(DWORD*)(offsetPESignature + 0x1C);
		BYTE* baseOfCode = Offset + *(BYTE**)(offsetPESignature + 0x2C);
		if (!VirtualProtect(baseOfCode, sizeOfCode, PAGE_EXECUTE_READWRITE, &dw))
		{
			MessageBox(NULL, "Failed to hook library", Name, MB_OK);
			exit(-1);
		}
	}

	static void UnhookLibrary()
	{
		DWORD dw = 0;
		BYTE* offsetPESignature = Offset + *(BYTE**)((BYTE*)Offset + 0x3C);
		DWORD sizeOfCode = *(DWORD*)(offsetPESignature + 0x1C);
		BYTE* baseOfCode = Offset + *(BYTE**)(offsetPESignature + 0x2C);
		if (!VirtualProtect(baseOfCode, sizeOfCode, PAGE_EXECUTE_READ, &dw))
			MessageBox(NULL, "Failed to Unhook library", Name, MB_OK);
	}

	// Retrieves the address by adding the DLLs base offset to the recorded offset
	static DWORD GetAddress(const DWORD offset)
	{
		DWORD proposedOffset = Offset + offset;
		return proposedOffset;
	}

	static DWORD GetAddressByOrdinal(const DWORD ordinal)
	{
		HMODULE module = (HMODULE)Offset;
		DWORD locatedAddress = (DWORD)GetProcAddress(module, (LPCSTR)ordinal);
		return locatedAddress;
	}
};

template <class Child>
char* Library<Child>::Name;

template <class Child>
DWORD Library<Child>::Offset;