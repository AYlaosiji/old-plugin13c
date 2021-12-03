#include "d2hd_license.h"
#include "pch.h"

#ifdef MODULES_HIGHRESOLUTION

HANDLE D2HD::Draw::d2mrArchive = nullptr;
D2DrawCell D2HD::Draw::blankCellFile("Sources\\local\\UI\\CHI\\Blank");

D2DrawCell D2HD::Draw::controlPanel800("Sources\\global\\ui\\Panel\\800CtrlPnl7");
D2DrawCell D2HD::Draw::statsButton("Sources\\global\\ui\\PANEL\\level");
D2DrawCell D2HD::Draw::skillButton("Sources\\global\\ui\\PANEL\\level");

D2DrawCell D2HD::Draw::d2mrFancyBorderCorner("Sources\\global\\ui\\Panel\\D2MRFancyBorderCorner");
D2DrawCell D2HD::Draw::neoD2MRFancyBorderCornerBottomLeft("Sources\\global\\ui\\Panel\\NeoD2MRFancyBorderCornerBottomLeft");
D2DrawCell D2HD::Draw::neoD2MRFancyBorderCornerBottomRight("Sources\\global\\ui\\Panel\\NeoD2MRFancyBorderCornerBottomRight");
D2DrawCell D2HD::Draw::neoD2MRFancyBorderCornerTopLeft("Sources\\global\\ui\\Panel\\NeoD2MRFancyBorderCornerTopLeft");
D2DrawCell D2HD::Draw::neoD2MRFancyBorderCornerTopRight("Sources\\global\\ui\\Panel\\NeoD2MRFancyBorderCornerTopRight");

D2DrawCell D2HD::Draw::d2mrFancyBorderInterfaceLeft("Sources\\global\\ui\\Panel\\D2MRFancyBorderInterfaceLeft");
D2DrawCell D2HD::Draw::d2mrFancyBorderInterfaceRight("Sources\\global\\ui\\Panel\\D2MRFancyBorderInterfaceRight");
D2DrawCell D2HD::Draw::neoD2MRFancyBorderInterfaceLeft("Sources\\global\\ui\\Panel\\NeoD2MRFancyBorderInterfaceLeft");
D2DrawCell D2HD::Draw::neoD2MRFancyBorderInterfaceRight("Sources\\global\\ui\\Panel\\NeoD2MRFancyBorderInterfaceRight");

D2DrawCell D2HD::Draw::d2mrFancyBorderLeft("Sources\\global\\ui\\Panel\\D2MRFancyBorderLeft");
D2DrawCell D2HD::Draw::d2mrFancyBorderRight("Sources\\global\\ui\\Panel\\D2MRFancyBorderRight");

D2DrawCell D2HD::Draw::d2mrFancyBorderBottom("Sources\\global\\ui\\Panel\\D2MRFancyBorderBottom");
D2DrawCell D2HD::Draw::d2mrFancyBorderTop("Sources\\global\\ui\\Panel\\D2MRFancyBorderTop");
D2DrawCell D2HD::Draw::neoD2MRFancyBorderBottomLeft("Sources\\global\\ui\\Panel\\NeoD2MRFancyBorderBottomLeft");
D2DrawCell D2HD::Draw::neoD2MRFancyBorderBottomRight("Sources\\global\\ui\\Panel\\NeoD2MRFancyBorderBottomRight");
D2DrawCell D2HD::Draw::neoD2MRFancyBorderTopLeft("Sources\\global\\ui\\Panel\\NeoD2MRFancyBorderTopLeft");
D2DrawCell D2HD::Draw::neoD2MRFancyBorderTopRight("Sources\\global\\ui\\Panel\\NeoD2MRFancyBorderTopRight");

D2DrawCell D2HD::Draw::d2mrFancyHorizontalBar("Sources\\global\\ui\\Panel\\D2MRFancyHorizontalBar");
D2DrawCell D2HD::Draw::d2mrFancyVerticalBar("Sources\\global\\ui\\Panel\\D2MRFancyVerticalBar");

D2DrawCell D2HD::Draw::d2mrFancyPanelHorizontalBar("Sources\\global\\ui\\Panel\\D2MRFancyPanelHorizontalBar");
D2DrawCell D2HD::Draw::d2mrFancyPanelVerticalBar("Sources\\global\\ui\\Panel\\D2MRFancyPanelVerticalBar");
D2DrawCell D2HD::Draw::d2mrFancyPanelFlipHorizontalBar("Sources\\global\\ui\\Panel\\D2MRFancyPanelFlipHorizontalBar");
D2DrawCell D2HD::Draw::d2mrFancyPanelFlipVerticalBar("Sources\\global\\ui\\Panel\\D2MRFancyPanelFlipVerticalBar");

D2DrawCell D2HD::Draw::d2mrFancyPanelLeft("Sources\\global\\ui\\Panel\\D2MRFancyPanelLeft");
D2DrawCell D2HD::Draw::d2mrFancyPanelRight("Sources\\global\\ui\\Panel\\D2MRFancyPanelRight");
D2DrawCell D2HD::Draw::d2mrFancyPanelFlipLeft("Sources\\global\\ui\\Panel\\D2MRFancyPanelFlipLeft");
D2DrawCell D2HD::Draw::d2mrFancyPanelFlipRight("Sources\\global\\ui\\Panel\\D2MRFancyPanelFlipRight");

