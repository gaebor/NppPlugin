#include "ConfigWindow.h"

#include <string>
#include <sstream>

#include "PluginInterface.h"
#include "PluginDefinition.h"
#include "Notepad_plus_msgs.h"

#include "resource.h"

#include "MyNppPlugin.h"

using namespace std;

INT_PTR CALLBACK DlgProc( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	switch(message)
	{
	case WM_INITDIALOG:

		return TRUE;
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDC_EXIT_BUTTON:
			EndDialog(hwnd, IDC_EXIT_BUTTON);
			break;
		default:
			EndDialog(hwnd, 0);
			break;
		}
		break;
	default:
		return FALSE;//DefDlgProc(hwnd, message, wParam, lParam);
	}
	return TRUE;
}

ConfigWindow::ConfigWindow(HANDLE module)
	: hModule(module)
{
}


ConfigWindow::~ConfigWindow(void)
{
}

void ConfigWindow::configure(Configuration* plgn)
{	
	wstring windowName = NPP_PLUGIN_NAME;
	windowName += L" configurations";

	const auto result = DialogBox((HINSTANCE)hModule, MAKEINTRESOURCE(ID_CONFIG_DIALOG), nppData._nppHandle, DlgProc);

	if (result <= 0)
	{
		const auto error_word = ::GetLastError();
		wostringstream ostr;
		ostr << error_word;

		::MessageBox(NULL, ostr.str().c_str(), L"Info...", MB_OK | MB_ICONEXCLAMATION);
	}

}

//bool ConfigWindow::hasRegistered = false;
 