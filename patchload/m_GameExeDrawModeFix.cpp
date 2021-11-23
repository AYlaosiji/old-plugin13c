#include"pch.h"
#ifdef MODULES_GAMEEXEDRAWMODEFIX

void __cdecl InterceptionFunc_01_A();
void __cdecl InterceptionFunc_02_A();
void __cdecl InterceptionFunc_01_B();
void __cdecl InterceptionFunc_02_B();
void __cdecl InterceptionFunc_01_C();
void __cdecl InterceptionFunc_02_C();

void m_GameExeDrawModeFix_LoadCfg()
{

}


void m_GameExeDrawModeFix_Install()
{
        DWORD offset;
        DWORD offset2;

        offset = D2DDraw::GetAddress(0x9467);
        Memory::SetCursor(offset);
        Memory::ChangeByte(0x6A, 0xE8);
        Memory::ChangeCallA(0x6A006A00, (DWORD)InterceptionFunc_01_A);
        Memory::ChangeByte(0x00, 0xEB);
        Memory::ChangeByte(0x68, 0x0F);

        offset = D2DDraw::GetAddress(0x94A2);
        Memory::SetCursor(offset);
        Memory::ChangeByte(0x6A, 0xE8);
        Memory::ChangeCallA(0x6A086A00, (DWORD)InterceptionFunc_02_A);
        Memory::ChangeByte(0x01, 0xEB);
        Memory::ChangeByte(0x6A, 0x0F);
        Memory::ChangeByte(0x10, 0x90);

        offset = D2Direct3D::GetAddress(0x10002);
        offset2= D2Direct3D::GetAddress(0x6f8942d0-0x6f880000);
        Memory::SetCursor(offset);
        Memory::ChangeByte(0x53, 0x90);
        Memory::ChangeByte(0x53, 0x90);
        Memory::ChangeByte(0x53, 0x90);
        Memory::ChangeByte(0x68, 0xE8);
        Memory::ChangeCallA(offset2, (DWORD)InterceptionFunc_01_B);
        Memory::ChangeByte(0xff, 0xeb);
        Memory::ChangeByte(0x15, 0x04);

        offset = D2Direct3D::GetAddress(0x10030);
        Memory::SetCursor(offset);
        Memory::ChangeByte(0x53, 0xE8);
        Memory::ChangeCallA(0x016A086A, (DWORD)InterceptionFunc_02_B);
        Memory::ChangeByte(0x6A, 0xEB);
        Memory::ChangeByte(0x10, 0x0F);

        offset = D2Direct3D::GetAddress(0xBA2E);
        Memory::SetCursor(offset);
        Memory::ChangeByte(0x10, 0x20);

        if (LoadD2::IsD2GlideLoad)
        {
            offset = D2Glide::GetAddress(0x7A29);
            offset2 = D2Glide::GetAddress(0x6F862438 - 0x6F850000);
            Memory::SetCursor(offset);
            Memory::ChangeByte(0x55, 0x90);
            Memory::ChangeByte(0x55, 0x90);
            Memory::ChangeByte(0x55, 0x90);
            Memory::ChangeByte(0x68, 0xE8);
            Memory::ChangeCallA(offset2, (DWORD)InterceptionFunc_01_C);
            Memory::ChangeByte(0xff, 0xeb);
            Memory::ChangeByte(0x15, 0x04);

            offset = D2Glide::GetAddress(0x7A57);
            Memory::SetCursor(offset);
            Memory::ChangeByte(0x55, 0xE8);
            Memory::ChangeCallA(0x016A086A, (DWORD)InterceptionFunc_02_C);
            Memory::ChangeByte(0x6A, 0xEB);
            Memory::ChangeByte(0x10, 0x0E);
        }
}

void m_GameExeDrawModeFix_UnInstall()
{

}



HDC __cdecl SGD2FDF_D2DDraw_CreateCompatibleDC() 
{
	return CreateCompatibleDC(nullptr);
}

HBITMAP __cdecl SGD2FDF_D2DDraw_CreateCompatibleBitmap(HDC hdc) 
{
	return CreateCompatibleBitmap(hdc, 8, 16);
}

HDC __cdecl SGD2FDF_D2Direct3D_CreateCompatibleDC() 
{
    return CreateCompatibleDC(nullptr);
}

HBITMAP __cdecl SGD2FDF_D2Direct3D_CreateCompatibleBitmap(HDC hdc) 
{
    return CreateCompatibleBitmap(hdc, 8, 16);
}

HDC __cdecl SGD2FDF_D2Glide_CreateCompatibleDC() 
{
    return CreateCompatibleDC(nullptr);
}

HBITMAP __cdecl SGD2FDF_D2Glide_CreateCompatibleBitmap(HDC hdc) 
{
    return CreateCompatibleBitmap(hdc, 8, 16);
}


__declspec(naked) void __cdecl InterceptionFunc_01_A()
{
    __asm
    {
        push ebp
         mov ebp, esp

        push ecx
        push edx

        call SGD2FDF_D2DDraw_CreateCompatibleDC

        pop edx
        pop ecx

        leave
        ret
    }

}

__declspec(naked) void __cdecl InterceptionFunc_02_A()
{
    __asm
    {
        push ebp
        mov ebp, esp

        // Original code.
        mov edi, eax
        mov dword ptr[ebp + 0x2C], edi

        push ecx
        push edx

        push esi
        call SGD2FDF_D2DDraw_CreateCompatibleBitmap
        add esp, 4

        pop edx
        pop ecx

        leave
        ret
    }
}

__declspec(naked) void __cdecl InterceptionFunc_01_B() 
{
    __asm
    {
        push ebp
        mov ebp, esp

        push ecx
        push edx

        call SGD2FDF_D2Direct3D_CreateCompatibleDC

        pop edx
        pop ecx

        leave
        ret
    }
}

__declspec(naked) void __cdecl InterceptionFunc_02_B()
{
    __asm
    {
        push ebp
        mov ebp, esp

        // Original code.
        mov esi, eax
        mov dword ptr[ebp + 0x30], eax

        push ecx
        push edx

        push esi
        call SGD2FDF_D2Direct3D_CreateCompatibleBitmap
        add esp, 4

        pop edx
        pop ecx

        leave
        ret
    }
}


__declspec(naked) void __cdecl InterceptionFunc_01_C() 
{
    __asm
    {
        push ebp
        mov ebp, esp

        push ecx
        push edx

        call SGD2FDF_D2Glide_CreateCompatibleDC

        pop edx
        pop ecx

        leave
        ret
    }
}

__declspec(naked) void __cdecl InterceptionFunc_02_C() 
{
    __asm
    {
        push ebp
        mov ebp, esp

        // Original code.
        mov edi, eax
        mov dword ptr[esp + 0x28], edi

        push ecx
        push edx

        push esi
        call SGD2FDF_D2Glide_CreateCompatibleBitmap
        add esp, 4

        pop edx
        pop ecx

        leave
        ret
    }
  
}

#endif