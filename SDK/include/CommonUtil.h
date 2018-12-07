#pragma once
#include <string>
using namespace std;

#ifndef COMMON_UTIL_H
#define COMMON_UTIL_H
namespace ssx_sdk {
	class CommonUtil
	{
	public:
		CommonUtil();
		~CommonUtil();

		//获取随机字符串
		static string getNonceStr();

		//获取时间 yyyyMMddHHmmss
		static string getTime();
	private:

	};
}
#endif // !COMMON_UTIL_H
