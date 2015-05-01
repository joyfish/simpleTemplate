#pragma once
#include "cocos2d.h"

using namespace std;
using namespace cocos2d;

class LanguageConfig  : public cocos2d::Ref
{
public:

    CC_SYNTHESIZE( int , id, Id);
	 
	CC_SYNTHESIZE( std::string, chinese, Chinese);

};

