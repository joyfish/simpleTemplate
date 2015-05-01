#pragma once
#include "BaseLayer.h"

class MoveToDisappear:public BaseLayer
{
public:
	static MoveToDisappear * create(std::string str, bool autoShow = true);
	static MoveToDisappear * create(Node *node, bool autoShow = true);

	void setCloseCallBack(std::function<void()> callback);
	void show();

	MoveToDisappear();
	~MoveToDisappear();
private:

	Node *m_node;
	bool m_autoShow;

	std::function<void()> m_callback;
private:
	virtual void initData();
	virtual void initView();
	
	bool initWithNode(Node *node);

	void disappear();

	void removeme();

	
};