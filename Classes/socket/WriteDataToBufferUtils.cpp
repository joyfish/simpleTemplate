#include "WriteDataToBufferUtils.h"
#include "cocos2d.h"


WriteDataToBufferUtils::WriteDataToBufferUtils(void)
{
}


WriteDataToBufferUtils::~WriteDataToBufferUtils(void)
{
}

int WriteDataToBufferUtils::writeByte(unsigned char t,std::vector<unsigned char> *writeBuffer) 
{
	int writeLen = sizeof(unsigned char);
	unsigned char *tempBuffer = new unsigned char[writeLen];
	memcpy(tempBuffer,&t, writeLen);

	//小端直接按照循序插入，打断需要反转字符串再插入
	writeBuffer->insert(writeBuffer->end(), (unsigned char*)tempBuffer, (unsigned char*)tempBuffer+writeLen);

	delete tempBuffer;


	return writeLen;
}

//假定shot是两个字节
int WriteDataToBufferUtils::writeShort(short t,std::vector<unsigned char> *writeBuffer)
{
	int writeLen = sizeof(short);
	unsigned char *tempBuffer = new unsigned char[writeLen];
	memcpy(tempBuffer,&t, writeLen);

	//小端直接按照循序插入，打断需要反转字符串再插入
	writeBuffer->insert(writeBuffer->end(), (unsigned char*)tempBuffer, (unsigned char*)tempBuffer+writeLen);

	delete tempBuffer;


	return writeLen;
}

//假定int是四个字节
int  WriteDataToBufferUtils::writeInt(int t,std::vector<unsigned char> *writeBuffer)
{
	int writeLen = sizeof(int);
	unsigned char *tempBuffer = new unsigned char[writeLen];//(unsigned char*)malloc(writeLen);
	memcpy(tempBuffer,&t, writeLen);

	//小端直接按照循序插入，打断需要反转字符串再插入
	writeBuffer->insert(writeBuffer->end(), (unsigned char*)tempBuffer, (unsigned char*)tempBuffer+writeLen);

	 delete(tempBuffer);


	return writeLen;
}

//假定long是四个字节
int  WriteDataToBufferUtils::writeLong(long long t,std::vector<unsigned char> *writeBuffer)
{
	int writeLen = sizeof(long long);
	unsigned char *tempBuffer = new unsigned char[writeLen];
	memcpy(tempBuffer,&t, writeLen);

	//小端直接按照循序插入，打断需要反转字符串再插入
	writeBuffer->insert(writeBuffer->end(), (unsigned char*)tempBuffer, (unsigned char*)tempBuffer+writeLen);
	 delete(tempBuffer);

	return writeLen;
}
