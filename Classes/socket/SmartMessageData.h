#ifndef _SMART_MESSAGE_DATA_H_
#define _SMART_MESSAGE_DATA_H_

#include <string>
#include "cocos2d.h"
#include <vector>

typedef unsigned char byte;

class SmartMessageData : public cocos2d::Ref
{
public:
	SmartMessageData(void);
	SmartMessageData(int action);
	~SmartMessageData(void);    

	CREATE_FUNC(SmartMessageData);


	static SmartMessageData* create(int action) 
	{ 
		SmartMessageData *pRet = new SmartMessageData(action); 
		if (pRet && pRet->init()) 
		{ 
			pRet->autorelease(); 
			return pRet; 
		} 
		else 
		{ 
			delete pRet; 
			pRet = NULL; 
			return NULL; 
		} 
	}

	bool init(){return true;}

	SmartMessageData* writeBool(bool value);

	SmartMessageData* writeShort(short t);

	SmartMessageData* writeInt(int t);

	SmartMessageData* writeLong(long long t);

	SmartMessageData* writeString(std::string str);

	bool getBool();

	short getShort();

	int getInt();

	long long getLong();

	const std::string getString();

	void setDataLength(int dataLength);

	int getDataLength();

	std::vector<unsigned char>* getData();

	void setData(char* msgBody,int len);

private:
	int dataLength;
	int bufferIndex;

	//CC_SYNTHESIZE(int, xuliehao, Xuliehao);
	CC_SYNTHESIZE(int, action, Action);
	//CC_SYNTHESIZE(int, timeStamp, TimeStamp);


	std::vector<unsigned char>   mBuffer;

	static const int  BYTE_LEN = 1;
    static const int  INT_LEN = 4;
	static const int  SHORT_LEN = 2;
	static const int  LONG_LEN = 8;

	static const unsigned char  byteIntType = 1;
	static const unsigned char  byteLongType = 2;
	static const unsigned char  byteStringType = 3;
	static const unsigned char  byteBoolType = 4;
};
#endif // _SMART_MESSAGE_DATA_H_
