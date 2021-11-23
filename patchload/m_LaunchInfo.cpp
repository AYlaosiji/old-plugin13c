#include"pch.h"
#ifdef MODULES_LANUNCHINFO

void caller_printPatchVersion();

void m_LaunchInfo_LoadCfg()
{

}

void m_LaunchInfo_Install()
{
    Memory::SetCursor(D2Launch::GetAddress(0x6FA58061 - 0x6FA40000));
    D2Launch::HookLibrary();
    Memory::ChangeCallB((DWORD)D2Win::D2CreateTextBox, (DWORD)caller_printPatchVersion);
}

void m_LaunchInfo_UnInstall()
{

}

BYTE colorOfPatchVersion = 4;
DWORD newTextBoxData[] = { 4,0x237,0x243,0xC8,0x14,0,0,0,0,0,0,2 };//type,x,y,l,h,?,?,?,?,?,?,?(0,257,C8,28)

#define SETFCTADDR(F, I, N) setFctAddr((DWORD*)&N, (HMODULE)offset_##F, (LPCSTR)I)
void setFctAddr(DWORD* addr, HMODULE module, LPCSTR index)
{
    if (index)
    {
        *addr = (DWORD)GetProcAddress(module, index);
        if (!*addr)
        {
            D2String::LogMsg("Bad index fct %d for %08X", index, module);
        }
    }
    else
        *addr = NULL;
}

static time_t getDateFromMacro(char const* time)
{
    char s_month[5];
    int month, day, year;
    struct tm t = { 0 };
    static const char month_names[] = "JanFebMarAprMayJunJulAugSepOctNovDec";

    sscanf(time, "%s %d %d", s_month, &day, &year);

    month = (strstr(month_names, s_month) - month_names) / 3;

    t.tm_mon = month;
    t.tm_mday = day;
    t.tm_year = year - 1900;
    t.tm_isdst = -1;

    return mktime(&t);
}

void __stdcall printPatchVersion(void** childrens, DWORD* sgnNumChildren)
{
    char buf[128] = { 0 };
    time_t t = getDateFromMacro(__DATE__);
    struct tm* p = localtime(&t);
    void* textbox = D2Win::D2CreateTextBox(newTextBoxData);
    childrens[*sgnNumChildren] = textbox;
    Fog::D2Assert((*sgnNumChildren)++ >= 40, "sgnNumChildren < MAX_CHILDREN", __FILE__, __LINE__);
    sprintf(buf, "1.0.00(%04d/%02d/%02d %s)", 1900 + p->tm_year, 1 + p->tm_mon, p->tm_mday, __TIME__);
    D2Win::D2PrintLineOnTextBox(textbox, buf, colorOfPatchVersion);
}


__declspec(naked) void caller_printPatchVersion()
{
    __asm {
        POP ESI
        PUSH DWORD PTR[ESI + 2]
        PUSH DWORD PTR[ESI + 9]
        CALL printPatchVersion
        CALL D2Win::D2CreateTextBox
        JMP ESI
    }
}

#endif
