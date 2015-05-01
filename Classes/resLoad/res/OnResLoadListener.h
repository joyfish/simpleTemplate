#pragma once
#include "cocos2d.h"

using namespace std;
using namespace cocos2d;

class IRes;

class OnResLoadListener 
{

public:

//资源加载开始
  virtual void onLoadStart(IRes *res)=0;

  //资源加载进度通知
  virtual void onLoadProgressNotify(IRes *res,float progress)=0;

  //资源加载完成
  virtual void onLoadComplete(IRes *res)=0;


};