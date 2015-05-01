#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "socket\myMessageHander.h"
class HelloWorld : public cocos2d::Layer,public myMessageHander
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

private:
	virtual void sendMessageToServer(int actionId);//根据不同的消息，发送的数据肯定也不一样
	virtual void receiveMessageFromServer(SmartMessageData * data);
	virtual void setActionMap();
};

#endif // __HELLOWORLD_SCENE_H__
