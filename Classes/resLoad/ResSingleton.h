#ifndef _RES_SINGLETON_H_
#define _RES_SINGLETON_H_

#include <string>
#include "cocos2d.h"
#include "FriendRes.h"

using namespace std;

using namespace cocos2d;

class ResSingleton
{
public:
	~ResSingleton(void);    

	void load();

	static ResSingleton* getInstance();

	void recycleFriendRes();

private:
	ResSingleton(void);
private:


	CC_SYNTHESIZE_RETAIN(FriendRes*, friendRes, FriendRes);



	static ResSingleton*  sInstance;

};
#endif // _RES_SINGLETON_H_
