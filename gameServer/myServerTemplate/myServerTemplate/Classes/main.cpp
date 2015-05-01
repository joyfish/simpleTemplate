#include "head\head.h"
#include "socket\mySocketUtils.h"

using namespace std;

int main()
{
	mySocketUtils::getInstance()->startServer();

	return 0;
}