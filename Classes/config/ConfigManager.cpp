#include "ConfigManager.h"
#include "ConfigFromXml.h"

ConfigManager * ConfigManager::sInstance = NULL;

ConfigManager* ConfigManager::getInstance()
{
	if (sInstance == NULL)
	{
		sInstance = new ConfigManager();
	}
	return sInstance;
}

ConfigManager::ConfigManager(void)
{
	
}
ConfigManager::~ConfigManager(void)
{

}

void ConfigManager::load()
{
	_languageMap = ConfigFromXml::readLanguageConfig("config/language.xml");
}

void ConfigManager::recycle()
{
	_languageMap.clear();
}