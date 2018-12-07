# 嗖嗖行技术对接文档

**历史版本**

版本号|完成时间|拟稿/修订人|发布时间|变更说明
---|---|---|---|---
V1.0.1|2018-09-01|ywzou、sjchen|2018-10-08|文档创建
V1.0.0|2018-12-04|ywzou|2018-12-05|支付通知增加支付发起方式、停车场编号字段，入场、出场照片非必填

## 一、概述
主要方便技术人员开发对接，实现停车费用的在线电子支付。通讯方式采用的物联协议MQTT,所以需要MQTT相关的依赖。

## 二、接口定义
### 2.1、数据请求
#### 2.1.1、SDK初始化
##### 2.1.1.1、简述
    主要实现SDK的初始化，验证SDK，绑定初始化参数。

##### 2.1.1.2、调用方法
``` C++
ssx_sdk::SSXSDK::init(const string manufacturer, const string parkCode, const string sysCode, const stringchannelNumber, const string key, const string ssxUrl);
```

##### 2.1.1.3、传入参数
参数|必选|类型|说明
---|---|---|---
manufacturer|true|string|厂商编号，嗖嗖行提供
parkCode|true|string|车场编号，嗖嗖行提供
sysCode|true|string|计费系统编号
key|true|string|签名加密秘钥，嗖嗖行提供（一个车场一份）
ssxUrl|true|string|请求路径
channelNumber|true|string|通道编号

##### 2.1.1.4、返回值
参数|类型|说明
---|---|---
code|string|返回码 0000:成功 其他表示失败
msg|string|返回信息描述


#### 2.1.2、车辆入场
##### 2.1.2.1、简述
    要实现车辆进入停车场时，停车场计费系统推送订单，记录车子入场时间、车牌号、入场照片等关键信息
##### 2.1.2.2、调用方法
``` C++
ssx_sdk::SSXSDK::entry(conststring carNumber, const string inTime, const string orderId, const stringfilePath,const int inType,const string scanNumber);
```

##### 2.1.2.3、传入参数
参数|必选|类型|说明
---|---|---|---
carNumber|true|string|入场车牌号
inTime|true|string|入场时间
orderId|true|string|车场流水号（停车场计费系统唯一单号，不可重复）
filePath|false|stirng|入场照片路径（不可包含中文路径）v1.0.1 update false
entryType|true|stirng|入场类型（2:扫码 1:智能识别）默认：1
scanNumber|false|stirng|扫描序号 当entryType为2时必传

##### 2.1.2.4、返回值
参数|类型|说明
---|---|---
code|string|返回码 0000:成功 其他表示失败
msg|string|返回信息描述

##### 2.1.2.5、示例
``` C++
#include <string>
#include <iostream>
#include "SSX_SDK.h"
 
using namespace std;
using namespace ssx_sdk;
 
int main(){
    string filePath = "E:\\images\\4.jpg";
    string carNumber = "陕A12345";
    string inTime= "20180907142001";
    string orderId = "20180907000001";
    int entryType= 1;
    string scanNumber= "";
    string res;
    res =SSXSDK::entry( carNumber, inTime, orderId, filePath,entryType,scanNumber);
 
    std::cout<< "entry() responseData ->" << res << endl;
    system("pause");
}
```
>输出结果：{"code":"0000","msg":"订单创建成功!"}


#### 2.1.3、车辆出场缴费
##### 2.1.3.1、简述
    主要实现车辆出场时缴纳停车费用
##### 2.1.3.2、调用方法
``` C++
ssx_sdk::SSXSDK::leave(conststring carNumber, const string outTime, const string orderId, const longduration, const int orderAmount, const string filePath,const int outType, conststring scanNumber);
```
##### 2.1.3.3、传入参数
参数|必选|类型|说明
---|---|---|---
carNumber|true|string|出场车牌号
outTime|true|string|出场时间
orderId|true|string|车场流水号（不能重复，用于对账）
duration|true|long|停车时长(单位：分钟)
orderAmount|true|int|停车费用(单位：分)
filePath|false|stirng|出场照片路径（不能包含中文路径）v1.0.1 update false
outType|true|stirng|出场类型（2:扫码 1:智能识别）默认:1
scanNumber|false|stirng|扫描序号扫描序号 当entryType为2时必传

##### 2.1.3.4、返回值
参数|类型|说明
---|---|---
code|string|返回码 0000:成功 其他表示失败
msg|string|返回信息描述

