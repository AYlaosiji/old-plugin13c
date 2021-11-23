class PATCHLOAD_API D2Json
{
private:
	cJSON* Root;

	void AssertObject(void* objectget);

public:
	D2Json();
	~D2Json();

	bool load(const char* filename);

	void unload();

	cJSON* GetRoot();

	cJSON* GetObjectItemInModule(const char* ModuleName, const char* cfgname);

	const bool GetModuleCfgBool(const char* ModuleName, const char* cfgname, bool* objectget);

	const bool GetModuleMapValues(const char* ModuleName, const char* ArrayName, cJSON** vecvalue, unsigned int maxelement);

	const bool GetCfgBool(cJSON* object, const char* cfgname, bool* objectget);

};