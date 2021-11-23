#include "pch.h"

D2DrawCell::D2DrawCell(const char* fileNames) :fileName(fileNames)
{
    pCellContext = std::unique_ptr<struct sDrawImageInfo>(new sDrawImageInfo);
    memset(pCellContext.get(), 0, sizeof(sDrawImageInfo));
}

D2DrawCell::~D2DrawCell() 
{
    unloadFileSafely();
}

void D2DrawCell::draw(int x, int y, unsigned int color, int transTable, unsigned char* pPalette) const
{
    D2Gfx::D2DrawImage((sDrawImageInfo*)pCellContext.get(), x, y, color, transTable, pPalette);
}

void D2DrawCell::drawVerticalCrop(int x, int y, unsigned int gama, int nsize, int nDrawType) const
{
    D2Gfx::D2DrawVerticalCropImage((sDrawImageInfo*)pCellContext.get(), x, y, gama,nsize, nDrawType);
}

void D2DrawCell::loadFileSafely() {
    if (isFileLoaded())
    {
        return;
    }

    setCellFilePtr(D2Win::D2LoadCellFile(fileName.c_str(), 0));
    if (getCellFilePtr() == nullptr || (unsigned int)getCellFilePtr() == 1)
    {
        MessageBoxW(nullptr, L"CellFile asset failed to load.", L"Diablo II Error", MB_OK | MB_ICONERROR);
        std::exit(0);
    }
}

void D2DrawCell::unloadFileSafely()
{
    if (isFileLoaded())
    {
        D2Cmp::VD2FreeImage(getCellFilePtr());
        Fog::D2FogMemDeAlloc(getCellFilePtr(), __FILE__, __LINE__, NULL);

        setCellFilePtr(nullptr);
    }
}

bool D2DrawCell::isFileLoaded() const {
    return getCellFilePtr() != nullptr;
}

int D2DrawCell::getFrame() const {
    int frame = 0;
    frame = ((sDrawImageInfo*)pCellContext.get())->dwCellNo;

    return frame;
}

void D2DrawCell::setFrame(int frame)
{
    ((sDrawImageInfo*)pCellContext.get())->dwCellNo = frame;
}

CellFile* D2DrawCell::getCellFilePtr() const
{
    CellFile* pCellFile = nullptr;
    pCellFile = ((sDrawImageInfo*)pCellContext.get())->pCellFile;
    return pCellFile;
}

void D2DrawCell::setCellFilePtr(CellFile* pCellFile)
{
    ((sDrawImageInfo*)pCellContext.get())->pCellFile = pCellFile;
}