##### 2.1.3.5、示例
``` C++
#include <string>
#include <iostream>
#include "SSX_SDK.h"
 
using namespace std;
using namespace ssx_sdk;
 
int main(){
    string filePath = "E:\\images\\5.jpg";
    string carNumber = "陕A12345";
    string outTime = "20180907152000";
    string orderId = "20180907000001";
    long duration= 3600;//单位:分钟
    int orderAmount = 300;//单位:分
    int outType =1;
    string scanNumber= "";
 
    string res;
    res =SSXSDK::leave(carNumber, outTime, orderId, duration, orderAmount，filePath,outType,scanNumber );
    std::cout<< "leave() responseData ->" << res << endl;
    system("pause");
}
```
> 输出结果：{"code":"0001","msg":"支付成功!"}

#### 2.1.4、车辆离场
##### 2.1.4.1、简述
    车辆离开停车场以后给搜搜行云平台推动离场确认数据，完善订单信息，标识订单真正的结束
##### 2.1.4.2、调用方法
``` C++
ssx_sdk::SSXSDK::finish(const string orderId, const string carNumber, const string finishTime);
```
##### 2.1.4.3、传入参数
参数|必选|类型|说明
---|---|---|---
carNumber|true|string|车牌号
orderId|true|string|车场流水号
finishTime|true|string|订单完成时间（格式必须为yyyyMMddHHmmss）

##### 2.1.4.4、返回值
参数|类型|说明
---|---|---
code|string|返回码 0000:成功 其他表示失败
msg|string|返回信息描述

##### 2.1.4.5、示例
``` C++
#include <string>
#include <iostream>
#include "SSX_SDK.h"
 
using namespace std;
using namespace ssx_sdk;
 
int main(){
    string carNumber = "陕A888888";
    string finishTime = "20180904133533";
    string orderId = "20180907000001";
 
    res =SSXSDK::finish(orderId, carNumber, finishTime);
    std::cout <<"finish() responseData ->" << res << endl;
    system("pause");
}
```
> 输出结果：{"code":"0000","msg":"处理成功!"}


#### 2.1.5、订单查询
##### 2.1.5.1、简述
    主要实现查询订单信息
##### 2.1.5.2、调用方法
``` C++
ssx_sdk::SSXSDK::queryOrder(const string orderId);
```
##### 2.1.5.3、传入参数
参数|必选|类型|说明
---|---|---|---
orderId|true|string|车场流水号

##### 2.1.5.4、返回值
参数|类型|说明
---|---|---
code|string|返回码 0000:成功 其他表示失败
msg|string|返回信息描述
data|string|订单数据（json格式）

##### 2.1.5.5、示例
``` C++
#include <string>
#include <iostream>
#include "SSX_SDK.h"
 
using namespace std;
using namespace ssx_sdk;
 
int main(){
    string orderId = "20180904000001";
    res =SSXSDK::queryOrder(orderId);
    std::cout <<"finish() responseData ->" << res << endl;
    system("pause");
}
```
>输出结果：{"code":"0000","msg":"订单信息查询成功!",data:….}

#### 2.1.6、补缴订单
##### 2.1.6.1、简述
    补缴订单数据的推送，并发起缴费
##### 2.1.6.2、调用方法
``` C++
ssx_sdk::SSXSDK::suppOrder(const string carNumber, conststring startTime, const string endTime, const string orderId, const longduration, const int orderAmount);
```
##### 2.1.6.3、传入参数
参数|必选|类型|说明
---|---|---|---
carNumber|true|string|补缴车牌号
startTime|true|string|补缴计费开始时间 格式yyyyMMddHHmmss
endTime|true|string|补缴计费结束时间 格式yyyyMMddHHmmss
orderId|true|string|补缴订单流水号（停车场计费系统唯一单号，不可重复）
duration|true|long|补缴订单计费时长（单位：分钟）
orderAmount|true|int|补缴订单计费金额（单位：分）

##### 2.1.6.4、返回值
参数|类型|说明
---|---|---
code|string|返回码 0000:成功 其他表示失败
msg|string|返回信息描述

##### 2.1.6.示例
``` C++
#include <string>
#include <iostream>
#include "SSX_SDK.h"
 
using namespace std;
using namespace ssx_sdk;
 
int main(){
    string carNumber = "陕A888888";
    string startTime="20180904133533";
    string endTime="20180904143533";
    string orderId = "20180907000001";
    long duration= 60;
    int orderAmount= 300;
    string res;
    res =SSXSDK::suppOrder(carNumber, startTime,endTime, orderId, duration, orderAmount);
    std::cout<< " suppOrder () responseData ->" << res << endl;
    system("pause");
}
```
>输出结果：{"code":"0000","msg":"补缴成功!"}

