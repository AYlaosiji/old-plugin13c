
#define MILIEU(X,L,N) (X + ((N<L)? (L-N)/2 : 0))

#define nbStatsInterface 512
struct statsInterfaceBIN
{
	WORD enabled;
	WORD page;
	WORD x;
	WORD y;
	WORD color;
	WORD font;
	WORD statsID;
};

extern statsInterfaceBIN statsInterface[nbStatsInterface];
extern DWORD bDontPrintBorder;

extern int selectedPage;
extern int lastPage;
extern int extraHiddenPage ;

void GoNextStatPage();
void GoPreviousStatPage();
void GoStatPage(int page);
int GetCurrentPage();
bool isOnStatsPage(int x, int y);