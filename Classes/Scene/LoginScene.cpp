#include "LoginScene.h"
#include "socket\myMessageManager.h"
#include "Dialog\moveToDisappear.h"
#include "msgBody\msgBody.h"
#include "ui\UIRichText.h"
LoginScene::LoginScene()
{

}
LoginScene::~LoginScene()
{

}
LoginScene* LoginScene::createScene()
{
	LoginScene *loginLayer= new LoginScene;
	BaseLayer::createSubLayer(loginLayer);
	return loginLayer;
}

void LoginScene::onEnter()
{
	BaseSceneLayer::onEnter();
	myMessageManager::getInstance()->rigeterMessageListener(CMD_Constant::ACTION_TEST1, this);
	myMessageManager::getInstance()->rigeterMessageListener(CMD_Constant::ACTION_TEST2, this);

}
void LoginScene::onExit()
{
	BaseSceneLayer::onExit();
	myMessageManager::getInstance()->destroyrMessageListener(CMD_Constant::ACTION_TEST1, this);
	myMessageManager::getInstance()->destroyrMessageListener(CMD_Constant::ACTION_TEST2, this);

}

void LoginScene::initData()
{
	BaseSceneLayer::initData();
	//BaseLayer::initData();
}
void LoginScene::initView()
{
	BaseSceneLayer::initView();

	std::string str = "uvukblijgig";// ConfigUtils::getLanguageById(1);
	//RichElementText * ttf = RichElementText::create(1, Color3B(255, 0, 0), 255, str, "Arial", 20);
	//RichElementText * ttf = RichElementText::create(1, Color3B(255, 0, 0), 255, str, "Arial", 20);
	ui::Button * button = Button::create();
	button->loadTextures("CloseNormal.png", "", "");
	//RichElementTouchNode * tou = RichElementTouchNode::create(2, Color3B(255, 0, 0), 255, button, CC_CALLBACK_2(LoginScene::buttonclick, this), __Integer::create(10));

	Button * bb = Button::create();
	bb->loadTextures("CloseNormal.png", "", "");
	/*RichElementCustomNode * custon = RichElementCustomNode::create(3, Color3B(0, 255, 0), 255, bb);

	RichText * rich = RichText::create();
	rich->ignoreContentAdaptWithSize(false);
	rich->setContentSize(Size(200, 100));

	rich->pushBackElement(ttf);
	rich->pushBackElement(tou);
	rich->pushBackElement(custon);

	rich->formatText();
	rich->setPosition(Vec2(400, 400));

	this->addChild(rich);*/

	jishiqi::createForverJishiqi(CC_CALLBACK_2(LoginScene::jishicallback, this));
	jishiqi *jishi = jishiqi::create(CC_CALLBACK_2(LoginScene::jishicallback, this), 0, 20);
	this->addChild(jishi);

}


//����Ϣ�Ļ��������������������
void LoginScene::sendMessageToServer(int actionId)
{
	
	switch (actionId)
	{
	case CMD_Constant::ACTION_TEST1:
		{
			msgBody_sample_1 msg;
			msg.setAAA(2345);
			msg.setBBB("hello");
		    SEND_MSGBODY_TO_SERVER(msg);
		}
		break;
	case CMD_Constant::ACTION_TEST2:
		{
		
		}
		break;
	default:
		break;
	}


}

//���������Ϣ���麯��
void LoginScene::receiveMessageFromServer(SmartMessageData * data)
{
	if(!data)
		return;
	int action = data->getAction();
	switch (action)
	{
	case CMD_Constant::ACTION_TEST1:
	   {
		   msgBody_sample_1 msg;
		   data>>msg;
	   }
	default:
		break;
	}
}

//����麯��������ɸѡ��Ϣ������
void LoginScene::setActionMap()
{
	this->addToMap(CMD_Constant::ACTION_TEST1);
	this->addToMap(CMD_Constant::ACTION_TEST2);
}

void LoginScene::buttonclick(Ref*target, Ref * data)
{
	//sceneMaker::exitGame();
	this->addChild(MoveToDisappear::create(ConfigUtils::getLanguageById(3)));
}


void LoginScene::jishicallback(jishiqi * g_jishiqi, jishiqi_type type)
{
	switch (type)
	{
	case jishiqi_type::jishiqi_start://
	{
		int fen = g_jishiqi->getFen();
		int miao = g_jishiqi->getMiao();
	}
		break;
	case jishiqi_type::jishiqi_ing:
	{
		int fen = g_jishiqi->getFen();
		int miao = g_jishiqi->getMiao();
	}
		break;
	case jishiqi_type::jishiqi_end:
	{
		int fen = g_jishiqi->getFen();
		int miao = g_jishiqi->getMiao();
	}
		break;
	default:
		break;
	}
}


void LoginScene::timeUpdate(float f)
{
	int i = f;
}