#include "myMessageHander.h"

bool myMessageHander::isContainAction(int action)
{
	std::map<int, int>::iterator itor = _actionValueMap.begin();
	for (; itor != _actionValueMap.end(); itor++)
	{
		if (itor->first == action&&itor->second== action)
		{
			return true;
		}
	}

	return false;
}

void myMessageHander::addToMap(int action)
{
	_actionValueMap.insert(std::pair<int,int>(action, action));
}