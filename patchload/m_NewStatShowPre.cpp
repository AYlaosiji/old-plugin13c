#include"pch.h"
#ifdef MODULES_NEWSTATSHOW
statsInterfaceBIN statsInterface[nbStatsInterface] = {0};

DWORD bDontPrintBorder = false;

int selectedPage = 0;
int lastPage = 0;
int extraHiddenPage = 0;

void GoNextStatPage()
{
	selectedPage++;
	if (selectedPage > lastPage)
		selectedPage = 0;
}

void GoPreviousStatPage()
{
	selectedPage--;
	if (selectedPage < 0)
		selectedPage = lastPage;
}

void GoStatPage(int page)
{
	if ((page >= 0) && (page <= lastPage + (D2Gfx::D2GetResolution() ? extraHiddenPage : 0)))
		selectedPage = page;
}

int GetCurrentPage()
{
	return selectedPage;
}

bool isOnStatsPage(int x, int y)
{
	if (x < D2Client::ptScreenSize->x / 2
		&& y < (D2Client::ptScreenSize->y - 16))
		return true;
	return false;
}
#endif