D2DrawCell D2HD::Draw::d2mrStoneBack("Sources\\global\\ui\\Panel\\D2MRStoneBack");

#ifdef RESOLUTIION1024x720
D2DrawCell D2HD::Draw::resolution1024x720Text("Sources\\local\\UI\\CHI\\1024x720");
#endif
#ifdef RESOLUTIION1280x720
D2DrawCell D2HD::Draw::resolution1280x720Text("Sources\\local\\UI\\CHI\\1280x720");
#endif
#ifdef RESOLUTIION1440x720
D2DrawCell D2HD::Draw::resolution1440x720Text("Sources\\local\\UI\\CHI\\1440x720");
#endif
#ifdef RESOLUTIION1024x768
D2DrawCell D2HD::Draw::resolution1024x768Text("Sources\\local\\UI\\CHI\\1024x768");
#endif
#ifdef RESOLUTIION1280x768
D2DrawCell D2HD::Draw::resolution1280x768Text("Sources\\local\\UI\\CHI\\1280x768");
#endif
#ifdef RESOLUTIION1440x768
D2DrawCell D2HD::Draw::resolution1440x768Text("Sources\\local\\UI\\CHI\\1440x768");
#endif
#ifdef RESOLUTIION1600x900
D2DrawCell D2HD::Draw::resolution1600x900Text("Sources\\local\\UI\\CHI\\1600x900");
#endif
#ifdef RESOLUTIION1068x600
D2DrawCell D2HD::Draw::resolution1068x600Text("Sources\\local\\UI\\CHI\\1068x600");
#endif
#ifdef RESOLUTIION1344x700
D2DrawCell D2HD::Draw::resolution1344x700Text("Sources\\local\\UI\\CHI\\1344x700");
#endif
D2DrawCell D2HD::Draw::resolutionerrorText("Sources\\local\\UI\\CHI\\error");



BOOL __stdcall D2HD::Draw::determineVideoOptionText(struct CellFile**
    outCellFile, void* baseAddress, unsigned int offset,
    struct CellFile* defaultCellFile) 
{

	blankCellFile.loadFileSafely();

#ifdef RESOLUTIION1024x720
	resolution1024x720Text.loadFileSafely();
#endif
#ifdef RESOLUTIION1280x720
	resolution1280x720Text.loadFileSafely();
#endif
#ifdef RESOLUTIION1440x720
	resolution1440x720Text.loadFileSafely();
#endif

#ifdef RESOLUTIION1024x768
	resolution1024x768Text.loadFileSafely();
#endif
#ifdef RESOLUTIION1280x768
	resolution1280x768Text.loadFileSafely();
#endif
#ifdef RESOLUTIION1440x768
	resolution1440x768Text.loadFileSafely();
#endif

#ifdef RESOLUTIION1600x900
	resolution1600x900Text.loadFileSafely();
#endif
#ifdef RESOLUTIION1068x600
    resolution1068x600Text.loadFileSafely();
#endif
#ifdef RESOLUTIION1344x700
    resolution1344x700Text.loadFileSafely();
#endif
    resolutionerrorText.loadFileSafely();


    if (baseAddress == D2Client::VideoOptionCellFileStart && offset == 0x154) 
    {
        if ((D2Client::ptScreenSize->x == 640 && D2Client::ptScreenSize->y == 480)
            || (D2Client::ptScreenSize->x  == 800 && D2Client::ptScreenSize->y == 600)) 
        {
            *outCellFile = defaultCellFile;
        }
#ifdef RESOLUTIION1024x720
        else if (D2Client::ptScreenSize->x == 1024 && D2Client::ptScreenSize->y == 720)
        {
            *outCellFile = resolution1024x720Text.getCellFilePtr();
        }
#endif
#ifdef RESOLUTIION1280x720
        else if (D2Client::ptScreenSize->x == 1280 && D2Client::ptScreenSize->y == 720)
        {
            *outCellFile = resolution1280x720Text.getCellFilePtr();
        }
#endif
#ifdef RESOLUTIION1440x720
        else if (D2Client::ptScreenSize->x == 1440 && D2Client::ptScreenSize->y == 720)
        {
            *outCellFile = resolution1440x720Text.getCellFilePtr();
        }
#endif
#ifdef RESOLUTIION1024x768
        else if (D2Client::ptScreenSize->x == 1024 && D2Client::ptScreenSize->y == 768)
        {
            *outCellFile = resolution1024x768Text.getCellFilePtr();
        }
#endif
#ifdef RESOLUTIION1280x768
        else if (D2Client::ptScreenSize->x == 1280 && D2Client::ptScreenSize->y == 768)
        {
            *outCellFile = resolution1280x768Text.getCellFilePtr();
        }
#endif
#ifdef RESOLUTIION1440x768
        else if (D2Client::ptScreenSize->x == 1440 && D2Client::ptScreenSize->y == 768)
        {
            *outCellFile = resolution1440x768Text.getCellFilePtr();
        }
#endif
#ifdef RESOLUTIION1600x900
        else if (D2Client::ptScreenSize->x == 1600 && D2Client::ptScreenSize->y == 900)
        {
            *outCellFile = resolution1600x900Text.getCellFilePtr();
        }
#endif
#ifdef RESOLUTIION1068x600
        else if (D2Client::ptScreenSize->x == 1068 && D2Client::ptScreenSize->y == 600)
        {
            *outCellFile = resolution1068x600Text.getCellFilePtr();
        }
#endif
#ifdef RESOLUTIION1344x700
        else if (D2Client::ptScreenSize->x == 1344 && D2Client::ptScreenSize->y == 700)
        {
            *outCellFile = resolution1344x700Text.getCellFilePtr();
        }
#endif
        else 
        {
            *outCellFile = resolutionerrorText.getCellFilePtr();
        }
    }
    else 
    {
            *outCellFile = resolutionerrorText.getCellFilePtr();
    }
    return TRUE;
}


