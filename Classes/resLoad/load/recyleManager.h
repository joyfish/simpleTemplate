#pragma once

#include "resLoad/res\IRes.h"

class recyleManager :Ref
{
public:
	void put(std::string url ,IRes * res );

	void recyleAll();

	~recyleManager();
private:
	std::map<std::string , IRes*> m_recyleDic;
};