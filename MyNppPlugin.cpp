#include "MyNppPlugin.h"

#include <shlobj.h>
#include <winuser.h>

#include <wchar.h>
#include <string>
#include <vector>
#include <fstream>
#include <thread>

#include "resource.h"
#include "ConfigWindow.h"

using namespace std;

MyNppPlugin::MyNppPlugin(void)
:	initialized_(false)
{
	functions.emplace(0, FunctionIdentifier(L"Compile", &MyNppPlugin::Compile));
	functions[0].sk._isAlt = false;
	functions[0].sk._isCtrl = false;
	functions[0].sk._isShift = true;
	functions[0].sk._key = VK_F7 ;

	functions.emplace(1, FunctionIdentifier(L"Compile with additional option", &MyNppPlugin::CompileQuiet));
	functions[1].sk._isAlt = false;
	functions[1].sk._isCtrl = true;
	functions[1].sk._isShift = false;
	functions[1].sk._key = VK_F7 ;

	functions.emplace(2, FunctionIdentifier(L"Configure compiler...", &MyNppPlugin::Configure));
}

MyNppPlugin::~MyNppPlugin(void)
{
}

MyNppPlugin* MyNppPlugin::ME()
{
	static MyNppPlugin myself;
	return &myself;
}

void MyNppPlugin::Initialize(HANDLE hM)
{
	hModule = hM;
	if (initialized_)
		::MessageBox(NULL, TEXT("Reinitializing..."), TEXT("Info"), MB_OK);

	//INITCOMMONCONTROLSEX icex;           // Structure for control initialization.
	//icex.dwICC = ICC_STANDARD_CLASSES;
	//const auto common = ::InitCommonControlsEx(&icex);

	//::SendMessage(nppData._nppHandle, NPPM_GETPLUGINSCONFIGDIR, (WPARAM)MAX_PATH, (LPARAM)buffer);
	//::MessageBox(NULL, buffer, TEXT("Info"), MB_OK);

	WCHAR pltstr[MAX_PATH];

	const auto result = ::SHGetFolderPath(NULL, CSIDL_LOCAL_APPDATA | CSIDL_FLAG_CREATE, NULL, 0, pltstr);

	if (result == S_OK)
	{
		//::MessageBox(NULL, pltstr, TEXT("Info"), MB_OK);
		wstring configDir(pltstr);
		configDir += L"\\";
		configDir += NPP_PLUGIN_NAME;
		configDir += L"\\config.txt";

		wifstream wifs(configDir);
		if (wifs.good())
		{
			configuration.Read(wifs);
		}else
		{
			wstring error_message = TEXT("Unable to load config file \"");
			error_message += configDir;
			error_message += TEXT("\"! Using default.");

			::MessageBox(NULL, error_message.c_str(), TEXT("Info"), MB_OK);
		}
	}else
	{
		::MessageBox(NULL, TEXT("Couldn't access local application data"), TEXT("Info"), MB_OK);
	}
	
	initialized_ = true;
	return;
}

void MyNppPlugin::DeInitialize()
{
	if (!initialized_)
		return;

	if (g_TBHex.hToolbarBmp)
		::DeleteObject(g_TBHex.hToolbarBmp);
	if (g_TBHex.hToolbarIcon)
		::DestroyIcon(g_TBHex.hToolbarIcon);

	initialized_ = false;
	return;
}

void MyNppPlugin::Compile()
{
	ME()->CompileInternal(L"");
}

void MyNppPlugin::CompileQuiet()
{
	ME()->CompileInternal(ME()->configuration.GetAdditionalCommand());
}

void MyNppPlugin::CompileInternal( const std::wstring& options /*= L""*/ )
{
	WCHAR buffer[MAX_PATH];

	::SendMessage(nppData._nppHandle, NPPM_GETFULLCURRENTPATH, 0, (LPARAM)buffer);
	wstring pathStr(buffer);
	parser.AddRule(L"$(FULLCURRENTPATH)", pathStr);

	::SendMessage(nppData._nppHandle, NPPM_GETFILENAME, 0, (LPARAM)buffer);
	wstring fileStr(buffer);

	::SendMessage(nppData._nppHandle, NPPM_GETCURRENTDIRECTORY, 0, (LPARAM)buffer);
	wstring directory(buffer);
	parser.AddRule(L"$(CURRENTDIRECTORY)", directory);

	if(fileStr.size()<5 || wstring(fileStr.c_str()+fileStr.size()-4, 4) != L".tex")
	{
		wstring message(L"the file \'" + fileStr + L"\' is not a tex file!");
		::MessageBox(NULL, message.c_str(), L"Info", MB_OK);
	}else{
		
		::SendMessage(nppData._nppHandle, NPPM_SAVECURRENTFILE, 0, (LPARAM)pathStr.c_str());

		pathStr.erase(pathStr.size()-4);
		parser.AddRule(L"$(FileName)", pathStr);

		vector<wstring> commands;
		commands.push_back(parser.Replace(configuration.GetPreBuildEvent()));
		
		commands.push_back(parser.Replace(configuration.GetBuildEvent()));
		if (!options.empty())
		{
			commands.back() += L" ";
			commands.back() += parser.Replace((const wstring&)options);

		}
		commands.push_back(parser.Replace(configuration.GetPostBuildEvent()));

		std::thread compilerThread([](vector<wstring> commands){
			vector<int> results;

			for (const auto& command : commands)
			{
				results.push_back(_wsystem(command.c_str()));
			}
		}, commands);

		compilerThread.detach();
		
	}
}

void MyNppPlugin::InitIcon()
{
	g_TBHex.hToolbarBmp = (HBITMAP)::LoadImage((HINSTANCE)hModule, MAKEINTRESOURCE(IDB_TB_ICON), IMAGE_BITMAP, 0, 0, LR_MONOCHROME );
	::SendMessage(nppData._nppHandle, NPPM_ADDTOOLBARICON, (WPARAM)funcItem[0]._cmdID, (LPARAM)&g_TBHex);
}

void MyNppPlugin::Configure()
{
	ME()->configuration.ConfigureMe(ME()->hModule);
}
