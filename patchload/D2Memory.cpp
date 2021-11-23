#include "pch.h"

#define active_CheckMemory TRUE
#define MSG_ERROR_READ_MEMORY "Error: Read access missing to patch memory at %08X.\n\nPlease install a clean version of Diablo II.\n\n"
#define MSG_CRITICAL_WRITE_MEMORY  "Error: Write access missing to patch memory at %08X.\n\nPlease install a clean version of Diablo II.\n\n"
#define ERROR_TESTING1   "Error: BYTE %02X wanted but %02X found to change memory at %08X\n\n"
#define ERROR_TESTING4   "Error: DWORD %08X wanted but %08X found to change memory at %08X\n\n"
void Memory::mem_showbox(const char* pFormat, ...)
{
	char buffer[300];
	va_list lArgs;
	va_start(lArgs, pFormat);
	vsprintf(buffer, pFormat, lArgs);
	va_end(lArgs);

	MessageBox(NULL, buffer, "Memory Warning", MB_OK | MB_ICONEXCLAMATION);
}

DWORD Memory::mem_seek(DWORD newPos)
{
	currentMemoryPos = (void*)newPos;
	return (DWORD)currentMemoryPos;
}

void Memory::patchMemory1(BYTE value)
{
	if (IsBadWritePtr(currentMemoryPos, 1))
	{
		mem_showbox(MSG_CRITICAL_WRITE_MEMORY, currentMemoryPos);
		exit(1);
	}
	*(BYTE*)currentMemoryPos = value;
	currentMemoryPos = (LPVOID)((DWORD)currentMemoryPos + 1);
}

void Memory::patchMemory4(DWORD value)
{
	if (IsBadWritePtr(currentMemoryPos, 4))
	{
		mem_showbox(MSG_CRITICAL_WRITE_MEMORY, currentMemoryPos);
		exit(1);
	}
	*(DWORD*)currentMemoryPos = value;
	currentMemoryPos = (LPVOID)((DWORD)currentMemoryPos + 4);
}

BYTE Memory::getMemory1(LPVOID mempos)
{
	if (IsBadReadPtr(mempos, 1))
	{
		mem_showbox(MSG_ERROR_READ_MEMORY, currentMemoryPos);
		exit(1);
	}
	return *(BYTE*)mempos;
}

DWORD Memory::getMemory4(LPVOID mempos)
{
	if (IsBadReadPtr(mempos, 4))
	{
		mem_showbox(MSG_ERROR_READ_MEMORY, currentMemoryPos);
		exit(1);
	}
	return *(DWORD*)mempos;
}

void Memory::memt_byte(BYTE old, BYTE val)
{
	BYTE current = getMemory1(currentMemoryPos);
	if (current == val)
	{
		currentMemoryPos = (LPVOID)((DWORD)currentMemoryPos + 1);
		return;
	}
	if (old != current)
	{
		if (active_CheckMemory)
		{
			mem_showbox(ERROR_TESTING1, old, current, currentMemoryPos);
			exit(1);
		}
	}
	patchMemory1(val);
}

bool Memory::testIfAlreadySet(DWORD current, DWORD wanted)
{
	if (current == wanted)
	{
		currentMemoryPos = (LPVOID)((DWORD)currentMemoryPos + 4);
		return true;
	}
	return false;
}

void Memory::testMemory4(DWORD old, DWORD found)
{
	if (old != found)
		if (active_CheckMemory)
		{
			mem_showbox(ERROR_TESTING4, old, found, currentMemoryPos);
			exit(1);
		}
}

void Memory::memt_dword(DWORD old, DWORD val)
{
	DWORD current = getMemory4(currentMemoryPos);
	DWORD wanted = val;
	if (testIfAlreadySet(current, wanted)) return;
	testMemory4(old, current);
	patchMemory4(wanted);
}

void Memory::memt_ref4(DWORD old, DWORD ref)
{
	DWORD current = getMemory4(currentMemoryPos);
	DWORD wanted = ref - (DWORD)currentMemoryPos - 4;
	if (testIfAlreadySet(current, wanted)) return;
	testMemory4(old, current);
	patchMemory4(wanted);
}

void Memory::memc_ref4(DWORD old, DWORD ref)
{
	DWORD current = getMemory4(currentMemoryPos);
	DWORD wanted = ref - (DWORD)currentMemoryPos - 4;
	if (testIfAlreadySet(current, wanted)) return;
	testMemory4(old, current + (DWORD)currentMemoryPos + 4);
	patchMemory4(wanted);
}

void Memory::memj_ref4(DWORD old, DWORD ref)
{
	DWORD current = getMemory4(currentMemoryPos);
	DWORD wanted = ref - (DWORD)currentMemoryPos - 4;
	if (testIfAlreadySet(current, wanted)) return;
	testMemory4(old, getMemory4((LPVOID)getMemory4((LPVOID)(current + (DWORD)currentMemoryPos + 6))));
	patchMemory4(wanted);
}

void Memory::memd_ref4(DWORD old, DWORD ref)
{
	DWORD current = getMemory4(currentMemoryPos);
	DWORD wanted = ref - (DWORD)currentMemoryPos - 4;
	if (testIfAlreadySet(current, wanted)) return;
	testMemory4(old, getMemory4((LPVOID)current));
	patchMemory4(wanted);
}

void* Memory::currentMemoryPos;

void Memory::SetCursor(DWORD position)
{
	mem_seek(position);
}

void Memory::ChangeByte(BYTE oldValue, BYTE newValue)
{
	memt_byte(oldValue, newValue);
}

void Memory::ChangeDword(DWORD oldValue, DWORD newValue)
{
	memt_dword(oldValue, newValue);
}

void Memory::ChangeCallA(DWORD oldValue, DWORD newValue)
{
	memt_ref4(oldValue, newValue);
}

void Memory::ChangeCallB(DWORD oldValue, DWORD newValue)
{
	memj_ref4(oldValue, newValue);
}

void Memory::ChangeCallC(DWORD oldValue, DWORD newValue)
{
	memc_ref4(oldValue, newValue);
}

void Memory::ChangeCallD(DWORD oldValue, DWORD newValue)
{
	memd_ref4(oldValue, newValue);
}