void*  __fastcall D2HD::Draw::determineVideoOptionText2(CellFile* assetValueC, DWORD assetValueB, void* assetValueA)
{
    //void* assetValueA;
    //DWORD assetValueB;
    //CellFile* assetValueC;
    CellFile* returnValue;

    //__asm {
    //    MOV assetValueA, EAX
    //    MOV assetValueB, ESI
    //    MOV assetValueC, ECX
    //}

    blankCellFile.loadFileSafely();

#ifdef RESOLUTIION1024x720
    resolution1024x720Text.loadFileSafely();
#endif
#ifdef RESOLUTIION1280x720
    resolution1280x720Text.loadFileSafely();
#endif
#ifdef RESOLUTIION1440x720
    resolution1440x720Text.loadFileSafely();
#endif

#ifdef RESOLUTIION1024x768
    resolution1024x768Text.loadFileSafely();
#endif
#ifdef RESOLUTIION1280x768
    resolution1280x768Text.loadFileSafely();
#endif
#ifdef RESOLUTIION1440x768
    resolution1440x768Text.loadFileSafely();
#endif

#ifdef RESOLUTIION1600x900
    resolution1600x900Text.loadFileSafely();
#endif
#ifdef RESOLUTIION1068x600
    resolution1068x600Text.loadFileSafely();
#endif
#ifdef RESOLUTIION1344x700
    resolution1344x700Text.loadFileSafely();
#endif
    resolutionerrorText.loadFileSafely();

    if (assetValueA == D2Client::VideoOptionCellFileStart && assetValueB == 0x154)
    {
        if ((D2Client::ptScreenSize->x == 640 && D2Client::ptScreenSize->y == 480)
            || (D2Client::ptScreenSize->x == 800 && D2Client::ptScreenSize->y == 600))
        {
            returnValue = assetValueC;
        }
#ifdef RESOLUTIION1024x720
        else if (D2Client::ptScreenSize->x == 1024 && D2Client::ptScreenSize->y == 720)
        {
            returnValue = resolution1024x720Text.getCellFilePtr();
        }
#endif
#ifdef RESOLUTIION1280x720
        else if (D2Client::ptScreenSize->x == 1280 && D2Client::ptScreenSize->y == 720)
        {
            returnValue = resolution1280x720Text.getCellFilePtr();
        }
#endif
#ifdef RESOLUTIION1440x720
        else if (D2Client::ptScreenSize->x == 1440 && D2Client::ptScreenSize->y == 720)
        {
            returnValue = resolution1440x720Text.getCellFilePtr();
        }
#endif
#ifdef RESOLUTIION1024x768
        else if (D2Client::ptScreenSize->x == 1024 && D2Client::ptScreenSize->y == 768)
        {
            returnValue = resolution1024x768Text.getCellFilePtr();
        }
#endif
#ifdef RESOLUTIION1280x768
        else if (D2Client::ptScreenSize->x == 1280 && D2Client::ptScreenSize->y == 768)
        {
            returnValue = resolution1280x768Text.getCellFilePtr();
        }
#endif
#ifdef RESOLUTIION1440x768
        else if (D2Client::ptScreenSize->x == 1440 && D2Client::ptScreenSize->y == 768)
        {
            returnValue = resolution1440x768Text.getCellFilePtr();
        }
#endif
#ifdef RESOLUTIION1600x900
        else if (D2Client::ptScreenSize->x == 1600 && D2Client::ptScreenSize->y == 900)
        {
            returnValue = resolution1600x900Text.getCellFilePtr();
        }
#endif
#ifdef RESOLUTIION1068x600
        else if (D2Client::ptScreenSize->x == 1068 && D2Client::ptScreenSize->y == 600)
        {
            returnValue = resolution1068x600Text.getCellFilePtr();
        }
#endif
#ifdef RESOLUTIION1344x700
        else if (D2Client::ptScreenSize->x == 1344 && D2Client::ptScreenSize->y == 700)
        {
            returnValue = resolution1344x700Text.getCellFilePtr();
        }
#endif
        else
        {
            returnValue = resolutionerrorText.getCellFilePtr();
        }
    }
    else
    {
        //if (assetValueC)returnValue = assetValueC;
        //else 
            returnValue = resolutionerrorText.getCellFilePtr();
    }
    return returnValue;
}


