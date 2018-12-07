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
		//ϵͳ��ʼ��
		static string init(const string manufacturer, const string parkCode, const string sysCode,const string channelNumber, const string key, const string ssxUrl);
		
		//����ʼ��
		static void unInit();
		
		//�����볡
		static string entry(const string carNumber, const string inTime, const string orderId,const string filePath,const int entryType,const string scanNumber);
		
		//�����볡 �볡ǰ ����ɷ�
		static string leave(const string carNumber, const string outTime, const string orderId, const long duration,const int orderAmount, const string filePath, const int outType, const string scanNumber);
		
		//�����볡�����Ͷ���������������
		static string finish(const string orderId, const string carNumber, const string finishTime);
		
		//������ѯ
		static string queryOrder(const string orderId);
		
		//���Ͷ���������۷ѡ������ɷѡ�
        static string pushOrder(const string orderId, const string carNumber, const string inTime, 
			const string inChannel, const string outTime, const string outChannel, const long duration, const int payAmount);

		//���Ͷ���������۷ѡ�ɨ��֧����
		static string scanningOrder(const string scanNumner,const string orderId,const string carNumber, const string inTime,
			const string inChannel, const string outTime, const string outChannel, const long duration, const int payAmount);

		//�ļ��ϴ�  orderId������ˮ�� �ļ�·�� attType�������entry�볡 out�볡
		static string uploadFile(const string orderId, const string filePath,const string attType);
		
		//���䶩��
		static string suppOrder(const string carNumber, const string startTime, const string endTime, const string orderId, const long duration, const int orderAmount);
		
		//��ѳ�������
		static string freeCar(const string carNumber,const string startTime,const string endTime, const string remarks, const bool delFlag);

		//���ûص���ʵ���� ������ʵ��
		static void setCommandInterface(CommandInterface *uplink);

		//���ǻص����� ��Ҫ����֪ͨ
		static void setCallBackFun(CallBackFun pCallBackFun);
	private:

	};
}

#endif // !SSX_SDK_H
