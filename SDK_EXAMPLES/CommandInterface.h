#pragma once
//数据上行接口
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

		//查询订单的数据【预付费查询车场的订单】
		virtual void queryOrder(string parkCode,string orderId,string carNumber);
		
		//扫码支付场景 车场推送在车场出口唯一一个要出场的订单数据
		virtual void scanQrCodePay(string parkCode,string sysCode,string channel,string scanNumber,string orderId,string carNumber,int tempCar);

		//扫码入场通知
		virtual void scanQrEntry(string parkCode,string sysCode,string channel,string carNumber, string scanNumber);

		//支付结果通知
		virtual void noticeOfPaymentResult(string orderId, string carNumber,int payStatus,int payAmount,int duration,string inTime,string outTime,string payTime,int payMethod,string parkCode);

	private:

	};
}

#endif // !UPLINK_INTERFACE_H


