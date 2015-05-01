#ifndef _CONFIG_FROM_XM_H_
#define _CONFIG_FROM_XM_H_

#include <string>
#include "cocos2d.h"
#include "tinyxml2\tinyxml2.h"


USING_NS_CC;
using namespace tinyxml2;

typedef Map<int, Ref*> configMap;

class ConfigFromXml
{
public:
	ConfigFromXml(void);
	~ConfigFromXml(void);    

	static configMap readItemConfig(std::string str);
	static configMap readLanguageConfig(std::string str);
private :
	static tinyxml2::XMLDocument* getDocument(std::string str);
};
#endif // _CONFIG_MANAGER_H_
