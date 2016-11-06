#pragma once
#include <map>

template<class String>
class CommandParser
{
public:
	CommandParser(void)
	{}
	~CommandParser(void)
	{}
	void Replace(String& targerStr)const
	{
		for (ReplacementType::const_iterator it = replacementValues.begin(); it != replacementValues.end(); ++it)
		{
			size_t position = 0;
			const String& replacementName = (*it).first;
			const String& replacementValue = (*it).second;
			while ((position = targerStr.find(replacementName, position)) != String::npos)
			{
				const String endStr = targerStr.substr(position + replacementName.size());
				targerStr.erase(position);
				targerStr.append(replacementValue);
				targerStr.append(endStr);

				position += replacementValue.size();
			}
		}
	}
	String Replace(const String& input)const
	{
		String result = input;
		Replace(result);
		return result;
	}
	void AddRule(const String& macro, const String& value)
	{
		replacementValues[macro] = value;
	}
protected:
	typedef std::map<String, String> ReplacementType;
	ReplacementType replacementValues;
};
