#include"pch.h"
void D2Win::Init()
{
	Name = "D2Win.dll";
	Offset = LoadDiabloLibrary();
	SetFunctions();
}


void D2Win::SetFunctions()
{
	D2GetPixelLen = (TD2GetPixelLen)D2Win::GetAddressByOrdinal(10028);
	D2PrintPopup = (TD2PrintPopup)D2Win::GetAddressByOrdinal(10085);
	D2LoadCellFile=(TD2LoadCellFile)D2Win::GetAddressByOrdinal(10111);
	D2PrintString = (TD2PrintString)D2Win::GetAddressByOrdinal(10150);
	D2DisplayBlendedText = (TD2DisplayBlendedText)D2Win::GetAddressByOrdinal(10162);
	D2SetFontSize = (TD2SetFontSize)D2Win::GetAddressByOrdinal(10184);
	D2CreateTextBox = (TD2CreateTextBox)D2Win::GetAddressByOrdinal(10098);
	D2PrintLineOnTextBox = (TD2PrintLineOnTextBox)D2Win::GetAddressByOrdinal(10022);
}

D2Win::TD2GetPixelLen D2Win::D2GetPixelLen;
D2Win::TD2PrintPopup D2Win::D2PrintPopup;
D2Win::TD2LoadCellFile D2Win::D2LoadCellFile;
D2Win::TD2PrintString D2Win::D2PrintString;
D2Win::TD2SetFontSize D2Win::D2SetFontSize;
D2Win::TD2DisplayBlendedText D2Win::D2DisplayBlendedText;
D2Win::TD2CreateTextBox D2Win::D2CreateTextBox;
D2Win::TD2PrintLineOnTextBox D2Win::D2PrintLineOnTextBox;

