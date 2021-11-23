class PATCHLOAD_API D2String
{
private:
	static BOOL GamePrintString(LPCSTR buf);

	static BOOL GamePrintInfo(LPCSTR buf);

	static BOOL GamePrintError(LPCSTR buf);

	static DWORD FormatPacket(BOOL bReceived, const BYTE* aPacket, DWORD aLen, LPSTR lpszBuffer, DWORD dwMaxChars, BOOL bUseColor);

public:
	//文件输出到patchload_sj.log里面
	static void LogMsg(const char* pFormat, ...);

	//在服务器给玩家发送信息
	static void __fastcall SendClientMessage(NetClient* pClient, BYTE msgType, char* FakeName, const char* FakeMessage);

	//支持输入$$颜色序号
	static void ReplaceColorSpecs(LPWSTR lpwsz);

	//游戏内打印错误
	static BOOL GameErrorf(LPCSTR lpszFormat, ...);

	//游戏内打印提示信息
	static BOOL GameInfof(LPCSTR lpszFormat, ...);

	//游戏内打印文本
	static BOOL GameStringf(LPCSTR lpszFormat, ...);

	//游戏内打印封包
	static BOOL GamePrintPacket(BOOL bReceived, const BYTE* aPacket, DWORD aLen);
};