#include "myStringUtils.h"

int myStringUtils::toInt(const string &value)
{
	return static_cast<int>(strtol(value.data(), NULL, 0));
}

double myStringUtils::toDouble(const string &value)
{
	return strtod(value.data(), 0);
}


template<typename T>
static string toStringInternal(T value)
{
	stringstream stream;
	stream << value;
	return stream.str();
}

string myStringUtils::toString(int value)
{
	return toStringInternal(value);
}

string toString(double value)
{
	return toStringInternal(value);
}

std::vector<string> myStringUtils::spiltStr(string sourceStr, string spilt)
{
	std::vector < std::string> ret;
	size_t last = 0;
	size_t index = sourceStr.find_first_of(spilt, last);
	while (index != std::string::npos)
	{
		ret.push_back(sourceStr.substr(last, index - last));
		last = index + 1;
		index = sourceStr.find_first_of(spilt, last);
	}
	if (index - last>0)
	{
		ret.push_back(sourceStr.substr(last, index - last));
	}

	return ret;
}

