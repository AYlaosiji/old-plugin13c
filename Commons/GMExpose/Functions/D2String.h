class PATCHLOAD_API D2String
{
private:
	static BOOL GamePrintString(LPCSTR buf);

	static BOOL GamePrintInfo(LPCSTR buf);

	static BOOL GamePrintError(LPCSTR buf);

	static DWORD FormatPacket(BOOL bReceived, const BYTE* aPacket, DWORD aLen, LPSTR lpszBuffer, DWORD dwMaxChars, BOOL bUseColor);

public:
	//�ļ������patchload_sj.log����
	static void LogMsg(const char* pFormat, ...);

	//�ڷ���������ҷ�����Ϣ
	static void __fastcall SendClientMessage(NetClient* pClient, BYTE msgType, char* FakeName, const char* FakeMessage);

	//֧������$$��ɫ���
	static void ReplaceColorSpecs(LPWSTR lpwsz);

	//��Ϸ�ڴ�ӡ����
	static BOOL GameErrorf(LPCSTR lpszFormat, ...);

	//��Ϸ�ڴ�ӡ��ʾ��Ϣ
	static BOOL GameInfof(LPCSTR lpszFormat, ...);

	//��Ϸ�ڴ�ӡ�ı�
	static BOOL GameStringf(LPCSTR lpszFormat, ...);

	//��Ϸ�ڴ�ӡ���
	static BOOL GamePrintPacket(BOOL bReceived, const BYTE* aPacket, DWORD aLen);
};