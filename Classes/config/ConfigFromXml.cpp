#include "ConfigFromXml.h"
#include "ItemConfig.h"
#include "LanguageConfig.h"

tinyxml2::XMLDocument*  ConfigFromXml::getDocument(std::string str)
{
	 tinyxml2::XMLDocument *pDoc = new tinyxml2::XMLDocument;
	 tinyxml2::XMLError pError;
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    ssize_t *temp = 0;    
    unsigned char* pBuffer = NULL;
    pBuffer = FileUtils::sharedFileUtils()->getFileData(str,"r",temp);
    if (pBuffer)
    {
        pError = pDoc->Parse((const char*)pBuffer);
    }
	else
	{
		return nullptr;
	}
#else
    string filePath = FileUtils::getInstance()->fullPathForFilename(str);
	log("external file path = %s", filePath.c_str());
    pError = pDoc->LoadFile(filePath.c_str());
#endif

	if (pError != 0)//xml¸ñÊ½´íÎó
	{
		return nullptr;
	}
	return pDoc;
}


configMap ConfigFromXml::readItemConfig(std::string str)
{
	tinyxml2::XMLDocument * doc = getDocument(str);

	CCAssert(doc!=nullptr,str.c_str());

	tinyxml2::XMLElement * rootEle = doc->RootElement();

	tinyxml2::XMLElement* element = rootEle->FirstChildElement();

	configMap map;
	while (element != nullptr)
	{
		ItemConfig *config = new ItemConfig;
		const XMLAttribute *attribute = element->FirstAttribute();
		while (attribute) 
		{
			std::string attributeName = attribute->Name();
			Value value = Value(attribute->Value());
			attribute = attribute->Next();
			if (attributeName == "id")
			{
				config->setId(value.asInt());
			}
			else if (attributeName == "name")
			{
				config->setName(value.asString());
			}
		}
		map.insert(config->getId(), config);
		element = element->NextSiblingElement();
	}

	delete doc;

	return map;
}

configMap ConfigFromXml::readLanguageConfig(std::string str)
{
	tinyxml2::XMLDocument * doc = getDocument(str);
	log("str.c_str()" );
	CCAssert(doc != nullptr, str.c_str());
	log("readLanguageConfig  SUCCESS" );
	tinyxml2::XMLElement * rootEle = doc->RootElement();

	tinyxml2::XMLElement* element = rootEle->FirstChildElement();

	configMap map;
	while (element != nullptr)
	{
		LanguageConfig *config = new LanguageConfig;
		const XMLAttribute *attribute = element->FirstAttribute();
		while (attribute)
		{
			std::string attributeName = attribute->Name();
			Value value = Value(attribute->Value());
			attribute = attribute->Next();
			if (attributeName == "id")
			{
				config->setId(value.asInt());
			}
			else if (attributeName == "chinese")
			{
				config->setChinese(value.asString());
			}
		}
		map.insert(config->getId(), config);
		element = element->NextSiblingElement();
	}

	delete doc;

	return map;
}