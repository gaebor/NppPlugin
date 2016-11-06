#pragma once

#include <windows.h>

class Configuration;

class __declspec(dllexport) ConfigWindow
{
public:
	ConfigWindow(HANDLE module);
	~ConfigWindow(void);
public:
	void configure(Configuration* config);
private:
	HANDLE hModule;
};
