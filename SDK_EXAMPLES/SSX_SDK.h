#pragma once

#include "SSX_SDK_DEF.h"
#include <string>
#include "CommandInterface.h"

using namespace std;

#ifndef SSX_SDK_H
#define SSX_SDK_H

namespace ssx_sdk {
	class SSX_SDK_API SSXSDK
	{
	public:
		SSXSDK();
		~SSXSDK();
		//系统初始化
		static string init(const string manufacturer, const string parkCode, const string sysCode,const string channelNumber, const string key, const string ssxUrl);
		
		//反初始化
		static void unInit();
		
		//车辆入场
		static string entry(const string carNumber, const string inTime, const string orderId,const string filePath,const int entryType,const string scanNumber);
		
		//车辆离场 离场前 发起缴费
		static string leave(const string carNumber, const string outTime, const string orderId, const long duration,const int orderAmount, const string filePath, const int outType, const string scanNumber);
		
		//车辆离场后推送订单结束交易请求
		static string finish(const string orderId, const string carNumber, const string finishTime);
		
		//订单查询
		static string queryOrder(const string orderId);
		
		//推送订单不发起扣费【出场缴费】
        static string pushOrder(const string orderId, const string carNumber, const string inTime, 
			const string inChannel, const string outTime, const string outChannel, const long duration, const int payAmount);

		//推送订单不发起扣费【扫码支付】
		static string scanningOrder(const string scanNumner,const string orderId,const string carNumber, const string inTime,
			const string inChannel, const string outTime, const string outChannel, const long duration, const int payAmount);

		//文件上传  orderId订单流水号 文件路径 attType附件类别entry入场 out离场
		static string uploadFile(const string orderId, const string filePath,const string attType);
		
		//补充订单
		static string suppOrder(const string carNumber, const string startTime, const string endTime, const string orderId, const long duration, const int orderAmount);
		
		//免费车辆推送
		static string freeCar(const string carNumber,const string startTime,const string endTime, const string remarks, const bool delFlag);

		//设置回调是实现类 主程序实现
		static void setCommandInterface(CommandInterface *uplink);

		//这是回调方法 主要用于通知
		static void setCallBackFun(CallBackFun pCallBackFun);
	private:

	};
}

#endif // !SSX_SDK_H
