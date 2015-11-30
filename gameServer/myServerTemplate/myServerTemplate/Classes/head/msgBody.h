#include "../socket/SmartMessageData.h"
#include <iostream>
class CMD_Constant
{
public:
	static const int ACTION_TEST1 = 1111;
	static const int ACTION_TEST2 = 1112;
};

template <class T>
void SEND_MSGBODY_TO_SERVER(T msgBody)
{
	SmartMessageData * data = SmartMessageData::create();
	data->retain();
	data << msgBody;
	data->setAction(msgBody.CMD_ID);
	myMessageManager::getInstance()->sendMessage(data);
}


struct msgBody_sample_1
{
	enum { CMD_ID = CMD_Constant::ACTION_TEST1 };
private:
	CC_SYNTHESIZE(int, _aaa, AAA);
	CC_SYNTHESIZE(std::string, _bbb, BBB);
public:
	//从msgBody_sample_1输出到SmartMessageData
	friend SmartMessageData * operator << (SmartMessageData * data, msgBody_sample_1 msg)
	{
		data->writeInt(msg.getAAA());
		data->writeString(msg.getBBB());
		return data;
	}
	//从SmartMessageData输入到msgBody_sample_1
	friend SmartMessageData * operator >> (SmartMessageData *data, msgBody_sample_1 &msg)
	{
		msg.setAAA(data->getInt());
		msg.setBBB(data->getString());
		return data;
	}

};


class msgBody_sample_2
{
	enum { CMD_ID = CMD_Constant::ACTION_TEST2 };
private:
	CC_SYNTHESIZE(int, _ccc, CCC);
	CC_SYNTHESIZE(msgBody_sample_1, _ddd, DDD);
public:

	friend SmartMessageData * operator << (SmartMessageData * data, msgBody_sample_2 msg)
	{
		data->writeInt(msg.getCCC());
		data << msg.getDDD();
		return data;
	}

	friend SmartMessageData * operator >> (SmartMessageData *data, msgBody_sample_2 &msg)
	{
		msg.setCCC(data->getInt());
		msgBody_sample_1 temp;
		data >> temp;
		msg.setDDD(temp);
		return data;
	}

};