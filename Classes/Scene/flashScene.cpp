#include "flashScene.h"
#include "socket\mySocketUtil.h"
#include "Scene\LoginScene.h"
#include "Dialog\moveToDisappear.h"
#include "config\ConfigConstant.h"

flashScene::flashScene() :isConnectSuccess(false), isLoadStartResCompete(false),
                         isLoadStartConfigCompete(false)
{
	log("flashScene flashScene" );
}

flashScene::~flashScene()
{

}

flashScene * flashScene::createScene()
{
	flashScene* scene = new flashScene;
	BaseLayer::createSubLayer(scene);
	return scene;
}

void flashScene::initData()
{
	log("flashScene INIT DATA" );
	BaseSceneLayer::initData();
	//���ӷ�����
	mySocketUtil::getInstance()->connectToServer("127.0.0.1",20000, std::bind(&flashScene::connectCallBack, this, std::placeholders::_1));

	ConfigManager::getInstance()->load();
	isLoadStartConfigCompete = true;//��Ӧ�и��ص��Ŷ�
	updateFlashOver();//��������˼һ�£�����һ�£��������������
	
	mFriendRes = FriendRes::createForeverRes();
	//mFriendRes->retain();
	mFriendRes->startLoad(this);

	ResSingleton::getInstance()->setFriendRes(mFriendRes);


}
void flashScene::initView()
{
	BaseSceneLayer::initView();
	log("flashScene initView" );

	TTFConfig ttfconfig;
	ttfconfig.fontFilePath = "fonts/Marker Felt.ttf";
	ttfconfig.fontSize = 30;
	ttfconfig.outlineSize = 2;
	
	Label *label = Label::createWithTTF(ttfconfig, "flashScene");
	label->enableOutline(Color4B(255, 0, 0, 244), 2);
	this->addChild(label);
	label->setPosition(200,200);

	jishiqi::createForverJishiqi(CC_CALLBACK_2(flashScene::jishicallback, this), 0, 50);
}

void flashScene::connectCallBack(bool flag)
{
	log("connectCallBack%d", flag);
	isConnectSuccess = flag;
	updateFlashOver();
	if (!flag)
	{
		static int acc = 1;
		if (acc == 3)
		{
			//����ʧ��
			MoveToDisappear * dlg = MoveToDisappear::create(ConfigUtils::getLanguageById(ConfigConstant::AAAAA));
			this->addChild(dlg);
			acc = 1;
			return;
		}
		acc++;
		//�������ӷ�����
		mySocketUtil::getInstance()->connectToServer("127.0.0.1",20000, CC_CALLBACK_1(flashScene::connectCallBack, this));

	}
}


void flashScene::OnLoadStart(LoadCount *loadCount)
{

}

void flashScene::OnLoadProgress(LoadCount *loadCount, float progress)
{
	int x = progress;
}


void flashScene::OnLoadComplete(LoadCount *loadCount)
{
	isLoadStartResCompete = true;
	updateFlashOver();
}

void flashScene::updateFlashOver()
{
	if (isLoadStartResCompete&&isConnectSuccess&&isLoadStartConfigCompete)//���ӳɹ�����Դ���سɹ�
	{
		//�����½����

		sceneMaker::makeAndRunToScene(LoginScene::createScene());
	}

}