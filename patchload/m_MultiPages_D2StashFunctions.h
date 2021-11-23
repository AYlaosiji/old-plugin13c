/*=================================================================
	File created by Yohann NICOLAS.

  infinity Stash gestion

=================================================================*/
#pragma once
void toggleToSharedStash(UnitAny* ptChar);
void toggleToSelfStash(UnitAny* ptChar);
void setCurrentStashIndex(UnitAny* ptChar, int index);
void selectPreviousStash(UnitAny* ptChar);
void selectNextStash(UnitAny* ptChar);
void selectPreviousIndexStash(UnitAny* ptChar);
void selectNextIndexStash(UnitAny* ptChar);
void selectPrevious2Stash(UnitAny* ptChar);
void selectNext2Stash(UnitAny* ptChar);
void selectPreviousIndex2Stash(UnitAny* ptChar);
void selectNextIndex2Stash(UnitAny* ptChar);
void swapStash(UnitAny* ptChar, DWORD page, bool toggle);
void renameCurrentStash(UnitAny* ptChar, char* name);
void insertStash(UnitAny* ptChar);
bool deleteStash(UnitAny* ptChar, bool isClient);

void selectStash(UnitAny* ptChar, Stash* newStash);
void setSelectedStashClient(DWORD stashId, DWORD stashFlags, DWORD flags, bool bOnlyItems);

Stash* addStash(UnitAny* ptChar, bool isShared);
DWORD loadStashList(UnitAny* ptChar, BYTE* data, DWORD maxSize, DWORD* curSize, bool isShared);
DWORD loadExStash(UnitAny* ptChar, BYTE data[], DWORD maxSize, DWORD& curSize);
DWORD loadExPet(UnitAny* ptChar, BYTE data[], DWORD maxSize, DWORD& curSize);
DWORD loadExCursor(UnitAny* ptChar, BYTE data[], DWORD maxSize, DWORD& curSize);
void saveStashList(UnitAny* ptChar, Stash* ptStash, BYTE** data, DWORD* maxSize, DWORD* curSize);
void saveExStash(UnitAny* ptChar, BYTE** data, DWORD* maxSize, DWORD* curSize);
void saveExPet(UnitAny* ptChar, BYTE** data, DWORD* maxSize, DWORD* curSize);
void saveExCursor(UnitAny* ptChar, BYTE** data, DWORD* maxSize, DWORD* curSize);
void Install_MultiPageStash();

/*================================= END OF FILE =================================*/