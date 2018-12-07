#pragma once
//�������нӿ�
#include "SSX_SDK_DEF.h"
#include <string>

using namespace std;

#ifndef UPLINK_INTERFACE_H
#define UPLINK_INTERFACE_H

namespace ssx_sdk {
	class SSX_SDK_API CommandInterface
	{
	public:
		CommandInterface() {};
		virtual ~CommandInterface();

		//��ѯ���������ݡ�Ԥ���Ѳ�ѯ�����Ķ�����
		virtual void queryOrder(string parkCode,string orderId,string carNumber);
		
		//ɨ��֧������ ���������ڳ�������Ψһһ��Ҫ�����Ķ�������
		virtual void scanQrCodePay(string parkCode,string sysCode,string channel,string scanNumber,string orderId,string carNumber,int tempCar);

		//ɨ���볡֪ͨ
		virtual void scanQrEntry(string parkCode,string sysCode,string channel,string carNumber, string scanNumber);

		//֧�����֪ͨ
		virtual void noticeOfPaymentResult(string orderId, string carNumber,int payStatus,int payAmount,int duration,string inTime,string outTime,string payTime,int payMethod,string parkCode);

	private:

	};
}

#endif // !UPLINK_INTERFACE_H


