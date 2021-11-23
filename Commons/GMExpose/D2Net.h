class PATCHLOAD_API D2Net : public Library<D2Net>
{

	static void SetFunctions();

public:
	static void Init();

public:

	typedef DWORD(__stdcall* TD2NetSendPacketToClient) (BOOL bZero, int nClientID, void* pPacket, int nPacketSize);
	static TD2NetSendPacketToClient D2NetSendPacketToClient;

	typedef DWORD(__stdcall* TD2SendToServer) (DWORD size, DWORD one, void* data);
	static TD2SendToServer D2SendToServer;

};