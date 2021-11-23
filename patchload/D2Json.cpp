#include "pch.h"

	void D2Json::AssertObject(void* objectget)
	{
		if (!objectget)
			MessageBox(NULL, "Error In AssertObject", "D2JsonError", MB_OK);
	}

	D2Json::D2Json() 
	{
	}

	D2Json::~D2Json()
	{
		unload();
	}

	bool D2Json::load(const char* filename)
	{
		unload();

		FILE* f; long len;
		char config_file[_MAX_PATH] = "";
		_getcwd(config_file, MAX_PATH);
		if (config_file[strlen(config_file)] != '\\')
			strcat(config_file, "\\");
		strcat(config_file, filename);
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

	void D2Json::unload()
	{
		cJSON_Delete(Root);
		free(Root);
	}

	cJSON* D2Json::GetRoot()
	{
		if (!Root)
		{
			MessageBox(NULL, "Error In Read Root", "D2JsonError", MB_OK);
		}
		return Root;
	}

	cJSON* D2Json::GetObjectItemInModule(const char* ModuleName, const char* cfgname)
	{
		cJSON* modules = cJSON_GetObjectItem(Root, "Modules");
		modules = cJSON_GetObjectItem(modules, ModuleName);
		modules = cJSON_GetObjectItem(modules, cfgname);
		return modules;
	}

	const bool D2Json::GetModuleCfgBool(const char* ModuleName, const char* cfgname, bool* objectget)
	{
		AssertObject(objectget);
		cJSON* originalvalue = GetObjectItemInModule(ModuleName, cfgname);
		if (originalvalue && originalvalue->type == cJSON_True)
		{
			if (originalvalue->type == cJSON_True)
			{
				*objectget = true;
				return true;
			}
			else if (originalvalue->type == cJSON_False)
			{
				*objectget = false;
				return true;
			}
		}
		return false;
	}

	const bool D2Json::GetModuleMapValues(const char* ModuleName, const char* ArrayName, cJSON** vecvalue, unsigned int maxelement)
	{
		cJSON* object = GetObjectItemInModule(ModuleName, ArrayName);

		if (!object)return false;

		if (object == NULL || vecvalue == NULL)
			return false;

		memset(vecvalue, NULL, maxelement);

		cJSON* pfromobject = object->child;
		while (pfromobject)
		{
			char* changablestr = pfromobject->string;
			//char* changablestr = dealnumstr;
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
							size_t num2 = (size_t)strtol(p + i + 1, NULL, 0);
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
					size_t num2 = (size_t)strtol(p + i + 1, NULL, 0);
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
			pfromobject = pfromobject->next;
		}
		return true;
	}

	const bool D2Json::GetCfgBool(cJSON* object,const char* cfgname, bool* objectget)
	{
		AssertObject(object);
		AssertObject(objectget);
		cJSON* originalvalue = cJSON_GetObjectItem(object, cfgname);
		if (originalvalue && originalvalue->type == cJSON_True)
		{
			if (originalvalue->type == cJSON_True)
			{
				*objectget = true;
				return true;
			}
			else if (originalvalue->type == cJSON_False)
			{
				*objectget = false;
				return true;
			}
		}
		return false;
	}