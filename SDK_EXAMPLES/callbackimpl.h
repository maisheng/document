#include <iostream>
#include "CommandInterface.h"

using namespace std;
using namespace ssx_sdk;

#ifndef CALLBACKIMPL_H
#define CALLBACKIMPL_H

class CallBackImpl:public CommandInterface
{
public:
    CallBackImpl() {}

    //预支付场景 获取订单数据
    void queryOrder(string parkCode, string orderId, string carNumber);

    //扫码支付获取最新要出场且在出场闸口的车辆订单数据
    void scanQrCodePay(string parkCode,string sysCode,string channel,string scanNumber,string orderId,string carNumber,int tempCar);

    //扫码入场
    void scanQrEntry(string parkCode,string sysCode,string channel,string carNumber,string scanNumber);

    //支付结果通知
    void noticeOfPaymentResult(string orderId, string carNumber,int payStatus,int orderAmount,int duration,string inTime,string outTime,string payTime,int payMethod,string parkCode);
};


#endif // CALLBACKIMPL_H
