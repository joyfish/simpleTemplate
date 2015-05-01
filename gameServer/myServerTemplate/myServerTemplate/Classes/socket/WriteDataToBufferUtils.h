#ifndef __WRITE_DATA_TO_BUFFER_UTILS_H__
#define __WRITE_DATA_TO_BUFFER_UTILS_H__
#include <vector>

//‘≠¿‡
class WriteDataToBufferUtils
{
public:
	WriteDataToBufferUtils(void);
	~WriteDataToBufferUtils(void);

	int static writeShort(short t, unsigned char * buff, int startIndex);

	int static writeInt(int t, unsigned char * buff, int startIndex);

	int static writeLong(long long t, unsigned char  * buff, int startIndex);

	int static writeByte(unsigned char t, unsigned char  * buff, int startIndex);


	int static writeShort(short t, std::vector<unsigned char> *writeBuffer);

	int static writeInt(int t, std::vector<unsigned char> *writeBuffer);

	int static writeLong(long long t, std::vector<unsigned char> *writeBuffer);

	int static writeByte(unsigned char t, std::vector<unsigned char> *writeBuffer);

};
#endif