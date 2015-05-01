#pragma once 

#include "cocos2d.h"
#include "CocosGUI.h"
#include "config\ConfigManager.h"
#include "config\ConfigUtils.h"
USING_NS_CC;
using namespace experimental;
using namespace ui;
using namespace std;

//那些作为scene出现的layer，继承自BaseSceneLayer，作为对话框出现的layer，继承自BaseLayer
class BaseLayer : public Layer
{
public:
	
	BaseLayer();
	virtual ~BaseLayer();

protected:
	static bool createSubLayer(BaseLayer* sublayer);

	virtual bool init()final;

	virtual void initData();//继承类只需要重写这两个初始化类就够了
	virtual void initView();
	virtual void onEnter();
	virtual void onExit();

	void showLoadingUI();
	void HideLoadingUI();

private:
	Sprite * loadIngCircle;
	Sprite * loadingBg;
};