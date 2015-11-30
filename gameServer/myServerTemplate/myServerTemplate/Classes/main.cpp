#include "head\head.h"
#include "socket\mySocketUtils.h"
#include "hello.h"
using namespace std;

int main()
{
	hello * hh = hello::create();
	mySocketUtils::getInstance()->startServer();

	return 0;
}