#include "ResSingleton.h"


ResSingleton * ResSingleton::sInstance = NULL;

ResSingleton* ResSingleton::getInstance() 
{
	if(sInstance == NULL)
	{
		sInstance  = new ResSingleton();
	}
	return sInstance;
}

ResSingleton::ResSingleton(void) :friendRes(NULL)
{
	
}
ResSingleton::~ResSingleton(void)
{
	CC_SAFE_RELEASE_NULL(friendRes);
	
}

void ResSingleton::recycleFriendRes()
{
	if (this->friendRes != NULL)
	{
		this->friendRes->releaseRes();
		CC_SAFE_RELEASE_NULL(friendRes);
	}
}
