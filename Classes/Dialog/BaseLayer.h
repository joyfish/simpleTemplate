#pragma once 

#include "cocos2d.h"
#include "CocosGUI.h"
#include "config\ConfigManager.h"
#include "config\ConfigUtils.h"
USING_NS_CC;
using namespace experimental;
using namespace ui;
using namespace std;

//��Щ��Ϊscene���ֵ�layer���̳���BaseSceneLayer����Ϊ�Ի�����ֵ�layer���̳���BaseLayer
class BaseLayer : public Layer
{
public:
	
	BaseLayer();
	virtual ~BaseLayer();

protected:
	static bool createSubLayer(BaseLayer* sublayer);

	virtual bool init()final;

	virtual void initData();//�̳���ֻ��Ҫ��д��������ʼ����͹���
	virtual void initView();
	virtual void onEnter();
	virtual void onExit();

	void showLoadingUI();
	void HideLoadingUI();

private:
	Sprite * loadIngCircle;
	Sprite * loadingBg;
};