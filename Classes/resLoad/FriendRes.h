#ifndef _FRIEND_RES_H_
#define _FRIEND_RES_H_

#include <string>
#include "cocos2d.h"
#include "load/LoadCount.h"

using namespace std;

using namespace cocos2d;

class FriendRes : public Ref
{
public:
	~FriendRes(void);    

	static FriendRes * createTempRes();
	static FriendRes * createForeverRes();
	static Vector<IRes*> *getForeverLoadResArray();
	void  initTempRes();
	void  initForeverRes();
	Vector<IRes*>* getResArray();
	void releaseRes();

	void startLoad(OnLoadListener *listener);
	void startSynLoad();
	int getResSize();
	int getResCount();


private:
	FriendRes(void);

private:
	LoadCount *mLoadCount; 

};
#endif // _FRIEND_RES_H_
