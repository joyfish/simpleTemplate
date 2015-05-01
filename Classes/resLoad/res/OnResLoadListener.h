#pragma once
#include "cocos2d.h"

using namespace std;
using namespace cocos2d;

class IRes;

class OnResLoadListener 
{

public:

//��Դ���ؿ�ʼ
  virtual void onLoadStart(IRes *res)=0;

  //��Դ���ؽ���֪ͨ
  virtual void onLoadProgressNotify(IRes *res,float progress)=0;

  //��Դ�������
  virtual void onLoadComplete(IRes *res)=0;


};