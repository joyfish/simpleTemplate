#include "WriteDataToBufferUtils.h"


WriteDataToBufferUtils::WriteDataToBufferUtils(void)
{
}


WriteDataToBufferUtils::~WriteDataToBufferUtils(void)
{
}


int WriteDataToBufferUtils::writeByte(unsigned char t,unsigned char  * buffer,int startIndex) {
	buffer += startIndex;
	*buffer = t ; 

	return 1;
}

//�ٶ�shot�������ֽ�
int WriteDataToBufferUtils::writeShort(short t,unsigned char * buffer,int startIndex){
	
	buffer += startIndex;

	for (int  i = 0; i< sizeof(short); ++i) 
	{  
		*buffer = (unsigned char)(t & 0xFF) ; 
		buffer++;

		t >>= 8; 
	}
	return 2;
}

//�ٶ�int���ĸ��ֽ�
int  WriteDataToBufferUtils::writeInt(int t,unsigned char * buffer,int startIndex){

	buffer += startIndex;

	for (int  i = 0; i< sizeof(int); ++i) 
	{  
		*buffer = (unsigned char)(t & 0xFF) ; 
		buffer++;

		t >>= 8; 
	}
	return 4;
}

//�ٶ�long���ĸ��ֽ�
int  WriteDataToBufferUtils::writeLong(long long t,unsigned char * buffer,int startIndex){
	buffer += startIndex;

	for (int  i = 0; i< sizeof(long long); ++i) 
	{  
		*buffer = (unsigned char)(t & 0xFF) ; 
		buffer++;

		t >>= 8; 
	}

	return 8;
}

int WriteDataToBufferUtils::writeByte(unsigned char t,std::vector<unsigned char> *writeBuffer) 
{
	int writeLen = sizeof(unsigned char);
	unsigned char *tempBuffer =  (unsigned char*)malloc(writeLen);
	memcpy(tempBuffer,&t, writeLen);

	//С��ֱ�Ӱ���ѭ����룬�����Ҫ��ת�ַ����ٲ���
	writeBuffer->insert(writeBuffer->end(), (unsigned char*)tempBuffer, (unsigned char*)tempBuffer+writeLen);

	free(tempBuffer);


	return writeLen;
}

//�ٶ�shot�������ֽ�
int WriteDataToBufferUtils::writeShort(short t,std::vector<unsigned char> *writeBuffer)
{
	int writeLen = sizeof(short);
	unsigned char *tempBuffer =  (unsigned char*)malloc(writeLen);
	memcpy(tempBuffer,&t, writeLen);

	//С��ֱ�Ӱ���ѭ����룬�����Ҫ��ת�ַ����ٲ���
	writeBuffer->insert(writeBuffer->end(), (unsigned char*)tempBuffer, (unsigned char*)tempBuffer+writeLen);

	free(tempBuffer);


	return writeLen;
}

//�ٶ�int���ĸ��ֽ�
int  WriteDataToBufferUtils::writeInt(int t,std::vector<unsigned char> *writeBuffer)
{
	int writeLen = sizeof(int);
	unsigned char *tempBuffer =  (unsigned char*)malloc(writeLen);
	memcpy(tempBuffer,&t, writeLen);

	//С��ֱ�Ӱ���ѭ����룬�����Ҫ��ת�ַ����ٲ���
	writeBuffer->insert(writeBuffer->end(), (unsigned char*)tempBuffer, (unsigned char*)tempBuffer+writeLen);

	 free(tempBuffer);


	return writeLen;
}

//�ٶ�long���ĸ��ֽ�
int  WriteDataToBufferUtils::writeLong(long long t,std::vector<unsigned char> *writeBuffer)
{
	int writeLen = sizeof(long long);
	unsigned char *tempBuffer =  (unsigned char*)malloc(writeLen);
	memcpy(tempBuffer,&t, writeLen);

	//С��ֱ�Ӱ���ѭ����룬�����Ҫ��ת�ַ����ٲ���
	writeBuffer->insert(writeBuffer->end(), (unsigned char*)tempBuffer, (unsigned char*)tempBuffer+writeLen);
	 free(tempBuffer);

	return writeLen;
}
