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

		//��ȡ����ַ���
		static string getNonceStr();

		//��ȡʱ�� yyyyMMddHHmmss
		static string getTime();
	private:

	};
}
#endif // !COMMON_UTIL_H
