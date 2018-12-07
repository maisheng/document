#include "callbackimpl.h"
#include "SSX_SDK.h"

using namespace std;

void CallBackImpl::queryOrder(string parkCode,string orderId, string carNumber) {
    cout << "client interface impl queryOrder() " << endl;

    const string _orderId=orderId;
    const string _parkCode=parkCode;
    const string _carNumber=carNumber;//carNumber
    const string inTime="20180831123056";
    const string inChannel="0001";
    const string outTime="20180831133056";
    const string outChannel="0001";
    const long duration=3600;
    const int orderAmount=300;

    cout << "CallBackImpl --> _carNumber() -->" << _carNumber << endl;
    string responseData = "";
    responseData = SSXSDK::pushOrder(_orderId, _carNumber, inTime,inChannel, outTime, outChannel, duration,orderAmount);

    cout << "CallBackImpl --> queryOrder() -->" << responseData << endl;
}


void CallBackImpl::scanQrCodePay(string parkCode,string sysCode,string channel,string scanNumber,string orderId,string carNumber,int tempCar){
    cout << "client interface impl scanQrCodePay() parkCode:"<< parkCode << endl;
    cout << "client interface impl scanQrCodePay() sysCode:"<< sysCode << endl;
    cout << "client interface impl scanQrCodePay() channel:"<< channel  << endl;
    cout << "client interface impl scanQrCodePay() scanNumber:"<< scanNumber << endl;
    cout << "client interface impl scanQrCodePay() tempCar:"<< tempCar << endl;
    //获取出口要出场的唯一一个车场的订单数据
    //    const string orderId="201809140002";
    //    const string carNumber="A888888";
    const string inTime="20180831123056";
    const string inChannel="0001";
    const string outTime="20180831133056";
    const string outChannel="0001";
    const long duration=3600;
    const int orderAmount=300;
    string responseData="";
    responseData = SSXSDK::scanningOrder(scanNumber,orderId,carNumber,inTime ,inChannel,outTime,outChannel,duration,orderAmount);

    cout << "CallBackImpl --> scanQrCodePay() -->" << responseData << endl;
}

void CallBackImpl::scanQrEntry(string parkCode,string sysCode,string channel,string carNumber,string scanNumber){
    cout << "client interface impl scanQrEntry() " << endl;

    cout << "client interface impl scanQrEntry() parkCode --> " << parkCode << endl;
    cout << "client interface impl scanQrEntry() sysCode --> " << sysCode << endl;
    cout << "client interface impl scanQrEntry() channel --> " << channel << endl;
    cout << "client interface impl scanQrEntry() carNumber --> " << carNumber << endl;
    cout << "client interface impl scanQrEntry() scanNumber --> " << scanNumber << endl;

    //车场自行判断数据入口是否有车辆等待入场 放行入场推送 入场数据
}


void CallBackImpl::noticeOfPaymentResult(string orderId, string carNumber,int payStatus,int orderAmount,int duration,string inTime,string outTime,string payTime,int payMethod,string parkCode){
    cout << "client interface impl noticeOfPaymentResult() " << endl;
    if(payStatus == 0){
        cout << "client interface impl noticeOfPaymentResult() pay error!" << endl;
    }else{
        cout << "client interface impl noticeOfPaymentResult() pay success!" << endl;
    }
}

