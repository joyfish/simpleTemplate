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

	//С��ֱ�Ӱ���ѭ����룬�����Ҫ��ת�ַ����ٲ���
	writeBuffer->insert(writeBuffer->end(), (unsigned char*)tempBuffer, (unsigned char*)tempBuffer+writeLen);

	delete tempBuffer;


	return writeLen;
}

//�ٶ�shot�������ֽ�
int WriteDataToBufferUtils::writeShort(short t,std::vector<unsigned char> *writeBuffer)
{
	int writeLen = sizeof(short);
	unsigned char *tempBuffer = new unsigned char[writeLen];
	memcpy(tempBuffer,&t, writeLen);

	//С��ֱ�Ӱ���ѭ����룬�����Ҫ��ת�ַ����ٲ���
	writeBuffer->insert(writeBuffer->end(), (unsigned char*)tempBuffer, (unsigned char*)tempBuffer+writeLen);

	delete tempBuffer;


	return writeLen;
}

//�ٶ�int���ĸ��ֽ�
int  WriteDataToBufferUtils::writeInt(int t,std::vector<unsigned char> *writeBuffer)
{
	int writeLen = sizeof(int);
	unsigned char *tempBuffer = new unsigned char[writeLen];//(unsigned char*)malloc(writeLen);
	memcpy(tempBuffer,&t, writeLen);

	//С��ֱ�Ӱ���ѭ����룬�����Ҫ��ת�ַ����ٲ���
	writeBuffer->insert(writeBuffer->end(), (unsigned char*)tempBuffer, (unsigned char*)tempBuffer+writeLen);

	 delete(tempBuffer);


	return writeLen;
}

//�ٶ�long���ĸ��ֽ�
int  WriteDataToBufferUtils::writeLong(long long t,std::vector<unsigned char> *writeBuffer)
{
	int writeLen = sizeof(long long);
	unsigned char *tempBuffer = new unsigned char[writeLen];
	memcpy(tempBuffer,&t, writeLen);

	//С��ֱ�Ӱ���ѭ����룬�����Ҫ��ת�ַ����ٲ���
	writeBuffer->insert(writeBuffer->end(), (unsigned char*)tempBuffer, (unsigned char*)tempBuffer+writeLen);
	 delete(tempBuffer);

	return writeLen;
}
