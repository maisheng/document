#include "callbackservice.h"
#include "SSX_SDK.h"
#include <iostream>
#include <string>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QVariantMap>

using namespace std;
using namespace ssx_sdk;

CallBackService::CallBackService()
{

}


CallBackService::~CallBackService()
{

}

int charLength(const char* str){
    int len = 0;
    while(str[len]){
        len = len + 1;
    }
    return len;
}

void CallBackService::handleNotice(const char* strJsonData){

    cout << "CallBackService-->handleNotice()" << endl;

    cout << "CallBackService-->handleNotice() param "<< strJsonData << endl;

     cout << "CallBackService-->handleNotice() charLength "<< charLength(strJsonData) << endl;
    int valuesize = charLength(strJsonData);
    QByteArray jsonData = QByteArray(strJsonData,valuesize);
    QString simpjson_str(jsonData);

    string cstr = string(jsonData);
    cout << " request data:  "<< cstr << endl;
    //    char *qc  = new char[1024];
    //    strcpy(qc,strJsonData);
    //    QString qStr = QString(QLatin1String(qc));

    //    QByteArray cdata = qStr.toLatin1();

    //解析json数据
    QJsonParseError error;
    QJsonDocument document = QJsonDocument::fromJson(simpjson_str.toUtf8(), &error);

    if(QJsonParseError::NoError == error.error)
    {   //map
        QVariantMap map = document.toVariant().toMap();

        string command = map["command"].toString().toStdString();
        cout << "CallBackService-->handleNotice() command : "<< command << endl;
        if (command.size() > 0 && strcmp("", command.c_str()) != 0) {
            string responseStr="is empty!";
            if (strcmp("prePay", command.c_str()) == 0) {//查询订单(预支付场景)

                string orderId = map["orderId"].toString().toStdString();
                string carNumber = map["carNumber"].toString().toStdString();
                string parkCode = map["parkCode"].toString().toStdString();

                QString str = map["carNumber"].toString();
                QByteArray cdata = str.toLocal8Bit();
                carNumber = string(cdata);
                cout << "carNumber : " << carNumber << endl;
                //根据orderId和carNumber查询出相应的订单数据

                const string inTime="20180831123056";
                const string inChannel="0001";
                const string outTime="20180831133056";
                const string outChannel="0001";
                const long duration=3600;
                const int orderAmount=300;

                responseStr = SSXSDK::pushOrder(orderId, carNumber, inTime,inChannel, outTime, outChannel, duration,orderAmount);
            }
            else if (strcmp("qrCodePay", command.c_str()) == 0) {//扫描二维码支付  出场扫码支付
                string parkCode = map["parkCode"].toString().toStdString();
                string sysCode = map["sysCode"].toString().toStdString();
                string channel = map["channel"].toString().toStdString();
                string scanNumber = map["scanNumber"].toString().toStdString();
                string orderId = map["orderId"].toString().toStdString();
                string carNumber = map["carNumber"].toString().toStdString();
                int tempCar = map["tempCar"].toInt();//是否是临时车牌 1true 0false

                const string inTime="20180831123056";
                const string inChannel="0001";
                const string outTime="20180831133056";
                const string outChannel="0001";
                const long duration=3600;
                const int orderAmount=300;

                responseStr = SSXSDK::scanningOrder(scanNumber,orderId,carNumber,inTime ,inChannel,outTime,outChannel,duration,orderAmount);
            }
            else if (strcmp("qrCodeEntry", command.c_str()) == 0) {//扫码入场通知
                string parkCode = map["parkCode"].toString().toStdString();
                string sysCode = map["sysCode"].toString().toStdString();
                string channel = map["channel"].toString().toStdString();
                string carNumber = map["carNumber"].toString().toStdString();
                string scanNumber = map["scanNumber"].toString().toStdString();

                cout << "client interface impl scanQrEntry() " << endl;

                cout << "client callFunction qrCodeEntry parkCode --> " << parkCode << endl;
                cout << "client callFunction qrCodeEntry sysCode --> " << sysCode << endl;
                cout << "client callFunction qrCodeEntry channel --> " << channel << endl;
                cout << "client callFunction qrCodeEntry carNumber --> " << carNumber << endl;
                cout << "client callFunction qrCodeEntry scanNumber --> " << scanNumber << endl;
            }
            else if (strcmp("payNotice", command.c_str()) == 0)
            {//支付通知
                string orderId = map["orderId"].toString().toStdString();
                string carNumber = map["carNumber"].toString().toStdString();
                int payStatus = map["payStatus"].toInt();
                int payAmount = map["payAmount"].toInt();
                int duration = map["duration"].toInt();
                string inTime = map["inTime"].toString().toStdString();
                string outTime = map["outTime"].toString().toStdString();
                string payTime = map["payTime"].toString().toStdString();
                int payMethod = map["payMethod"].toInt();
                string parkCode = map["parkCode"].toString().toStdString();

                cout << "payNotice orderId " << orderId << endl;
                cout << "payNotice carNumber " << carNumber << endl;
                cout << "payNotice payStatus " << payStatus << endl;
                cout << "payNotice payAmount " << payAmount << endl;
                cout << "payNotice duration " << duration << endl;
                cout << "payNotice inTime " << inTime << endl;
                cout << "payNotice outTime " << outTime << endl;
                cout << "payNotice payTime " << payTime << endl;
                 cout << "payNotice payMethod " << payMethod << endl;
                  cout << "payNotice parkCode " << parkCode << endl;

                cout << "client interface impl noticeOfPaymentResult() " << endl;
                if(payStatus == 0){
                    cout << "client interface impl noticeOfPaymentResult() pay error!" << endl;
                }else{
                    cout << "client interface impl noticeOfPaymentResult() pay success!" << endl;
                }
            }
            else {
                cout << " CallBackService handleNotice () Unknown command !" << endl;
            }

            cout << "CallBackService --> handleNotice() responseData -->" << responseStr << endl;
        }else{
            cout << "CallBackService-->handleNotice() command is null " << endl;
        }
    }else{
        //        cout << error.errorString() << endl;
        cout << "CallBackService-->handleNotice() Parsing error!!!! " << endl;
    }

}
