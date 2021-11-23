#include"pch.h"
#ifdef MODULES_HIGHRESOLUTION
std::vector<D2HD::D2HDResolution> D2HD::D2HDResolution::resolutions = 
{
    D2HD::D2HDResolution(640, 480),
	D2HD::D2HDResolution(800, 600),
    D2HD::D2HDResolution(800, 600),

#ifdef RESOLUTIION1024x720
	D2HD::D2HDResolution(1024, 720),
#endif
#ifdef RESOLUTIION1280x720
	D2HD::D2HDResolution(1280, 720),
#endif
#ifdef RESOLUTIION1440x720
	D2HD::D2HDResolution(1440, 720),
#endif

#ifdef RESOLUTIION1024x768
	D2HD::D2HDResolution(1024, 768),
#endif
#ifdef RESOLUTIION1280x768
	D2HD::D2HDResolution(1280, 768),
#endif
#ifdef RESOLUTIION1440x768
	D2HD::D2HDResolution(1440, 768),
#endif

#ifdef RESOLUTIION1600x900
	D2HD::D2HDResolution(1600, 900),
#endif
#ifdef RESOLUTIION1068x600
	D2HD::D2HDResolution(1068, 600),
#endif
#ifdef RESOLUTIION1344x700
	D2HD::D2HDResolution(1344, 700),
#endif

};

D2HD::D2HDResolution::D2HDResolution(const int width,const int height) : width(width), height(height) 
{
}

int D2HD::D2HDResolution::getWidth() const 
{
    return D2HD::D2HDResolution::width;
}

int D2HD::D2HDResolution::getHeight() const 
{
    return D2HD::D2HDResolution::height;
}

bool D2HD::D2HDResolution::operator==(const D2HD::D2HDResolution& other) const 
{
    return D2HD::D2HDResolution::width == other.width
        && D2HD::D2HDResolution::height == other.height;
}

std::vector<D2HD::D2HDResolution>& D2HD::D2HDResolution::getResolutions() 
{
    if (D2Gfx::D2GetRenderMode() == D2RenderModes::VIDEO_MODE_DDRAW
        || D2Gfx::D2GetRenderMode() == D2RenderModes::VIDEO_MODE_D3D) 
    {
        D2HD::D2HDResolution::removeNonStandardResolutions();
    }

    return D2HD::D2HDResolution::resolutions;
}

void D2HD::D2HDResolution::removeNonStandardResolutions() {
    // Enumerate all valid resolutions for checking.
    std::vector<D2HD::D2HDResolution> compatibleResolutions;

    DEVMODEW devMode;
    devMode.dmSize = sizeof(DEVMODEW);

    for (DWORD i = 0; EnumDisplaySettingsW(nullptr, i, &devMode); i++) {
        compatibleResolutions.push_back(D2HD::D2HDResolution(devMode.dmPelsWidth,
            devMode.dmPelsHeight));
    }

    // If a resolution is not listed in EnumDisplaySettings, then remove it to prevent crash.
    for (auto it = D2HD::D2HDResolution::resolutions.cbegin();
        it != D2HD::D2HDResolution::resolutions.cend();) {
        if (std::find(compatibleResolutions.cbegin(), compatibleResolutions.cend(),
            *it) == compatibleResolutions.cend()) {
            it = D2HD::D2HDResolution::resolutions.erase(it);
        }
        else {
            it++;
        }
    }
}
#endif