#include "BaseLayer.h"

BaseLayer::BaseLayer() :loadIngCircle(nullptr), loadingBg(nullptr)
{

}

BaseLayer::~BaseLayer()
{

}

bool BaseLayer::createSubLayer(BaseLayer* sublayer)
{
	if (sublayer&&sublayer->init())
	{
		sublayer->autorelease();
		return true;
	}
	else
	{
		delete sublayer;
		sublayer = nullptr;
		return false;
	}
}

bool BaseLayer::init()
{
	if (!Layer::init())
		return false;
	
	this->initData();
	this->initView();
	return true;
}

void BaseLayer::initData()
{

}

void BaseLayer::initView()
{
	Vec2 size = Director::getInstance()->getVisibleSize();


	loadIngCircle = Sprite::create("CloseNormal.png");
	loadingBg = Sprite::create("CloseNormal.png");

	loadingBg->setPosition(size.x / 2, size.y / 2);

	this->addChild(loadingBg);
	loadingBg->addChild(loadIngCircle);

	this->HideLoadingUI();
}

void BaseLayer::onEnter()
{
	Layer::onEnter();

}

void BaseLayer::onExit()
{
	Layer::onExit();

}

void BaseLayer::showLoadingUI()
{
	loadingBg->setVisible(true);
	loadIngCircle->runAction(RepeatForever::create(RotateBy::create(1.0f, 360)));
}

void BaseLayer::HideLoadingUI()
{
	loadingBg->setVisible(false);
	loadIngCircle->stopAllActions();
}
