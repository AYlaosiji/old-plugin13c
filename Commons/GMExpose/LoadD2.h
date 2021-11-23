
#include"..\Commons\GMExpose\Library.h"
#include"..\Commons\GMExpose\D2Client.h"
#include"..\Commons\GMExpose\D2Game.h"
#include"..\Commons\GMExpose\D2Common.h"
#include"..\Commons\GMExpose\D2Lang.h"
#include"..\Commons\GMExpose\D2Gfx.h"
#include"..\Commons\GMExpose\D2Net.h"
#include"..\Commons\GMExpose\D2Win.h"
#include"..\Commons\GMExpose\D2Launch.h"
#include"..\Commons\GMExpose\Fog.h"
#include"..\Commons\GMExpose\D2Cmp.h"
#include "..\Commons\GMExpose\Storm.h"
#include "..\Commons\GMExpose\D2DDraw.h"
#include "..\Commons\GMExpose\D2Direct3D.h"
#include "..\Commons\GMExpose\D2Glide.h"
#include "..\Commons\GMExpose\D2Gdi.h"

class  PATCHLOAD_API LoadD2
{
public:

	static BOOL IsD2GdiLoad;
	static BOOL IsD2GlideLoad;

	static void Init();

	static void Hook();

	static void UnHook();
};