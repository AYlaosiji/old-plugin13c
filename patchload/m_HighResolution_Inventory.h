namespace D2HD 
{
    namespace Inventory 
    {
        void __stdcall getBeltPos(int nIndex, int nMode, BeltBox* out, int nBox);
        void __stdcall getBeltsTxtRecord(int nIndex, int nMode, BeltsTxt* out);
        void __stdcall getInventorySize(int nRecord, int nScreenMode, InventorySize* pOutRect);
        void __stdcall getInventoryGrid(int nRecord, int nScreenMode, InventoryGrid* pOut);
        void __stdcall getInventoryField(int nRecord, int nScreenMode, InventoryLayout* pOut, int nField);
    }
}