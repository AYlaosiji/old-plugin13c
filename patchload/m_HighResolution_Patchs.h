namespace D2HD
{
	void __stdcall getModeParams(int mode, int* width, int* height);
	void getModeParamsInterception107();
	void getModeParamsInterception111();

	void repositionPanels();
	void repositionPanelsInterception();

	void __stdcall getPatchedResolutionMode(int* resolutionMode);
	void getPatchedResolutionModeInterception();

	void __stdcall resizeGameLogicResolution(int mode);
	void resizeGameLogicResolutionInterception();

	void __stdcall getGameWindowWidth(int* width);
	void resizeGameWindowResizeWidthInterception();

	void __stdcall getGameWindowHeight(int* height);
	void resizeGameWindowResizeHeightInterception();

	void __stdcall setResolutionMode(int* gameResolution, int configResolution);
	void setResolutionModeEAXInterception();
	void setResolutionModeEDIInterception();

	void __stdcall setResolutionModeFromMenu(int* mode);
	void setResolutionModeFromMenuInterception();

	void __stdcall isMouseOverStatsButton(bool* isMouseOver);
	void isMouseOverStatsButtonInterception();

	void __stdcall isMouseOverSkillButton(bool* isMouseOver);
	void isMouseOverSkillButtonInterception();

	void setGDIRenderResolutionInterception();

	void __stdcall setGDIForegroundRenderWidth(int mode);
	void setGDIForegroundRenderWidthInterception();

	void __stdcall setDirectDrawRenderResolution(int mode, int* width, int* height);
	void setDirectDrawRenderResolutionInterception();

	void __stdcall setDirect3DRenderResolution(int mode);
	void setDirect3DRenderResolutionInterception();

	void __stdcall setGlideRenderResolution(int newGameResolutionMode, int* glideResolutionMode);
	void setGlideRenderResolutionInterception();

	void __stdcall setupGlideWindowSize(int newGlideResolutionMode);
	void setupGlideWindowSizeInterception();
}