void D2HD::Draw::drawControlPanel800Foreground() 
{
    controlPanel800.loadFileSafely();

    controlPanel800.setFrame(0);
    controlPanel800.draw(0, D2Client::ptScreenSize->y, 0xFFFFFFFF, 5, nullptr);

    controlPanel800.setFrame(1);
    controlPanel800.draw((D2Client::ptScreenSize->x  / 2) - 235, D2Client::ptScreenSize->y, 0xFFFFFFFF, 5, nullptr);

    controlPanel800.setFrame(2);
    controlPanel800.draw((D2Client::ptScreenSize->x  / 2) - 107, D2Client::ptScreenSize->y, 0xFFFFFFFF, 5, nullptr);

    controlPanel800.setFrame(3);
    controlPanel800.draw((D2Client::ptScreenSize->x  / 2) + 21, D2Client::ptScreenSize->y, 0xFFFFFFFF, 5, nullptr);

    controlPanel800.setFrame(4);
    controlPanel800.draw((D2Client::ptScreenSize->x  / 2) + 149, D2Client::ptScreenSize->y, 0xFFFFFFFF, 5, nullptr);

    controlPanel800.setFrame(5);
    controlPanel800.draw(D2Client::ptScreenSize->x  - 117, D2Client::ptScreenSize->y, 0xFFFFFFFF, 5, nullptr);
}

void D2HD::Draw::drawControlPanelBackground() 
{
    D2DrawCell& panelLeft = isFlipD2MRControlPanel ? d2mrFancyPanelFlipLeft : d2mrFancyPanelLeft;
    D2DrawCell& panelRight =isFlipD2MRControlPanel ? d2mrFancyPanelFlipRight : d2mrFancyPanelRight;
    D2DrawCell& panelHorizontalBar = isFlipD2MRControlPanel? d2mrFancyPanelFlipHorizontalBar : d2mrFancyPanelHorizontalBar;

    panelLeft.loadFileSafely();
    panelRight.loadFileSafely();
    panelHorizontalBar.loadFileSafely();

    panelLeft.setFrame(0);
    panelRight.setFrame(0);
    panelHorizontalBar.setFrame(0);

    panelLeft.draw((117 + 48), D2Client::ptScreenSize->y - 1, 0xFFFFFFFF, 5, 0);
    panelRight.draw((D2Client::ptScreenSize->x  - 117 - 48 - 238), D2Client::ptScreenSize->y - 1, 0xFFFFFFFF, 5, nullptr);

    for (int i = 0; ((i * 254) + (117 + 48 + 238)) < ((D2Client::ptScreenSize->x  / 2) - 128); i++) {
        panelHorizontalBar.draw(((i * 254) + (117 + 48 + 238)), D2Client::ptScreenSize->y - 1, 0xFFFFFFFF, 5, nullptr);
    }

    for (int i = 0; ((D2Client::ptScreenSize->x  - 117 - 48 - 238) - (i * 254)) > ((D2Client::ptScreenSize->x  / 2) + 128); i++) {
        panelHorizontalBar.draw(((D2Client::ptScreenSize->x  - 117 - 48 - 238) - ((i + 1) * 254)), D2Client::ptScreenSize->y - 1, 0xFFFFFFFF, 5, nullptr);
    }
}

void D2HD::Draw::drawPanelBackground() 
{
    switch (*D2Client::PanelOpenMode) 
    {
    case 1:
        D2HD::Draw::drawRightPanelBackground();
        D2HD::Draw::drawRightPanelBorders();
        break;

    case 2:
        D2HD::Draw::drawLeftPanelBackground();
        D2HD::Draw::drawLeftPanelBorders();
        break;

    case 3:
        D2HD::Draw::drawLeftPanelBackground();
        D2HD::Draw::drawRightPanelBackground();

        D2HD::Draw::drawLeftPanelBorders();
        D2HD::Draw::drawRightPanelBorders();
        break;

    default:
        break;
    }
}

