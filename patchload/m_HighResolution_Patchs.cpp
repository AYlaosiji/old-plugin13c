#include "d2hd_license.h"
#include"pch.h"
#ifdef MODULES_HIGHRESOLUTION
void __stdcall D2HD::getModeParams(int mode, int* width, int* height)
{
    if ((size_t)mode < D2HD::D2HDResolution::getResolutions().size())
    {
        *width = D2HD::D2HDResolution::getResolutions().at(mode).getWidth();
        *height = D2HD::D2HDResolution::getResolutions().at(mode).getHeight();
    }
    else
    {
        *width = 640;
        *height = 480;
    }

    if ((*width > MAXIMUM_WIDTH
        || *height > MAXIMUM_HEIGHT)
        || (*width < MINIMUM_WIDTH
            || *height < MINIMUM_HEIGHT))
    {
        MessageBoxW(nullptr,
            L"You defined a new resolution that breaks expected limits. Change those limits in D2HD/D2HDConfig.h.",
            L"Defined Resolution Exceeds Limit", MB_OK | MB_ICONSTOP);
        std::exit(0);
    }
}

void D2HD::repositionPanels()
{
    *D2Client::ptWindowStartX = (D2Client::ptScreenSize->x / 2) - 320;
    *D2Client::ptNegWindowStartY = (D2Client::ptScreenSize->y - 480) / -2;
}

void __stdcall D2HD::getPatchedResolutionMode(int* resolutionMode)
{
    *resolutionMode = (D2Client::ptScreenSize->x >= 800) ? 2 : 0;
}

void __stdcall D2HD::resizeGameLogicResolution(int mode)
{
    D2HD::getModeParams(mode, (int*)D2Client::WindowWidth, (int*)D2Client::WindowHeight);
    *D2Client::InventoryArrangeMode = mode;
}

void __stdcall D2HD::getGameWindowWidth(int* width)
{
    *width = *D2Gfx::WindowWidth;
}

void __stdcall D2HD::getGameWindowHeight(int* height)
{
    *height = *D2Gfx::WindowHeight;
}

void __stdcall D2HD::setResolutionMode(int* gameResolution,
    int configResolution)
{
    if (configResolution == 1)
    {
        *gameResolution = 2;
    }
    else {
        *gameResolution = configResolution;
    }
}

void __stdcall D2HD::setResolutionModeFromMenu(int* mode) 
{
    int currentMode = D2Gfx::D2GetResolution();

    if (currentMode == 0) {
        *mode = 2;
    }
    else if ((size_t)currentMode >= D2HDResolution::getResolutions().size() -
        1) {
        *mode = 0;
    }
    else {
        *mode = currentMode + 1;
    }
}

void __stdcall D2HD::isMouseOverStatsButton(bool* isMouseOver)
{
    const int leftSide = (D2Client::ptScreenSize->x / 2) - 193;
    const int rightSide = leftSide + 32;
    const int topSide = D2Client::ptScreenSize->y - 41;
    const int bottomSide = topSide + 32;

    const int mousePositionX = *D2Client::ptMouseX;
    const int mousePositionY = *D2Client::ptMouseY;

    *isMouseOver = ((mousePositionX >= leftSide && mousePositionX <= rightSide)
        && (mousePositionY >= topSide && mousePositionY <= bottomSide));
}

void __stdcall D2HD::isMouseOverSkillButton(bool* isMouseOver)
{
    const int leftSide = (D2Client::ptScreenSize->x / 2) + 164;
    const int rightSide = leftSide + 32;
    const int topSide = D2Client::ptScreenSize->y - 41;
    const int bottomSide = topSide + 32;

    const int mousePositionX = *D2Client::ptMouseX;
    const int mousePositionY = *D2Client::ptMouseY;

    *isMouseOver = ((mousePositionX >= leftSide && mousePositionX <= rightSide)
        && (mousePositionY >= topSide && mousePositionY <= bottomSide));
}

void __stdcall D2HD::setGDIForegroundRenderWidth(int mode)
{
    int discarded = 0;
    D2HD::getModeParams(mode, D2Gdi::ForegroundRenderWidth, &discarded);
}

void __stdcall D2HD::setDirectDrawRenderResolution(int mode, int* width, int* height)
{
    D2HD::getModeParams(mode, width, D2DDraw::WindowHeight);
    *height = *D2DDraw::WindowHeight;
}

void __stdcall D2HD::setDirect3DRenderResolution(int mode)
{
    D2HD::getModeParams(mode, D2Direct3D::WindowWidth, D2Direct3D::WindowHeight);
}

void __stdcall D2HD::setGlideRenderResolution(int newGameResolutionMode,int* glideResolutionMode)
{
    D2HD::getModeParams(newGameResolutionMode, D2Glide::WindowWidth, D2Glide::WindowHeight);

    switch (newGameResolutionMode) {
    case 0:
        *glideResolutionMode = 7;
        break;

    case 1:
        *glideResolutionMode = 8;
        break;

    default:
        *glideResolutionMode = (newGameResolutionMode - 2) + 8;
        break;
    }

    // Apply special case for /r/Diablo2Resurgence
    if ( *D2Glide::WindowWidth == 1068 && *D2Glide::WindowHeight == 600)
    {
        *glideResolutionMode = 0xFF;
    }

    *D2Glide::SpritesInited = (newGameResolutionMode != 1);
}

void __stdcall D2HD::setupGlideWindowSize(int newGlideResolutionMode) 
{
    const int resolutionMode = (newGlideResolutionMode == 7) ? 0 : ((
        newGlideResolutionMode - 8) + 2);
    D2HD::getModeParams(resolutionMode, *Glide3x::WindowWidthPtr, *Glide3x::WindowHeightPtr);
}
#endif