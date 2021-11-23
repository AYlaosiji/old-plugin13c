class cfgload
{
	static cJSON* Root;//动态

public:
#ifndef CFGLOAD_NAME
#define CFGLOAD_NAME "patchload_sj.json"
#endif 

#define CFGLOAD_MODULE "Modules"
#define CFGLOAD_MODULE_DESCRIPTION "Description"
#define CFGLOAD_MODULE_ISON "IsOn"
#define CFGLOAD_MODULE_HOKKEY "Hot Key"
#define CFGLOAD_INSTEAD_GLOBAL "Global Instead List"
#define CFGLOAD_INSTEAD_VK "VK Instead List"
#define CFGLOAD_INSTEAD_BYTECOLOUR "BYTE Colour Instead List"
#define CFGLOAD_INSTEAD_UNITTN "Unit TN Instead List"

	static bool Init()
	{
		FILE* f; long len;
		char config_file[_MAX_PATH] = "";
		_getcwd(config_file, MAX_PATH);
		if (config_file[strlen(config_file)] != '\\')
			strcat(config_file, "\\");
		strcat(config_file, CFGLOAD_NAME);
		fopen_s(&f, config_file, "rb");
		if (f == NULL)
		{
			return false;
		}

		fseek(f, 0, SEEK_END);
		len = ftell(f);
		fseek(f, 0, SEEK_SET);

		char* data = (char*)malloc(len + 1);
		if (!data)return false;
		fread(data, 1, len, f);
		Root = cJSON_Parse(data);
		if (Root == NULL)
		{
			fclose(f);
			free(data);
			data = NULL;
			return false;
		}
		fclose(f);
		free(data);
		data = NULL;
		return true;
	}

	static bool Init(const char * config_file)
	{

		FILE* f; long len;
		//char config_file[_MAX_PATH] = "";
		//_getcwd(config_file, MAX_PATH);
		//if (config_file[strlen(config_file)] != '\\')
		//	strcat(config_file, "\\");
		//strcat(config_file, CFGLOAD_NAME);
		fopen_s(&f, config_file, "rb");
		if (f == NULL)
		{
			return false;
		}

		fseek(f, 0, SEEK_END);
		len = ftell(f);
		fseek(f, 0, SEEK_SET);

		char* data = (char*)malloc(len + 1);
		if (!data)return false;
		fread(data, 1, len, f);
		Root = cJSON_Parse(data);
		if (Root == NULL)
		{
			fclose(f);
			free(data);
			data = NULL;
			return false;
		}
		fclose(f);
		free(data);
		data = NULL;
		return true;
	}

	static void Release()
	{
		cJSON_Delete(Root);
		free(Root);
	}

	static bool StringInstead(const char* index, const char* str, char*& out)
	{
		cJSON* modules = cJSON_GetObjectItem(Root, index);
		if (!modules)return false;
		cJSON* modulesvalue = cJSON_GetObjectItem(modules, str);
		if (modulesvalue && modulesvalue->type == cJSON_String)
		{
			out = modulesvalue->valuestring;
			return true;
		}
		return false;
	}

	static cJSON* GetModuleCfg(const char* ModuleName, const char* cfgname)
	{
		cJSON* modules = cJSON_GetObjectItem(Root, CFGLOAD_MODULE);
		if (!modules)return NULL;
		char* strouta = NULL;
		cJSON* modulesvalue = NULL;
		if (StringInstead(CFGLOAD_INSTEAD_GLOBAL, ModuleName, strouta))
		{
			modulesvalue = cJSON_GetObjectItem(modules, strouta);
		}
		else
		{
			modulesvalue = cJSON_GetObjectItem(modules, ModuleName);
		}
		if (!modulesvalue)return NULL;

		cJSON* mymodulevalue = NULL;
		if (StringInstead(CFGLOAD_INSTEAD_GLOBAL, cfgname, strouta))
		{
			mymodulevalue = cJSON_GetObjectItem(modulesvalue, strouta);
		}
		else
		{
			mymodulevalue = cJSON_GetObjectItem(modulesvalue, cfgname);
		}
		return mymodulevalue;
	}

	static const unsigned char GetModuleHotKey(const char* ModuleName)
	{
		cJSON* originalvalue = NULL;
		originalvalue = GetModuleCfg(ModuleName, CFGLOAD_MODULE_HOKKEY);

		if (originalvalue == NULL)return NULL;

		char* retstr = NULL;
		StringInstead(CFGLOAD_INSTEAD_VK, originalvalue->valuestring, retstr);

		if (retstr == NULL)return NULL;

		long num = strtol(retstr, NULL, 0);
		return (unsigned char)num;
	}

	static const bool GetModuleIsOn(const char* ModuleName)
	{
		cJSON* temp = GetModuleCfg(ModuleName, CFGLOAD_MODULE_ISON);
		if (temp == NULL)return false;
		if (temp->type == cJSON_True)
			return true;
		return false;
	}

	static const bool GetModuleDescription(const char* ModuleName, char* pDescription, size_t len)
	{
		if (pDescription == NULL)return false;
		memset(pDescription, NULL, len);
		cJSON* temp = GetModuleCfg(ModuleName, CFGLOAD_MODULE_DESCRIPTION);
		if (temp == NULL)return false;
		if (temp->type == cJSON_String)
		{
			strcpy_s(pDescription, len,temp->valuestring);
			return true;
		}
		return false;
	}

	static const unsigned char GetModuleCfgBYTEColour(const char* ModuleName, const char* cfgname)
	{
		cJSON* originalvalue = GetModuleCfg(ModuleName, cfgname);
		if (originalvalue == NULL || originalvalue->type != cJSON_String)return NULL;

		char* strout = NULL;
		if (StringInstead(CFGLOAD_INSTEAD_BYTECOLOUR, originalvalue->valuestring, strout))
		{
			return (unsigned char)strtol(strout, NULL, 0);
		}
		return (unsigned char)strtol(originalvalue->valuestring, NULL, 0);
	}

	static const int GetModuleCfgInt(const char* ModuleName, const char* cfgname)
	{
		cJSON* originalvalue = GetModuleCfg(ModuleName, cfgname);
		if (originalvalue == NULL || originalvalue->type != cJSON_Number)return NULL;
		return originalvalue->valueint;
	}

	static const bool GetModuleCfgBool(const char* ModuleName, const char* cfgname)
	{
		cJSON* originalvalue = GetModuleCfg(ModuleName, cfgname);
		if (originalvalue && originalvalue->type == cJSON_True)return true;
		return false;
	}

	static const bool GetModuleCfgString(const char* ModuleName, const char* cfgname,char * dest,size_t len)
	{
		if (dest == NULL)return false;
		memset(dest, NULL, len);
		cJSON* originalvalue = GetModuleCfg(ModuleName, cfgname);
		if (originalvalue && originalvalue->type == cJSON_String)
		{
			strcpy_s(dest,len, originalvalue->valuestring);
			return true;
		}
		return false;
	}

	static const bool GetModuleMapValuesFromRoot(cJSON* object, cJSON** vecvalue, size_t maxelement, const char* InsteadName = CFGLOAD_INSTEAD_UNITTN)
	{
		if (object == NULL || vecvalue == NULL)
			return false;

		memset(vecvalue, NULL, maxelement);

		cJSON* pfromobject = object->child;
		while (pfromobject)
		{
			//MessageBox(NULL, "ssss", "开始", MB_OK);
			char* dealnumstr = pfromobject->string;
			char* changablestr = NULL;
			if (!StringInstead(InsteadName, dealnumstr, changablestr))
				changablestr = dealnumstr;
			char* pitchstart = changablestr;
			char* c = changablestr;
			while (*c)
			{
				if (*c == ',')
				{
					size_t len = c - pitchstart + 1;
					char* p = (char*)malloc(len);
					if (!p)
					{
						return false;
					}
					memcpy(p, pitchstart, len);
					p[len - 1] = 0;
					bool bspecial = false;
					for (size_t i = 0; i < len; i++)
					{
						if (p[i] == '-')
						{
							p[i] = 0;
							size_t num1 = (size_t)strtol(p, NULL, 0);
							size_t num2 = (size_t)strtol(p + i+1, NULL, 0);
							if (num1 == 0 || num2 == 0)break;
							for (size_t i = num1; i <= num2 && i < maxelement; i++)
							{
								vecvalue[i - 1] = pfromobject;
							}
							bspecial = true;
							break;
						}
						else if (p[i] == '+')
						{
							p[i] = 0;
							long num = strtol(p, NULL, 0);
							if (num)
							{
								for (size_t i = num; i <= maxelement; i++)
								{
									vecvalue[i - 1] = pfromobject;
								}
							}
							bspecial = true;
							break;

						}
					}
					if (bspecial == false)
					{
						long num = strtol(p, NULL, 0);
						if (num)
						{
							vecvalue[num - 1] = pfromobject;
						}
					}
					free(p);
					p = NULL;
					pitchstart = c + 1;
				}
				c++;
			}
			size_t len = c - pitchstart + 1;
			char* p = (char*)malloc(len);
			if (!p)
				return false;
			memcpy(p, pitchstart, len);
			p[len - 1] = 0;
			bool bspecial = false;
			for (size_t i = 0; i < len; i++)
			{
				if (p[i] == '-')
				{
					p[i] = 0;
					size_t num1 = (size_t)strtol(p, NULL, 0);
					size_t num2 = (size_t)strtol(p + i+1, NULL, 0);
					if (num1 == 0 || num2 == 0)break;
					for (size_t i = num1; i <= num2 && i < maxelement; i++)
					{
						vecvalue[i - 1] = pfromobject;
					}
					bspecial = true;
					break;
				}
				else if (p[i] == '+')
				{
					p[i] = 0;
					long num = strtol(p, NULL, 0);
					if (num)
					{
						for (size_t i = num; i <= maxelement; i++)
						{
							vecvalue[i - 1] = pfromobject;
						}
					}
					bspecial = true;
					break;

				}
			}
			if (bspecial == false)
			{
				long num = strtol(p, NULL, 0);
				if (num)
				{
					//char info[MAX_PATH] = "";
					//sprintf_s(info, MAX_PATH, "第%d个数赋值为%d",num-1, pfromobject);
					//MessageBox(NULL, info, "开始", MB_OK);
					vecvalue[num - 1] = pfromobject;
				}
			}
			free(p);
			p = NULL;
			//MessageBox(NULL, "next", "开始", MB_OK);
			pfromobject = pfromobject->next;
		}
		//MessageBox(NULL, "return", "开始", MB_OK);
		return true;
	}

	static const bool GetModuleMapValues(const char* ModuleName, const char* ArrayName, cJSON** vecvalue, size_t maxelement, const char* InsteadName = CFGLOAD_INSTEAD_UNITTN)
	{
		cJSON* originalvalue = GetModuleCfg(ModuleName, ArrayName);

		if (originalvalue == NULL)return false;

		return GetModuleMapValuesFromRoot(originalvalue, vecvalue, maxelement, InsteadName);
	}

	static const bool GetModuleMapByteColor(const char* ModuleName, const char* ArrayName, unsigned char* vecvalue, size_t maxelement, const char* InsteadName = CFGLOAD_INSTEAD_UNITTN, const char* InsteadColorName = CFGLOAD_INSTEAD_BYTECOLOUR)
	{
		cJSON** p = (cJSON**)malloc(maxelement*sizeof(cJSON*));
		if (p == NULL)return false;

		if (!GetModuleMapValues(ModuleName, ArrayName, p, maxelement, InsteadName))
		{
			free(p);
			return false;
		}

		for (size_t i = 0; i < maxelement; i++)
		{
			if (p[i]&&p[i]->type == cJSON_String)
			{
				char* pout = NULL;
				if (!StringInstead(InsteadColorName, p[i]->valuestring, pout))
					pout = p[i]->valuestring;
				vecvalue[i] = (unsigned char)strtol(pout, NULL, 0);
			}
		}
		free(p);
		p = NULL;
		return true;
	}
};