// Draws a background on opened left panels to cover up extra space.
void D2HD::Draw::drawLeftPanelBackground() 
{
    d2mrStoneBack.loadFileSafely();

    int basePositionX = (D2Client::ptScreenSize->x  / 2);

    // Draw background pieces
    const int backWidth = 256;
    const int backHeight = 256;

    for (int row = 0; (row * backHeight) < D2Client::ptScreenSize->y; row++) {
        int backBasePositionY = ((row + 1) * backHeight);

        for (int col = 0; (int)(basePositionX - (col * backWidth)) >= 0; col++) {
            d2mrStoneBack.setFrame(((row % 2) * 2) + (col % 2));
            int backBasePositionX = basePositionX - ((col + 1) * backWidth);

            d2mrStoneBack.draw(backBasePositionX, backBasePositionY, leftPanelBackgroundColor.getBGRFormat(), 5, nullptr);
        }
    }

    // Draw the ribbons only if the user has it enabled AND the game resolution allows the ribbons to be drawn without
    // problems.
    if (!isEnableD2MRBackgroundRibbon
        && ((D2Client::ptScreenSize->y - ((256 + 256 + 40) + 48)) <= (2 * (256 + 28)))) 
    {
        return;
    }

    int basePositionY = (D2Client::ptScreenSize->y / 2) - 300;

    d2mrFancyBorderLeft.loadFileSafely();
    d2mrFancyHorizontalBar.loadFileSafely();
    d2mrFancyVerticalBar.loadFileSafely();

    d2mrFancyBorderLeft.setFrame(0);
    d2mrFancyBorderLeft.draw((basePositionX - 60), (basePositionY + 256) + (256 + 256 + 40), leftPanelBorderColor.getBGRFormat(), 5, nullptr);
    d2mrFancyBorderLeft.setFrame(1);
    d2mrFancyBorderLeft.draw((basePositionX - 60), (basePositionY + 256 + 28) + (256 + 256 + 40), leftPanelBorderColor.getBGRFormat(), 5, nullptr);

    d2mrFancyBorderLeft.draw((basePositionX - 60), (basePositionY), leftPanelBorderColor.getBGRFormat(), 5, nullptr);
    d2mrFancyBorderLeft.setFrame(0);
    d2mrFancyBorderLeft.draw((basePositionX - 60), (basePositionY - 28), leftPanelBorderColor.getBGRFormat(), 5, nullptr);

    if (!isEnableD2MRPanelBorderStyle) 
    {
        basePositionX += 2;
    }

    d2mrFancyHorizontalBar.setFrame(2);

    d2mrFancyHorizontalBar.draw((basePositionX - 400 - 35), (basePositionY + (256 + 256 + 40)), leftPanelBorderColor.getBGRFormat(), 5, nullptr);
    d2mrFancyHorizontalBar.draw((basePositionX - 400 - 35), (basePositionY + 60), leftPanelBorderColor.getBGRFormat(), 5, nullptr);

    for (int i = 0; (basePositionX - 400 - 35) - (i * 256) >= 0; i++) {
        d2mrFancyHorizontalBar.setFrame(std::abs(i - 1) % 2);
        d2mrFancyHorizontalBar.draw((basePositionX - 400 - 35) - ((i + 1) * 256), (basePositionY + (256 + 256 + 40)), leftPanelBorderColor.getBGRFormat(), 5, nullptr);
        d2mrFancyHorizontalBar.draw((basePositionX - 400 - 35) - ((i + 1) * 256), (basePositionY + 60), leftPanelBorderColor.getBGRFormat(), 5, nullptr);
    }

    d2mrFancyVerticalBar.setFrame(2);

    d2mrFancyVerticalBar.draw((basePositionX - 400), (basePositionY), leftPanelBorderColor.getBGRFormat(), 5, nullptr);

    for (int i = 0; ((basePositionY - 35) - (i * 256)) >= 0; i++) {
        d2mrFancyVerticalBar.setFrame(std::abs(i - 1) % 2);
        d2mrFancyVerticalBar.draw((basePositionX - 400), ((basePositionY - 35) - (i * 256)), leftPanelBorderColor.getBGRFormat(), 5, nullptr);
    }

    for (int i = 0; ((basePositionY + (256 + 256 + 40)) + (i * 256)) < (D2Client::ptScreenSize->y); i++) {
        d2mrFancyVerticalBar.setFrame(i % 2);
        d2mrFancyVerticalBar.draw((basePositionX - 400), ((basePositionY + (256 + 256 + 40)) + ((i + 1) * 256)), leftPanelBorderColor.getBGRFormat(), 5, nullptr);
    }
}

