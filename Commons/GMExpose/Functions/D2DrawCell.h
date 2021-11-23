class D2DrawCell 
{
public:
    PATCHLOAD_API D2DrawCell(const char* fileName);
    PATCHLOAD_API  ~D2DrawCell();

    PATCHLOAD_API void draw(int x, int y, unsigned int color, int transTable, unsigned char* pPalette) const;
    PATCHLOAD_API void drawVerticalCrop(int x, int y, unsigned int gama, int nsize, int nDrawType) const;
    PATCHLOAD_API void loadFileSafely();
    PATCHLOAD_API void unloadFileSafely();
    PATCHLOAD_API bool isFileLoaded() const;

    PATCHLOAD_API int getFrame() const;
    PATCHLOAD_API void setFrame(int frame);
    PATCHLOAD_API CellFile* getCellFilePtr() const;


private:
	std::unique_ptr<struct sDrawImageInfo> pCellContext;
	std::string fileName;
	void setCellFilePtr(CellFile* pCellFile);
	D2DrawCell() = delete;
};


