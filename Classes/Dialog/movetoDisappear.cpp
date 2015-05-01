#include "moveToDisappear.h"

MoveToDisappear *MoveToDisappear::create(std::string str, bool autoShow)
{
	TTFConfig ttfconfig;
	ttfconfig.fontFilePath = "fonts/Marker Felt.ttf";
	ttfconfig.fontSize = 30;
	ttfconfig.outlineSize = 2;

	auto label = LabelTTF::create(str, "Arial", 24);

	//Label * label = Label::createWithTTF(ttfconfig,str);
	return MoveToDisappear::create(label,autoShow);
	
}

MoveToDisappear * MoveToDisappear::create(Node *node, bool autoShow)
{
	CCAssert(node!=nullptr,"node is null");
	MoveToDisappear *dialog = new MoveToDisappear;
	dialog->m_node = node;
	dialog->m_autoShow = autoShow;
	if (node->getReferenceCount()==1)//如果没有retrin();
		dialog->m_node->retain();
	BaseLayer::createSubLayer(dialog);

	return dialog;
}

MoveToDisappear::MoveToDisappear() :m_node(NULL), m_callback(nullptr)
{
	
}

MoveToDisappear::~MoveToDisappear()
{
	CC_SAFE_RELEASE_NULL(m_node);
	
}


void MoveToDisappear::initData()
{
	BaseLayer::initData();

}

void MoveToDisappear::initView()
{
	BaseLayer::initView();

	initWithNode(m_node);
}


bool MoveToDisappear::initWithNode(Node *node)
{

	Size winSize = Director::getInstance()->getWinSize();//设计分辨率尺寸
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();
	Point centerPoint = Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y);

	//加上提示背景
    Sprite *bgSprite = Sprite::create("common/tishi_box.png");
	bgSprite->setPosition(centerPoint);
	this->addChild(bgSprite);

	//加上外部Node
	node->setPosition(centerPoint);
	node->release();
	this->addChild(node);
	
	if (m_autoShow)//否则要手动调用show（）；
		this->disappear();
	
	return true;
}


void MoveToDisappear::show()
{
	Director::getInstance()->getRunningScene()->addChild(this);
	this->disappear();
}

void MoveToDisappear::disappear()
{
	DelayTime *delay = DelayTime::create(0.2);
	MoveBy *move = MoveBy::create(0.6,Point(0,110));
	FadeTo *fade = FadeTo::create(0.4f,0);
	DelayTime *delay2= DelayTime::create(0.1f);
	FiniteTimeAction *disappear = CallFunc::create(CC_CALLBACK_0(MoveToDisappear::removeme,this));

	Sequence *sq = Sequence::create(delay,move,delay2,fade,disappear,nullptr);
	this->runAction(sq);
}

void MoveToDisappear::removeme()
{
	if (m_callback!=nullptr)
		m_callback();
	this->removeAllChildren();
	this->removeFromParentAndCleanup(true);
	
}

void MoveToDisappear::setCloseCallBack(std::function<void()> callback)
{
	this->m_callback = callback;
}
