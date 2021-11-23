namespace D2HD 
{
    namespace Draw 
    {
        extern HANDLE d2mrArchive;
        extern D2DrawCell blankCellFile;

        extern D2DrawCell controlPanel800;
        extern D2DrawCell statsButton;
        extern D2DrawCell skillButton;

        extern D2DrawCell d2mrFancyBorderCorner;
        extern D2DrawCell neoD2MRFancyBorderCornerBottomLeft;
        extern D2DrawCell neoD2MRFancyBorderCornerBottomRight;
        extern D2DrawCell neoD2MRFancyBorderCornerTopLeft;
        extern D2DrawCell neoD2MRFancyBorderCornerTopRight;

        extern D2DrawCell d2mrFancyBorderInterfaceLeft;
        extern D2DrawCell d2mrFancyBorderInterfaceRight;
        extern D2DrawCell neoD2MRFancyBorderInterfaceLeft;
        extern D2DrawCell neoD2MRFancyBorderInterfaceRight;

        extern D2DrawCell d2mrFancyBorderLeft;
        extern D2DrawCell d2mrFancyBorderRight;

        extern D2DrawCell d2mrFancyBorderBottom;
        extern D2DrawCell d2mrFancyBorderTop;
        extern D2DrawCell neoD2MRFancyBorderBottomLeft;
        extern D2DrawCell neoD2MRFancyBorderBottomRight;
        extern D2DrawCell neoD2MRFancyBorderTopLeft;
        extern D2DrawCell neoD2MRFancyBorderTopRight;

        extern D2DrawCell d2mrFancyHorizontalBar;
        extern D2DrawCell d2mrFancyVerticalBar;
        extern D2DrawCell d2mrFancyPanelFlipHorizontalBar;
        extern D2DrawCell d2mrFancyPanelFlipVerticalBar;

        extern D2DrawCell d2mrFancyPanelHorizontalBar;
        extern D2DrawCell d2mrFancyPanelVerticalBar;

        extern D2DrawCell d2mrFancyPanelLeft;
        extern D2DrawCell d2mrFancyPanelRight;
        extern D2DrawCell d2mrFancyPanelFlipLeft;
        extern D2DrawCell d2mrFancyPanelFlipRight;

        extern D2DrawCell d2mrStoneBack;
        //
#ifdef RESOLUTIION1024x720
        extern D2DrawCell resolution1024x720Text;
#endif
#ifdef RESOLUTIION1280x720
        extern D2DrawCell resolution1280x720Text;
#endif
#ifdef RESOLUTIION1440x720
        extern D2DrawCell resolution1440x720Text;
#endif

#ifdef RESOLUTIION1024x768
        extern D2DrawCell resolution1024x768Text;
#endif
#ifdef RESOLUTIION1280x768
        extern D2DrawCell resolution1280x768Text;
#endif
#ifdef RESOLUTIION1440x768
        extern D2DrawCell resolution1440x768Text;
#endif

#ifdef RESOLUTIION1600x900
        extern D2DrawCell resolution1600x900Text;
#endif
#ifdef RESOLUTIION1068x600
        extern D2DrawCell resolution1068x600Text;
#endif
#ifdef RESOLUTIION1344x700
        extern D2DrawCell resolution1344x700Text;
#endif
        extern D2DrawCell resolutionerrorText;

        extern "C" 
        {
            BOOL __stdcall determineVideoOptionText( struct CellFile** outCellFile, void* baseAddress, unsigned int offset, struct CellFile* defaultCellFile);
            void* __fastcall determineVideoOptionText2(CellFile* assetValueC, DWORD assetValueB, void* assetValueA);

            void determineVideoOptionTextInterception();

            void drawPanelBackground();
            void drawPanelBackgroundInterception();
            void drawLeftPanelBackground();
            void drawLeftPanelBorders();
            void drawRightPanelBackground();
            void drawRightPanelBorders();
            void drawLeftPanelBorders();
            void drawRightPanelBorders();

            void drawControlPanel800Foreground();
            void drawControlPanel800ForegroundInterception();

            void drawControlPanelBackground();
            void drawControlPanelBackgroundInterception();

            void __stdcall drawActiveStatsButton();
            void drawActiveStatsButtonInterception();
            void __stdcall drawInactiveStatsButton();
            void drawInactiveStatsButtonInterception();
            void __stdcall drawStatsButtonText();
            void drawStatsButtonTextInterception();

            void __stdcall drawActiveSkillButton();
            void drawActiveSkillButtonInterception();
            void __stdcall drawInactiveSkillButton();
            void drawInactiveSkillButtonInterception();
            void __stdcall drawSkillButtonText();
            void drawSkillButtonTextInterception();

            void unloadCellFile(CellFile** cellFile);
            void __stdcall unloadCellFiles(CellFile** orignal);
            void unloadCellFilesInterception();
        }
    }
}