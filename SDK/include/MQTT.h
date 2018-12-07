#pragma once
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <iostream>
#include "MQTTClient.h"
#include "CommandInterface.h"

using namespace std;
#ifndef MQTT_H
#define MQTT_H
namespace ssx_sdk {
	class MQTT
	{
	public:
		MQTT(const char* address, const char* userName, const char* passWord, const char* clientId, const char* topic, const int qos, const long timeOut, const int connectTimeout, const int keepAliveInterval, const int cleanSession,const int useSslTls,const char* sslTlsVersion);
		~MQTT();
		
		//�����ͻ���
		int createClient();
		
		//������Ϣ
		void startSubscribe();
		
		//�ر�����
		void disConnect();

		//�ͻ��˵��߳�����������
		void againConnect();

		//���ûص�ʵ��
		void setCommandInterface(CommandInterface *cmd);

		void setCallBackFun(CallBackFun pCallBackFun);
	private:
		char m_address[256];
		char m_userName[256];
		char m_passWord[256];
		char m_clientId[256];
		char m_topic[256];
		int m_qos;
		long m_timeOut;
		int m_connectTimeout;
		int m_keepAliveInterval;
		int m_cleanSession;
		int m_useSslTls;
		char m_sslTlsVersion[256];
		MQTTClient m_client;
		CommandInterface *m_cmd;
		CallBackFun m_cb = NULL;
	};
}
#endif // !MQTT_H
