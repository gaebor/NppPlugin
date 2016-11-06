#pragma once

#include "PluginInterface.h"
#include "PluginDefinition.h"

extern FuncItem funcItem[nbFunc];
extern NppData nppData;

#include <string>
#include <vector>
#include <map>

#include "Notepad_plus_msgs.h"
#include "CommandParser.h"
#include "Configuration.h"

class ConfigWindow;

class MyNppPlugin
{
public:
	class FunctionIdentifier
	{
	public:
		FunctionIdentifier(std::wstring name = L"", void (*f)(void) = NULL, ShortcutKey s = defaultKey)
			:	functionName(name), function(f), sk(s)
		{
		}
		~FunctionIdentifier()
		{
		}
		const std::wstring functionName;
		void (* const function)(void);
		ShortcutKey sk;
	};
	typedef std::map<int, FunctionIdentifier> FunctionsType;
private:
	MyNppPlugin(void);
	~MyNppPlugin(void);
protected:
	friend class ConfigWindow;

	bool initialized_;
	toolbarIcons	g_TBHex;
	void CompileInternal(const std::wstring& options = L"");
	Configuration configuration;
	
	CommandParser<std::wstring> parser;
	FunctionsType functions;
public:
	const FunctionsType& GetFunctions()const {return functions;}
	static MyNppPlugin* ME();
	void Initialize(HANDLE hM);
	void DeInitialize();
	void InitIcon();
	static void Compile();
	static void CompileQuiet();
	HANDLE hModule;
	static void Configure();
public:
};