void D2HD::Draw::drawLeftPanelBorders() 
{
    D2DrawCell& borderLeft = isEnableD2MRPanelBorderStyle? d2mrFancyBorderInterfaceLeft : neoD2MRFancyBorderInterfaceLeft;
    D2DrawCell& borderBottomLeft = isEnableD2MRPanelBorderStyle? d2mrFancyBorderBottom : neoD2MRFancyBorderBottomLeft;
    D2DrawCell& borderTopLeft = isEnableD2MRPanelBorderStyle ? d2mrFancyBorderTop : neoD2MRFancyBorderTopLeft;
    D2DrawCell& borderCornerBottomLeft = isEnableD2MRPanelBorderStyle ? d2mrFancyBorderCorner : neoD2MRFancyBorderCornerBottomLeft;
    D2DrawCell& borderCornerTopLeft = isEnableD2MRPanelBorderStyle ? d2mrFancyBorderCorner : neoD2MRFancyBorderCornerTopLeft;

    borderLeft.loadFileSafely();
    borderBottomLeft.loadFileSafely();
    borderTopLeft.loadFileSafely();
    borderCornerBottomLeft.loadFileSafely();
    borderCornerTopLeft.loadFileSafely();

    int basePositionX = (D2Client::ptScreenSize->x  / 2) - 400;
    int basePositionY = (D2Client::ptScreenSize->y / 2) - 300;

    if (!isEnableD2MRPanelBorderStyle) 
    {
        basePositionX += 2;
    }

    // Draw top border pieces
    borderTopLeft.setFrame(0);
    borderTopLeft.draw((basePositionX + 56), (basePositionY + 60), leftPanelBorderColor.getBGRFormat(), 5, nullptr);
    borderTopLeft.setFrame(1);
    borderTopLeft.draw((basePositionX + 56) + 256, (basePositionY + 60), leftPanelBorderColor.getBGRFormat(), 5, nullptr);

    // Draw bottom border pieces
    borderBottomLeft.setFrame(0);
    borderBottomLeft.draw((basePositionX + 56), (basePositionY + 256) + (256 + 40), leftPanelBorderColor.getBGRFormat(), 5, nullptr);
    borderBottomLeft.setFrame(1);
    borderBottomLeft.draw((basePositionX + 56) + 256, (basePositionY + 256) + (256 + 40), leftPanelBorderColor.getBGRFormat(), 5, nullptr);

    // Draw top left corner border pieces
    borderCornerTopLeft.setFrame(0);
    borderCornerTopLeft.draw((basePositionX + 56) + 284, (basePositionY + 60), leftPanelBorderColor.getBGRFormat(), 5, nullptr);

    // Draw bottom left corner border pieces
    borderCornerBottomLeft.setFrame(0);
    borderCornerBottomLeft.draw((basePositionX + 56) + 284, (basePositionY)+(256 + 256 + 40), leftPanelBorderColor.getBGRFormat(), 5, nullptr);

    // Draw left border pieces
    borderLeft.setFrame(0);
    borderLeft.draw(basePositionX, (basePositionY + 256), leftPanelBorderColor.getBGRFormat(), 5, nullptr);
    borderLeft.setFrame(1);
    borderLeft.draw(basePositionX, (basePositionY + 256) + 256, leftPanelBorderColor.getBGRFormat(), 5, nullptr);
    borderLeft.setFrame(2);
    borderLeft.draw(basePositionX, (basePositionY + 256) + (256 + 40), leftPanelBorderColor.getBGRFormat(), 5, nullptr);
}

void D2HD::Draw::drawRightPanelBackground() {
    d2mrStoneBack.loadFileSafely();
    d2mrStoneBack.setFrame(0);

    int basePositionX = (D2Client::ptScreenSize->x  / 2);

    // Draw background pieces
    const int backWidth = 256;
    const int backHeight = 256;

    for (int row = 0; (row * backHeight) < D2Client::ptScreenSize->y; row++) {
        int backBasePositionY = ((row + 1) * backHeight);

        for (int col = 0; basePositionX + (col * backWidth) < D2Client::ptScreenSize->x ; col++) {
            d2mrStoneBack.setFrame(((row % 2) * 2) + ((col + 1) % 2));
            int backBasePositionX = basePositionX + (col * backWidth);

            d2mrStoneBack.draw(backBasePositionX, backBasePositionY, rightPanelBackgroundColor.getBGRFormat(), 5, 0);
        }
    }

    // Draw the ribbons only if the user has it enabled AND the game resolution allows the ribbons to be drawn without
    // problems.
    if (!isEnableD2MRBackgroundRibbon
        && ((D2Client::ptScreenSize->y - ((256 + 256 + 40) + 48)) <= (2 * (256 + 28)))) {
        return;
    }

    d2mrFancyBorderRight.loadFileSafely();
    d2mrFancyHorizontalBar.loadFileSafely();
    d2mrFancyVerticalBar.loadFileSafely();

    int basePositionY = (D2Client::ptScreenSize->y / 2) - 300;

    d2mrFancyBorderRight.setFrame(0);
    d2mrFancyBorderRight.draw((basePositionX), (basePositionY + 256) + (256 + 256 + 40), rightPanelBackgroundColor.getBGRFormat(), 5, nullptr);
    d2mrFancyBorderRight.setFrame(1);
    d2mrFancyBorderRight.draw((basePositionX), (basePositionY + 256 + 28) + (256 + 256 + 40), rightPanelBackgroundColor.getBGRFormat(), 5, nullptr);

    d2mrFancyBorderRight.draw((basePositionX), (basePositionY), rightPanelBackgroundColor.getBGRFormat(), 5, nullptr);
    d2mrFancyBorderRight.setFrame(0);
    d2mrFancyBorderRight.draw((basePositionX), (basePositionY - 28), rightPanelBackgroundColor.getBGRFormat(), 5, nullptr);

    for (int i = 0; (basePositionX + 400) + (i * 256) < (D2Client::ptScreenSize->x ); i++) {
        d2mrFancyHorizontalBar.setFrame(i % 2);
        d2mrFancyHorizontalBar.draw((basePositionX + 400) + (i * 256), (basePositionY + (256 + 256 + 40)), rightPanelBackgroundColor.getBGRFormat(), 5, nullptr);
        d2mrFancyHorizontalBar.draw((basePositionX + 400) + (i * 256), (basePositionY + 60), rightPanelBackgroundColor.getBGRFormat(), 5, nullptr);
    }

    d2mrFancyVerticalBar.setFrame(2);
    d2mrFancyVerticalBar.draw((basePositionX + 400 - 60), (basePositionY), rightPanelBackgroundColor.getBGRFormat(), 5, nullptr);

    for (int i = 0; ((basePositionY - 35) - (i * 256)) >= 0; i++) {
        d2mrFancyVerticalBar.setFrame(std::abs(i - 1) % 2);
        d2mrFancyVerticalBar.draw((basePositionX + 400 - 60), ((basePositionY - 35) - (i * 256)), rightPanelBackgroundColor.getBGRFormat(), 5, nullptr);
    }

    for (int i = 0;
        ((basePositionY + (256 + 256 + 40)) + (i * 256)) < (D2Client::ptScreenSize->y);
        i++) {
        d2mrFancyVerticalBar.setFrame(i % 2);
        d2mrFancyVerticalBar.draw((basePositionX + 400 - 60), ((basePositionY + (256 + 256 + 40)) + ((i + 1) * 256)), rightPanelBackgroundColor.getBGRFormat(), 5, nullptr);
    }
}

