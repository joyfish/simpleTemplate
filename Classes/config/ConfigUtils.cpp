#include "ConfigUtils.h"
#include "ConfigManager.h"
USING_NS_CC;


std::string ConfigUtils::getLanguageById(int id)
{
	configMap map = ConfigManager::getInstance()->getLanguageMap();
	LanguageConfig *config = dynamic_cast<LanguageConfig*>(map.at(id));
	return config->getChinese();
}