#include "SmartMessageData.h"
#include <string>
#include "WriteDataToBufferUtils.h"

using namespace std;

SmartMessageData::SmartMessageData(void)
{
	this->dataLength = 0;
	this->bufferIndex = 0;
	this->action = 0;
}

SmartMessageData::SmartMessageData(int action)
{
	this->dataLength = 0;
	this->bufferIndex = 0;
	this->action = action;
}


SmartMessageData::~SmartMessageData(void)
{

}

SmartMessageData* SmartMessageData::writeBool(bool value)
{
	int count = 0;
	
	count = WriteDataToBufferUtils::writeByte((byte)value,&mBuffer);

	dataLength += count;

	return this;
}

bool SmartMessageData::getBool()
{
	
	unsigned char tempBuffer[BYTE_LEN];
	std::vector<unsigned char>::iterator iter = mBuffer.begin() ;
	for(int i = 0; i < BYTE_LEN; i++) 
	{
		tempBuffer[i] = *(iter + bufferIndex);
		bufferIndex++;
	}

	bool value = false;
	memcpy(&value,tempBuffer, BYTE_LEN);

	return value;
}

SmartMessageData* SmartMessageData::writeShort(short t)
{
	int count = 0;

	count = WriteDataToBufferUtils::writeShort(t, &mBuffer);

	dataLength += count;

	return this;
}

short SmartMessageData::getShort()
{
	unsigned char tempBuffer[SHORT_LEN];
	std::vector<unsigned char>::iterator iter = mBuffer.begin();
	for (int i = 0; i < SHORT_LEN; i++)
	{
		tempBuffer[i] = *(iter + bufferIndex);
		bufferIndex++;
	}

	short value = 0;
	memcpy(&value, tempBuffer, SHORT_LEN);


	return value;
}

SmartMessageData* SmartMessageData::writeInt(int t) {
	
	int count = 0;

	count = WriteDataToBufferUtils::writeInt(t,&mBuffer);

	dataLength += count;

	return this;
}

int SmartMessageData::getInt() {
	
	unsigned char tempBuffer[INT_LEN];
	std::vector<unsigned char>::iterator iter = mBuffer.begin() ;
	for(int i = 0; i < INT_LEN; i++) 
	{
		tempBuffer[i] = *(iter + bufferIndex);
		bufferIndex++;
	}

	int value = 0;
	memcpy(&value,tempBuffer, INT_LEN);


	return value;
}

SmartMessageData* SmartMessageData::writeLong(long long  t) {
	
	int count = 0;

	count = WriteDataToBufferUtils::writeLong(t,&mBuffer);

	dataLength += count;

	return this;
}

long long SmartMessageData::getLong() {
	
	unsigned char tempBuffer[LONG_LEN];
	std::vector<unsigned char>::iterator iter = mBuffer.begin() ;
	for(int i = 0; i < LONG_LEN; i++) 
	{
		tempBuffer[i] = *(iter + bufferIndex);
		bufferIndex++;
	}

	long long  value = 0;
	memcpy(&value,tempBuffer, LONG_LEN);

	return value;
}

SmartMessageData* SmartMessageData::writeString(string utf) {

	 int utfLen = utf.size();

	 int count = 0;

	count = WriteDataToBufferUtils::writeInt(utfLen,&mBuffer);

	dataLength += count;

	mBuffer.insert(mBuffer.end(), utf.c_str(), utf.c_str()+utfLen);

	dataLength += utfLen;

	return this;
}

const string SmartMessageData::getString()
{
	unsigned char tempBuffer[INT_LEN];
	std::vector<unsigned char>::iterator iter = mBuffer.begin() ;
	for(int i = 0; i < INT_LEN; i++) 
	{
		tempBuffer[i] = *(iter + bufferIndex);
		bufferIndex++;
	}
	int strByteNum = 0;
	memcpy(&strByteNum,tempBuffer, INT_LEN);

	std::string result = "";
	
	std::vector<unsigned char>::iterator utfIter = mBuffer.begin() ;
	for(int i = 0; i < strByteNum; i++) 
	{
		result += *(utfIter + bufferIndex);
		bufferIndex++;
	}

	return result;
}


void SmartMessageData::setDataLength(int dataLength)
{
	this->dataLength = dataLength;
}

int SmartMessageData::getDataLength() 
{
	return this->dataLength;
}

 std::vector<unsigned char>* SmartMessageData::getData() 
{
	return &(this->mBuffer);
}

void SmartMessageData::setData(char* msgBody,int len) 
{
	mBuffer.insert(mBuffer.end(), (char*)msgBody, (char*)msgBody+len);
	this->dataLength = len;
}