#### 2.1.7、免费车辆推送
##### 2.1.7.1、简述
接收车场的免费车辆数据（可适用于包月的车），只做记录，实际付费以推送的订单为准，以车牌号码和结束时间作为唯一的标识，做添加修改操作，同一车场同一车牌号反复推送，若上一次结束时间大于等于系统时间上一次则做修改（有效免费数据），若上次推送的结束时间小于系统时间则作添加操作（失效过期）。
##### 2.1.7.2、调用方法
``` C++
ssx_sdk::SSXSDK::freeCar (const string carNumber,conststring startTime,const string endTime,const string remarks, const int delFlag);
```
##### 2.1.7.3、传入参数
参数|必选|类型|说明
---|---|---|---
carNumber|true|string|免费车牌号
startTime|true|string|开始时间 格式yyyyMMddHHmmss
endTime|true|string|结束时间 格式yyyyMMddHHmms
remarks|false|string|备注，不可超过200字
delFlag|false|long|删除标识(0:false 1:true) 默认0

##### 2.1.7.4、返回值
参数|类型|说明
---|---|---
code|string|返回码 0000:成功 其他表示失败
msg|string|返回信息描述

##### 2.1.7.示例
``` C++
#include <string>
#include <iostream>
#include "SSX_SDK.h"
 
using namespacestd;
using namespace ssx_sdk;
 
int main(){
    string carNumber = "陕A888888";
    string startTime="20180904133533";
    string endTime="20181003143533";
    string remarks ="包月车";
    int delFlag=0;
 
    string res =SSXSDK::freeCar(carNumber, startTime, endTime, remarks, delFlag);
    cout <<" freeCar() responseData ->" << res << endl;
    system("pause");
}
```
>输出结果：{"code":"0000","msg":"推送成功!"}

### 2.2、数据通知
SDK通知计费系统相应的操作指令。停车场计费系统更具指令类型完成相应的业务处理。实现接收通知有两个方案（详见`附录:通知实现方式`）：
①、实现通知指令接口的相关业务方法
②、编写回调函数，根据通知的指令自行实现相关的业务

#### 2.2.1、预支付（订单查询）
##### 2.2.1.1、简述
主要实现车辆未出场，车主发起提前缴费，嗖嗖行云平台将发送查询指令到SDK，SDK接收到指令以后，将相应的订单数据推送到嗖嗖行平台，用户提前支付停车费，支付成功后在规定的优惠时间内驶出停车场。

##### 2.2.1.2、调用方法
需要车场的计费系统实现接口`CommandInterface`中的`queryOrder(string orderId,string carNumber)`方法，SDK接收到查询指令后会自动调用该方法，并传入车辆入场时的唯一流水号和车牌号码，计费系统可根据流水号和车牌号码查询出订单信息然后推送（调用方法：`SSXSDK::pushOrder(_orderId,_carNumber, inTime,inChannel, outTime, outChannel, duration,orderAmount)`）到嗖嗖行平台

##### 2.2.1.3、传入参数
- SDK回调传参 （`回调方法queryOrder(...)`）

参数|必选|类型|说明
---|---|---|---
orderId|true|string|车场流水号
parkCode|true|string|停车场编号 v1.0.1 add
carNumber|true|string|车牌号

- 订单数据推送请求参数（`调用方法pushOrder(...)`）

参数|必选|类型|说明
---|---|---|---
orderId|true|string|车场流水号
carNumber|true|string|车牌号
inTime|true|string|入场时间（格式：yyyyMMddHHmmss）
inChannel|true|string|入场通道
outTime|true|string|离场时间（格式：yyyyMMddHHmmss）
outChannel|true|string|离场通道
duration|true|string|停车时长（单位：分）
orderAmount|true|string|停车费用（单位：分）

##### 2.2.1.4、数据推送返回值
参数|类型|说明
---|---|---
code|string|返回码 0000:成功 其他表示失败
msg|string|返回信息描述