void D2HD::Draw::drawRightPanelBorders() 
{
    D2DrawCell& borderRight = isEnableD2MRPanelBorderStyle ? d2mrFancyBorderInterfaceRight : neoD2MRFancyBorderInterfaceRight;
    D2DrawCell& borderBottomRight = isEnableD2MRPanelBorderStyle ? d2mrFancyBorderBottom : neoD2MRFancyBorderBottomRight;
    D2DrawCell& borderTopRight = isEnableD2MRPanelBorderStyle ? d2mrFancyBorderTop : neoD2MRFancyBorderTopRight;
    D2DrawCell& borderCornerBottomRight = isEnableD2MRPanelBorderStyle ? d2mrFancyBorderCorner : neoD2MRFancyBorderCornerBottomRight;
    D2DrawCell& borderCornerTopRight = isEnableD2MRPanelBorderStyle ? d2mrFancyBorderCorner : neoD2MRFancyBorderCornerTopRight;

    borderRight.loadFileSafely();
    borderBottomRight.loadFileSafely();
    borderTopRight.loadFileSafely();
    borderCornerBottomRight.loadFileSafely();
    borderCornerTopRight.loadFileSafely();

    int basePositionX = (D2Client::ptScreenSize->x  / 2);
    int basePositionY = (D2Client::ptScreenSize->y / 2) - 300;

    // Draw top border pieces
    borderTopRight.setFrame(0);
    borderTopRight.draw((basePositionX + 60), (basePositionY + 60), rightPanelBackgroundColor.getBGRFormat(), 5, nullptr);
    borderTopRight.setFrame(1);
    borderTopRight.draw((basePositionX + 60) + 256, (basePositionY + 60), rightPanelBackgroundColor.getBGRFormat(), 5, nullptr);

    // Draw bottom border pieces
    borderBottomRight.setFrame(0);
    borderBottomRight.draw((basePositionX + 60), (basePositionY + 256) + (256 + 40), rightPanelBackgroundColor.getBGRFormat(), 5, nullptr);
    borderBottomRight.setFrame(1);
    borderBottomRight.draw((basePositionX + 60) + 256, (basePositionY + 256) + (256 + 40), rightPanelBackgroundColor.getBGRFormat(), 5, nullptr);

    // Draw top right corner border pieces
    borderCornerTopRight.setFrame(0);
    borderCornerTopRight.draw((basePositionX), (basePositionY + 60), rightPanelBackgroundColor.getBGRFormat(), 5, nullptr);

    // Draw bottom right corner border pieces
    borderCornerBottomRight.setFrame(0);
    borderCornerBottomRight.draw((basePositionX), (basePositionY + 256) + (256 + 40), rightPanelBackgroundColor.getBGRFormat(), 5, nullptr);

    // Draw left border pieces
    borderRight.setFrame(0);
    borderRight.draw((basePositionX + 320), (basePositionY + 256), rightPanelBackgroundColor.getBGRFormat(), 5, nullptr);
    borderRight.setFrame(1);
    borderRight.draw((basePositionX + 320), (basePositionY + 256) + 256, rightPanelBackgroundColor.getBGRFormat(), 5, nullptr);
    borderRight.setFrame(2);
    borderRight.draw((basePositionX + 320), (basePositionY + 256) + (256 + 40), rightPanelBackgroundColor.getBGRFormat(), 5, nullptr);
}

void __stdcall D2HD::Draw::drawActiveStatsButton() 
{
    Fog::D2Assert(1, "Fix It", __FILE__, __LINE__);
    statsButton.loadFileSafely();
    //statsButton.setFrame(*D2CLIENT_StatsButtonClicked);
    statsButton.draw((D2Client::ptScreenSize->x  / 2) - 194, D2Client::ptScreenSize->y - 8, 0xFFFFFFFF, 5, nullptr);
}

void __stdcall D2HD::Draw::drawInactiveStatsButton() {
    statsButton.loadFileSafely();
    statsButton.setFrame(2);
    statsButton.draw((D2Client::ptScreenSize->x  / 2) - 194, D2Client::ptScreenSize->y - 8, 0xFFFFFFFF, 5, nullptr);
}

