#ifndef _CONFIG_MANAGER_H_
#define _CONFIG_MANAGER_H_

#include <string>
#include "cocos2d.h"
#include "config\LanguageConfig.h"
using namespace std;

using namespace cocos2d;

typedef Map<int, Ref*> configMap;


class ConfigManager
{
public:
	~ConfigManager(void);    

	void load();
	void recycle();

	static ConfigManager* getInstance();

	CC_SYNTHESIZE_READONLY(configMap, _languageMap, LanguageMap);

private:
	//std::map<int, Ref> _languageMap;
private:
	ConfigManager(void);

	static ConfigManager*  sInstance;

};
#endif // _CONFIG_MANAGER_H_