##### 2.2.1.5、示例
> callbackimpl.h
``` C++
#include <iostream>
#include "CommandInterface.h"
 
using namespace std;
using namespace ssx_sdk;
 
#ifndef CALLBACKIMPL_H
#define CALLBACKIMPL_H
 
class CallBackImpl:public CommandInterface{
public:
    CallBackImpl(){}
    //预支付场景 获取订单数据
    void queryOrder(string orderId, string carNumber);
    //扫码支付获取最新要出场且在出场闸口的车辆订单数据
    void scanQrCodePay(string parkCode,string sysCode,string channel,string scanNumber,string orderId,string carNumber,int tempCar);
    //扫码入场
    voidscanQrEntry(string parkCode,string sysCode,string channel,string carNumber);
    //支付结果通知
    void noticeOfPaymentResult(string orderId, string carNumber,int payStatus,int orderAmount,int duration,string inTime,string outTime,string payTime);
};
#endif // CALLBACKIMPL_H
```
> callbackimpl.cpp
``` C++
#include "callbackimpl.h"
#include "SSX_SDK.h"
 
using namespace std;
 
void CallBackImpl::queryOrder(stringorderId, string carNumber) {
    cout << "client interface implqueryOrder() " << endl;
    const string _orderId=orderId;
    const string_parkCode="201808150001";
    const string _carNumber=carNumber;
    const string inTime="20180831123056";
    const string inChannel="0001";
    const string outTime="20180831133056";
    const string outChannel="0001";
    const long duration=3600;
    const int orderAmount=300;
 
    cout << "CallBackImpl -->_carNumber() -->" << _carNumber << endl;
 
    string responseData =SSXSDK::pushOrder(_orderId, _carNumber, inTime,inChannel, outTime,outChannel, duration,orderAmount);
 
    cout << "CallBackImpl -->queryOrder() -->" << responseData << endl;
}
```
>输出结果：{"code":"0000","msg":"获取成功!"}


#### 2.2.2、扫码入场
##### 2.2.2.1、简述
用户在不使用嗖嗖行小程序的情况下，车辆在入场时扫描入场二维码进行入场。针对无牌车辆停车场景。

##### 2.2.2.2、调用方法
需要车场的计费系统实现接口`CommandInterface`中的`scanQrEntry(string parkCode,stringsysCode,string channel,string carNumber)`方法,SDK接收到指令会调用该方法，车场自行判断入口是否有车辆等待入场、放行入场、推送入场数据（调用2.1.2）。

##### 2.2.2.3、传入参数
>SDK回调传参

参数|必选|类型|说明
---|---|---|---
parkCode|true|string|车场流水号，嗖嗖行提供
sysCode|true|string|计费系统编号
carNumber|true|string|车牌号

##### 2.2.2.4、示例
> callbackimpl.h
``` C++
#include <iostream>
#include "CommandInterface.h"
 
using namespace std;
using namespace ssx_sdk;
 
#ifndef CALLBACKIMPL_H
#define CALLBACKIMPL_H
 
class CallBackImpl:public CommandInterface{
public:
    CallBackImpl(){}
    //预支付场景 获取订单数据
    void queryOrder(string orderId, string carNumber);
    //扫码支付获取最新要出场且在出场闸口的车辆订单数据
    void scanQrCodePay(string parkCode,string sysCode,string channel,string scanNumber,string orderId,string carNumber,int tempCar);
    //扫码入场
    voidscanQrEntry(string parkCode,string sysCode,string channel,string carNumber);
    //支付结果通知
    void noticeOfPaymentResult(string orderId, string carNumber,int payStatus,int orderAmount,int duration,string inTime,string outTime,string payTime);
};
#endif // CALLBACKIMPL_H
```
> callbackimpl.cpp
``` C++
#include "callbackimpl.h"
#include "SSX_SDK.h"
 
using namespace std;
 
voidCallBackImpl::scanQrEntry(string parkCode,string sysCode,string channel,string carNumber){
    cout << "client interface implscanQrEntry() " << endl;
    cout << "client interface implscanQrEntry()--> " << parkCode << endl;
    cout << "client interface implscanQrEntry()--> " << sysCode << endl;
    cout << "client interface implscanQrEntry()--> " << channel << endl;
    cout << "client interface implscanQrEntry()--> " << carNumber << endl;
    //车场自行判断数据入口是否有车辆等待入场 放行入场推送（调用2.1.2）入场数据
}
```
>输出结果：{"code":"0000","msg":"获取成功!"}

#### 2.2.3、扫码支付
##### 2.2.3.1、简述
##### 2.2.3.2、调用方法
##### 2.2.3.3、传入参数
##### 2.2.3.4、返回值
##### 2.2.3.5、示例


#### 2.2.4、支付结果通知
##### 2.2.4.1、简述
##### 2.2.4.2、调用方法
##### 2.2.4.3、传入参数
##### 2.2.4.4、返回值
##### 2.2.4.5、示例

## 附录:通知实现方式