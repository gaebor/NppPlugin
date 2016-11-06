#pragma once

#include <map>
#include <string>
#include <ostream>

#include <wtypes.h>

class ConfigWindow;

class Configuration
{
public:
	Configuration();
	~Configuration();
	void Read(std::wistream& is);
	void Write(std::wostream os)const;
	void ConfigureMe(HANDLE module);

	const std::wstring& GetAdditionalCommand()const;
	const std::wstring& GetPreBuildEvent()const;
	const std::wstring& GetBuildEvent()const;
	const std::wstring& GetPostBuildEvent()const;
protected:
	friend class ConfigWindow;
	typedef std::map<std::wstring, std::wstring> Attributes;
	std::wstring preBuildEvent;
	std::wstring buildEvent;
	std::wstring postBuildEvent;
	std::wstring additionalCommand;
};