void __stdcall D2HD::Draw::drawStatsButtonText() 
{
    bool isMouseOverStatsButton = false;
    D2HD::isMouseOverStatsButton(&isMouseOverStatsButton);

	if (isMouseOverStatsButton && !*D2Client::EscMenuOpened)
	{
		wchar_t* statsButtonText = D2Lang::D2GetStringFromIndex(3986);
		D2Win::D2PrintString(statsButtonText, (D2Client::ptScreenSize->x / 2) - 179, D2Client::ptScreenSize->y - 50, 0, 1);
	}
}

void __stdcall D2HD::Draw::drawActiveSkillButton() 
{
    Fog::D2Assert(1, "Fix It", __FILE__, __LINE__);
    skillButton.loadFileSafely();
    //skillButton.setFrame(*D2CLIENT_SkillButtonClicked);
    skillButton.draw((D2Client::ptScreenSize->x  / 2) + 163, D2Client::ptScreenSize->y - 8, 0xFFFFFFFF, 5, nullptr);
}

void __stdcall D2HD::Draw::drawInactiveSkillButton() 
{
    skillButton.loadFileSafely();
    skillButton.setFrame(2);
    skillButton.draw((D2Client::ptScreenSize->x  / 2) + 163, D2Client::ptScreenSize->y - 8, 0xFFFFFFFF, 5, nullptr);
}

void __stdcall D2HD::Draw::drawSkillButtonText() 
{
    bool isMouseOverSkillButton = false;
    D2HD::isMouseOverSkillButton(&isMouseOverSkillButton);

    if (isMouseOverSkillButton && !*D2Client::EscMenuOpened)
    {
        wchar_t* skillButtonText = D2Lang::D2GetStringFromIndex(3987);
        D2Win::D2PrintString(skillButtonText, (D2Client::ptScreenSize->x  / 2) + 178, D2Client::ptScreenSize->y - 50, 0, 1);
    }
}

void __stdcall D2HD::Draw::unloadCellFiles(CellFile** original) 
{
    blankCellFile.unloadFileSafely();
    controlPanel800.unloadFileSafely();
    statsButton.unloadFileSafely();
    skillButton.unloadFileSafely();

    d2mrFancyBorderCorner.unloadFileSafely();
    neoD2MRFancyBorderCornerBottomLeft.unloadFileSafely();
    neoD2MRFancyBorderCornerBottomRight.unloadFileSafely();
    neoD2MRFancyBorderCornerTopLeft.unloadFileSafely();
    neoD2MRFancyBorderCornerTopRight.unloadFileSafely();

    d2mrFancyBorderInterfaceLeft.unloadFileSafely();
    d2mrFancyBorderInterfaceRight.unloadFileSafely();
    neoD2MRFancyBorderInterfaceLeft.unloadFileSafely();
    neoD2MRFancyBorderInterfaceRight.unloadFileSafely();

    d2mrFancyBorderLeft.unloadFileSafely();
    d2mrFancyBorderRight.unloadFileSafely();

    d2mrFancyBorderBottom.unloadFileSafely();
    d2mrFancyBorderTop.unloadFileSafely();
    neoD2MRFancyBorderBottomLeft.unloadFileSafely();
    neoD2MRFancyBorderBottomRight.unloadFileSafely();
    neoD2MRFancyBorderTopLeft.unloadFileSafely();
    neoD2MRFancyBorderTopRight.unloadFileSafely();

    d2mrFancyHorizontalBar.unloadFileSafely();
    d2mrFancyVerticalBar.unloadFileSafely();
    d2mrFancyPanelFlipHorizontalBar.unloadFileSafely();
    d2mrFancyPanelFlipVerticalBar.unloadFileSafely();

    d2mrFancyPanelHorizontalBar.unloadFileSafely();
    d2mrFancyPanelVerticalBar.unloadFileSafely();

    d2mrFancyPanelLeft.unloadFileSafely();
    d2mrFancyPanelRight.unloadFileSafely();
    d2mrFancyPanelFlipLeft.unloadFileSafely();
    d2mrFancyPanelFlipRight.unloadFileSafely();

    d2mrStoneBack.unloadFileSafely();


#ifdef RESOLUTIION1024x720
    resolution1024x720Text.unloadFileSafely();
#endif
#ifdef RESOLUTIION1280x720
    resolution1280x720Text.unloadFileSafely();
#endif
#ifdef RESOLUTIION1440x720
    resolution1440x720Text.unloadFileSafely();
#endif
#ifdef RESOLUTIION1024x768
    resolution1024x768Text.unloadFileSafely();
#endif
#ifdef RESOLUTIION1280x768
    resolution1280x768Text.unloadFileSafely();
#endif
#ifdef RESOLUTIION1440x768
    resolution1440x768Text.unloadFileSafely();
#endif
#ifdef RESOLUTIION1600x900
	resolution1600x900Text.unloadFileSafely();
#endif
#ifdef RESOLUTIION1068x600
	resolution1068x600Text.unloadFileSafely();
#endif
#ifdef RESOLUTIION1344x700
	resolution1344x700Text.unloadFileSafely();
#endif
	resolutionerrorText.unloadFileSafely();

    *original = *D2Client::PanelBorderImage;
}

#endif