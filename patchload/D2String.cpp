#include "pch.h"

	BOOL D2String::GamePrintString(LPCSTR buf)
	{
		wchar_t wbuf[512];
		::MultiByteToWideChar(CP_ACP, 0, buf, -1, wbuf, 512);
		ReplaceColorSpecs(wbuf);
		D2Client::D2ClientMsgTop(wbuf, 0);
		return TRUE;
	}

	BOOL D2String::GamePrintInfo(LPCSTR buf)
	{
		char head[] = "$$0[$$9Info$$0]$$0:";
		LPSTR newBuf = new char[strlen(head) + strlen(buf) + 5];
		sprintf_s(newBuf, strlen(head) + strlen(buf) + 5, "%s$$0 %s", head, buf);
		GamePrintString(newBuf);
		delete[]newBuf;
		return TRUE;
	}

	BOOL D2String::GamePrintError(LPCSTR buf)
	{
		char head[] = "$$0[$$1Error$$0]$$0:";
		LPSTR newBuf = new char[strlen(head) + strlen(buf) + 5];
		sprintf_s(newBuf, strlen(head) + strlen(buf) + 5, "%s$$0 %s", head, buf);
		GamePrintString(newBuf);
		delete[]newBuf;
		return TRUE;
	}

	DWORD D2String::FormatPacket(BOOL bReceived, const BYTE* aPacket, DWORD aLen, LPSTR lpszBuffer, DWORD dwMaxChars, BOOL bUseColor)
	{
		if (lpszBuffer == NULL)
			return 0;

		lpszBuffer[0] = '\0';
		if (aPacket == NULL || aLen == 0)
			return 0;

		char sz[64] = "";

		if (bUseColor)
		{
			if (bReceived)
				sprintf(sz, "$$4R $$2%3d$$4:$$0", aLen);
			else
				sprintf(sz, "$$4S $$2%3d$$4:$$0", aLen);
		}
		else
		{
			if (bReceived)
				sprintf(sz, "R %3d:", aLen);
			else
				sprintf(sz, "S %3d:", aLen);
		}


		DWORD dwCopied = strlen(sz);
		if (dwCopied > dwMaxChars)
			return 0;

		strcat(lpszBuffer, sz);

		for (DWORD i = 0; i < aLen && dwCopied + 3 <= dwMaxChars; i++)
		{
			sprintf(sz, "  %02X", aPacket[i]);
			strcat(lpszBuffer, sz);
			dwCopied += 3;
		}

		return dwCopied;
	}

	void D2String::LogMsg(const char* pFormat, ...)
	{
		char log_file[MAX_PATH] = "";
		char info[MAX_PATH] = "";
		sprintf(info, "patchload_sj.log");
		_getcwd(log_file, MAX_PATH);
		if (log_file[strlen(log_file)] != '\\')
			strcat(log_file, "\\");
		strcat(log_file, info);
		va_list lArgs;
		va_start(lArgs, pFormat);

		FILE* lDebug = fopen(log_file, "a");

		if (lDebug != NULL)
		{
			time_t timep;
			struct tm* p;
			time(&timep);
			p = localtime(&timep);
			fprintf(lDebug, "Time:%04d-%02d-%02d %02d:%02d:%02d  ", p->tm_year + 1900, p->tm_mon + 1, p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec);
			vfprintf(lDebug, pFormat, lArgs);
			fprintf(lDebug, "\n");
			fclose(lDebug);
		}
		else
		{
			Fog::D2Assert(TRUE, "Failed In Open File", __FILE__, __LINE__);
		}
		va_end(lArgs);
	}

	void __fastcall D2String::SendClientMessage(NetClient* pClient, BYTE msgType, char* FakeName, const char* FakeMessage)
	{
		D2GSPacketSrv26 data = { NULL };
		data.nHeader = 0x26;
		data.nMessageType = msgType;
		data.Unk1 = 0x02;
		data.Unk2 = 0x09;
		data.Unk2_0 = 0x00;
		data.nMessageColor = 0x00;
		data.nNameColor = 0x00;
		char* szName = data.szStrings;
		strcat(szName, FakeName);
		char* szMessage = (szName + (strlen(szName) + 1));
		sprintf(szMessage, FakeMessage);
		CopyMemory(&data.szStrings, szName, sizeof(502));
		D2Game::D2SendPacketToClient(pClient, &data, sizeof(D2GSPacketSrv26));
	}

	void D2String::ReplaceColorSpecs(LPWSTR lpwsz)
	{
		if (lpwsz == NULL)
			return;
		const int LEN = wcslen(lpwsz);
		for (int i = 0; i < LEN; i++)
		{
			if (lpwsz[i] == 0xf8f5 || lpwsz[i] == 0x3f)
			{
				lpwsz[i] = 0xff;
			}
			if (i > 0 && lpwsz[i - 1] == 36 && lpwsz[i] == 36)
			{
				lpwsz[i - 1] = 0xff;
				lpwsz[i] = 99;
			}
		}
	}

	BOOL D2String::GameErrorf(LPCSTR lpszFormat, ...)
	{
		if (lpszFormat == NULL || lpszFormat[0] == '\0')
			return FALSE;

		char szString[256] = "";
		va_list args;
		va_start(args, lpszFormat);
		_vsnprintf_s(szString, 255, lpszFormat, args);
		va_end(args);
		return GamePrintError(szString);
	}

	BOOL D2String::GameInfof(LPCSTR lpszFormat, ...)
	{
		if (lpszFormat == NULL || lpszFormat[0] == '\0')
			return FALSE;

		TCHAR szString[256] = "";
		va_list args;
		va_start(args, lpszFormat);
		_vsnprintf_s(szString, 255, lpszFormat, args);
		va_end(args);
		return GamePrintInfo(szString);
	}

	BOOL D2String::GameStringf(LPCSTR lpszFormat, ...)
	{
		if (lpszFormat == NULL || lpszFormat[0] == '\0')
			return FALSE;

		TCHAR szString[256] = "";
		va_list args;
		va_start(args, lpszFormat);
		_vsnprintf_s(szString, 255, lpszFormat, args);
		va_end(args);
		return GamePrintString(szString);
	}

	BOOL D2String::GamePrintPacket(BOOL bReceived, const BYTE* aPacket, DWORD aLen)
	{
		char szBuffer[1024] = "";
		if (!FormatPacket(bReceived, aPacket, aLen, szBuffer, 1023, TRUE))
			return FALSE;

		return GamePrintInfo(szBuffer);
	}
