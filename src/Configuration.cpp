#include "Configuration.h"
#include "ConfigWindow.h"

using namespace std;

void Configuration::Read( std::wistream& is )
{
	wstring line;
	while (is.good())
	{
		getline(is, line);
		if (line.find_first_of('\t') != wstring::npos)
		{
			const wstring paramName(line.begin(), line.begin() + line.find_first_of('\t'));
			const wstring paramValue(line.begin() + line.find_first_of('\t') + 1, line.end());

			//::MessageBox(NULL, paramName.c_str(), TEXT("Info"), MB_OK);

			if (paramName == L"PRE_BUILD_EVENT")
				preBuildEvent = paramValue;
			else if (paramName == L"BUILD_EVENT")
				buildEvent = paramValue;
			else if (paramName == L"POST_BUILD_EVENT")
				postBuildEvent = paramValue;
			else if (paramName == L"OPTION")
			{
				additionalCommand = paramValue;
				//::MessageBox(NULL, additionalCommand.c_str(), TEXT("Info"), MB_OK);
			}
		}
	}
}

void Configuration::Write( std::wostream os ) const
{
	if (os.good())
	{
		os << L"PRE_BUILD_EVENT" << '\t' << preBuildEvent << endl;
		os << L"BUILD_EVENT" << '\t' << buildEvent << endl;
		os << L"POST_BUILD_EVENT" << '\t' << postBuildEvent << endl;
		os << L"OPTION" << '\t' << additionalCommand << endl;
	}
}

Configuration::Configuration()
{
	preBuildEvent = L"TASKKILL /F /IM AcroRd32.exe";
	buildEvent = L"pdflatex \"$(FileName).tex\" -output-directory $(CURRENTDIRECTORY)";
	postBuildEvent = L"start $(FileName).pdf";
	additionalCommand = L"-quiet";
}

Configuration::~Configuration()
{

}

void Configuration::ConfigureMe(HANDLE module)
{
	ConfigWindow cw(module);
	cw.configure(this);
}

const std::wstring& Configuration::GetAdditionalCommand() const
{
	return additionalCommand;
}

const std::wstring& Configuration::GetPreBuildEvent() const
{
	return preBuildEvent;
}

const std::wstring& Configuration::GetBuildEvent() const
{
	return buildEvent;
}

const std::wstring& Configuration::GetPostBuildEvent() const
{
	return postBuildEvent;
}
