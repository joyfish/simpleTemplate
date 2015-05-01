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

//假定shot是两个字节
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

//假定int是四个字节
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

//假定long是四个字节
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

	//小端直接按照循序插入，打断需要反转字符串再插入
	writeBuffer->insert(writeBuffer->end(), (unsigned char*)tempBuffer, (unsigned char*)tempBuffer+writeLen);

	free(tempBuffer);


	return writeLen;
}

//假定shot是两个字节
int WriteDataToBufferUtils::writeShort(short t,std::vector<unsigned char> *writeBuffer)
{
	int writeLen = sizeof(short);
	unsigned char *tempBuffer =  (unsigned char*)malloc(writeLen);
	memcpy(tempBuffer,&t, writeLen);

	//小端直接按照循序插入，打断需要反转字符串再插入
	writeBuffer->insert(writeBuffer->end(), (unsigned char*)tempBuffer, (unsigned char*)tempBuffer+writeLen);

	free(tempBuffer);


	return writeLen;
}

//假定int是四个字节
int  WriteDataToBufferUtils::writeInt(int t,std::vector<unsigned char> *writeBuffer)
{
	int writeLen = sizeof(int);
	unsigned char *tempBuffer =  (unsigned char*)malloc(writeLen);
	memcpy(tempBuffer,&t, writeLen);

	//小端直接按照循序插入，打断需要反转字符串再插入
	writeBuffer->insert(writeBuffer->end(), (unsigned char*)tempBuffer, (unsigned char*)tempBuffer+writeLen);

	 free(tempBuffer);


	return writeLen;
}

//假定long是四个字节
int  WriteDataToBufferUtils::writeLong(long long t,std::vector<unsigned char> *writeBuffer)
{
	int writeLen = sizeof(long long);
	unsigned char *tempBuffer =  (unsigned char*)malloc(writeLen);
	memcpy(tempBuffer,&t, writeLen);

	//小端直接按照循序插入，打断需要反转字符串再插入
	writeBuffer->insert(writeBuffer->end(), (unsigned char*)tempBuffer, (unsigned char*)tempBuffer+writeLen);
	 free(tempBuffer);

	return writeLen;
}
