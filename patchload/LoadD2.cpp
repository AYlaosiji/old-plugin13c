#include"pch.h"
BOOL LoadD2::IsD2GdiLoad = FALSE;
BOOL LoadD2::IsD2GlideLoad = FALSE;

void LoadD2::Init()
{
	D2Client::Init();
	D2Game::Init();
	D2Common::Init();
	D2Lang::Init();
	D2Gfx::Init();
	D2Net::Init();
	D2Win::Init();
	D2Launch::Init();
	Fog::Init();
	D2Cmp::Init();
	Storm::Init();
	D2DDraw::Init();
	D2Direct3D::Init();
	//由于客户端使用D2Gfx加载，d2gfx加载了哪个dll，那么就会hook到哪个dll上
	//服务器端对这两个dll无所谓hook不hook
	if (GetModuleHandle("D2Gdi"))
	{
		D2Gdi::Init();
		IsD2GdiLoad = TRUE;
	}

	if (GetModuleHandle("D2Glide"))
	{
		D2Glide::Init();
		IsD2GlideLoad = TRUE;
	}

}

void LoadD2::Hook()
{
	D2Client::HookLibrary();
	D2Game::HookLibrary();
	D2Common::HookLibrary();
	D2Lang::HookLibrary();
	D2Gfx::HookLibrary();
	D2Net::HookLibrary();
	D2Win::HookLibrary();
	D2Launch::HookLibrary();
	Fog::HookLibrary();
	D2Cmp::HookLibrary();
	Storm::HookLibrary();
	D2DDraw::HookLibrary();
	D2Direct3D::HookLibrary();
	if (IsD2GdiLoad)
		D2Gdi::HookLibrary();
	if (IsD2GlideLoad)
		D2Glide::HookLibrary();
}

void LoadD2::UnHook()
{
	D2Client::UnhookLibrary();
	D2Game::UnhookLibrary();
	D2Common::UnhookLibrary();
	D2Lang::UnhookLibrary();
	D2Gfx::UnhookLibrary();
	D2Net::UnhookLibrary();
	D2Win::UnhookLibrary();
	D2Launch::UnhookLibrary();
	Fog::UnhookLibrary();
	D2Cmp::UnhookLibrary();
	Storm::UnhookLibrary();
	D2DDraw::UnhookLibrary();
	D2Direct3D::UnhookLibrary();
	if (IsD2GdiLoad)
		D2Gdi::UnhookLibrary();
	if (IsD2GlideLoad)
		D2Glide::UnhookLibrary();
}
