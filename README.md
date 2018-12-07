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

##### 2.1.1.3、返回值
参数|类型|说明
---|---|---
code|string|返回码 0000:成功 其他表示失败
msg|string|返回信息描述


### 2.1、数据通知

## 附录:通知实现方式