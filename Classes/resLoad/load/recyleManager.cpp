#include "recyleManager.h"

void recyleManager::put(std::string url, IRes * res)
{
	std::map<std::string, IRes*>::iterator itor = m_recyleDic.find(url);
	if (itor == m_recyleDic.end())
	{
		res->setResRefrenceCount(true);
		m_recyleDic[url] = res;
	}
	else
	{
		IRes * ires = itor->second;
		ires->setResRefrenceCount(true);
	}
	
}

recyleManager::~recyleManager()
{
	
	m_recyleDic.clear();
}

void recyleManager::recyleAll()
{ 
	std::vector<std::string> eraseArr;
	std::map<std::string, IRes*>::iterator itor = m_recyleDic.begin();
	for (; itor != m_recyleDic.end(); itor++)
	{
		auto var = *itor;
		IRes * res = var.second;
		res->setResRefrenceCount(false);
		if (res->getResRefrenceCount() == 0)
		{
			res->recycle();
			eraseArr.push_back(var.first);
		}
		else
		{
			std::string str = res->getUrl();
		}
	}

	std::vector<std::string>::iterator itor2 = eraseArr.begin();
	for (; itor2 != eraseArr.end(); itor2++)
	{
		auto var = *itor2;
		m_recyleDic.erase(var);
	}

}