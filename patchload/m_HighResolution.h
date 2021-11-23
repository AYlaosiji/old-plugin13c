#define MODULES_HIGHRESOLUTION

#define MAXIMUM_WIDTH 1600
#define MAXIMUM_HEIGHT 900
#define MINIMUM_WIDTH 640
#define MINIMUM_HEIGHT 480

//#define RESOLUTIION1024x720
//#define RESOLUTIION1280x720
//#define RESOLUTIION1440x720
#define RESOLUTIION1024x768
#define RESOLUTIION1280x768
//#define RESOLUTIION1440x768
#define RESOLUTIION1600x900
//#define RESOLUTIION1068x600
#define RESOLUTIION1344x700

#include "m_HighResolution_HD.h"
#include "m_HighResolution_Color.h"
#include "m_HighResolution_Draw.h"
#include "m_HighResolution_Inventory.h"
#include "m_HighResolution_Patchs.h"

class Glide3x : public Library<Glide3x >
{
	static void SetFunctions()
	{
		WindowWidthPtr = (int**)GetAddress(0x1C9A0);
		WindowHeightPtr = (int**)GetAddress(0x1C82C);
	}
public:
	static void Init()
	{
		Name = "glide3x.dll";
		Offset = LoadDiabloLibrary();
		SetFunctions();
	}
	static int** WindowWidthPtr;
	static int** WindowHeightPtr;
};


extern BOOL isFlipD2MRControlPanel;
extern BOOL isEnableD2MRBackgroundRibbon;
extern D2HD::D2HDColor leftPanelBackgroundColor;
extern D2HD::D2HDColor leftPanelBorderColor;
extern D2HD::D2HDColor rightPanelBackgroundColor;
extern D2HD::D2HDColor rightPanelBorderColor;
extern BOOL isEnableD2MRPanelBorderStyle;

void m_HighResolution_LoadCfg();
void m_HighResolution_Install();
void m_HighResolution_UnInstall();
