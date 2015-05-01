#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class myStringUtils
{
public:
	static std::vector<string> spiltStr(string sourceStr,string spilt);

	static int toInt(const string &value);
	static double toDouble(const string &value);
	static std::string toString(int value);
	static std::string toString(float value);
	
};