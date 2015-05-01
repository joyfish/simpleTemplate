#include "FriendRes.h"
#include "res/TextureRes.h"
#include "res/ArmatureRes.h"
#include "res/PlistRes.h"

FriendRes::FriendRes(void) 
{
	mLoadCount = LoadCount::create();
	mLoadCount->retain();
}

FriendRes::~FriendRes(void)
{
	CC_SAFE_RELEASE_NULL(mLoadCount);
}

FriendRes * FriendRes::createTempRes()
{
	FriendRes *res = new FriendRes();
	res->initTempRes();
	res->autorelease();
	return res;
}

FriendRes * FriendRes::createForeverRes()
{
	FriendRes *res = new FriendRes();
	res->initForeverRes();
	res->autorelease();
	return res;
}

Vector<IRes*>* FriendRes::getForeverLoadResArray()
{
	FriendRes *res = FriendRes::createForeverRes();
	return res->getResArray();
}

void  FriendRes::initTempRes()
{

}

void  FriendRes::initForeverRes()
{
	TextureRes *textureRes = NULL;
	ArmatureRes	 *armatureRes= NULL;
	PlistRes	 *plistRes= NULL;

	//加载对话中要用到的英雄图片资源
	textureRes = TextureRes::create("friend/fd_bp.png");
	mLoadCount->loadRes(textureRes,false);
	textureRes = TextureRes::create("friend/fd_bp.png");
	mLoadCount->loadRes(textureRes, false);
	textureRes = TextureRes::create("friend/fd_btn_del.png");
	mLoadCount->loadRes(textureRes,false);
	textureRes = TextureRes::create("friend/fd_btn_jj.png");
	mLoadCount->loadRes(textureRes,false);
	textureRes = TextureRes::create("friend/fd_btn_ty.png");
	mLoadCount->loadRes(textureRes,false);
	textureRes = TextureRes::create("friend/fd_btn_zs.png");
	mLoadCount->loadRes(textureRes,false);
	textureRes = TextureRes::create("friend/fd_btn_zs_d.png");
	mLoadCount->loadRes(textureRes,false);
	textureRes = TextureRes::create("friend/fd_cz.png");
	mLoadCount->loadRes(textureRes,false);
	textureRes = TextureRes::create("friend/fd_divider.png");
	mLoadCount->loadRes(textureRes,false);
	textureRes = TextureRes::create("friend/fd_logo.png");
	mLoadCount->loadRes(textureRes,false);
	textureRes = TextureRes::create("friend/fd_stl.png");
	mLoadCount->loadRes(textureRes,false);
	textureRes = TextureRes::create("friend/fd_tab_mf.png");
	mLoadCount->loadRes(textureRes,false);
	textureRes = TextureRes::create("friend/fd_tab_mf_s.png");
	mLoadCount->loadRes(textureRes,false);	
	textureRes = TextureRes::create("friend/fd_tab_sq.png");
	mLoadCount->loadRes(textureRes,false);		
	textureRes = TextureRes::create("friend/fd_tab_sq_s.png");
	mLoadCount->loadRes(textureRes,false);		

	armatureRes = ArmatureRes::create("armature/kai.ExportJson",5);
	mLoadCount->loadRes(armatureRes, true);
	armatureRes = ArmatureRes::create("armature/quan.ExportJson", 1);
	mLoadCount->loadRes(armatureRes, false);
	armatureRes = ArmatureRes::create("armature/rainAnimation.ExportJson", 3);
	mLoadCount->loadRes(armatureRes, true);

	


}


void FriendRes::releaseRes()
{
	if(mLoadCount != NULL)
	{
		mLoadCount->getRecyleManager()->recyleAll();
		
	}
}




void FriendRes::startLoad(OnLoadListener *listener)
{
	if(mLoadCount != NULL) 
	{
		mLoadCount->start(listener);
	}
}

void FriendRes::startSynLoad()
{
	if(mLoadCount != NULL) 
	{
		mLoadCount->startSynLoad();
	}
}

int FriendRes::getResSize()
{
	if(mLoadCount != NULL) 
	{
		return mLoadCount->getResSize();
	} else 
	{
		return 0;
	}
}

int FriendRes::getResCount()
{
	if(mLoadCount != NULL) 
	{
		return mLoadCount->getResCount();
	} else 
	{
		return 0;
	}
}

Vector<IRes*>* FriendRes::getResArray()
{
	return mLoadCount->getResArray();
}
