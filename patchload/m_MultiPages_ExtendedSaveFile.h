
BYTE* readExtendedSaveFile(char* name, DWORD* size);
void writeExtendedSaveFile(char* name, BYTE* data, DWORD size);
int loadExtendedSaveFile(UnitAny* ptChar, BYTE data[], DWORD maxSize);//WORKS
void saveExtendedSaveFile(UnitAny* ptChar, BYTE** data, DWORD* maxSize, DWORD* curSize);
void backupExtendedSaveFile(char* name);