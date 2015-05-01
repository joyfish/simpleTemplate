#pragma once
#include "cocos2d.h"

using namespace std;
using namespace cocos2d;

class ItemConfig  : public cocos2d::Ref
{
public:

    CC_SYNTHESIZE( int , id, Id);
	 
	CC_SYNTHESIZE( std::string, name, Name);
	
	CC_SYNTHESIZE( int , type, Type);

	CC_SYNTHESIZE( int , quality,  Quality);

	CC_SYNTHESIZE( int , wearNeedGrade,  WearNeedGrade);
	
	CC_SYNTHESIZE(std::string, img, Img);

	CC_SYNTHESIZE( int , subType, SubType);

	CC_SYNTHESIZE(std::string, equipAttr, EquipAttr);

	CC_SYNTHESIZE( int , exchangeFromId, ExchangeFromId);

	CC_SYNTHESIZE( int , exchangeToId, ExchangeToId);

	CC_SYNTHESIZE(std::string, description, Description);
	
	//循序
	CC_SYNTHESIZE( int , order, Order);

	CC_SYNTHESIZE( int , sellMoney, SellMoney);//能卖出去的钱

};