#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QFileInfo>
#include <QMessageBox>
#include <QFileDialog>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QVariantMap>

#include <QTextBlock>

#include "SSX_SDK.h"
#include "callbackimpl.h"
#include "callbackservice.h"

using namespace std;
using namespace ssx_sdk;

//参数定义
struct Parameter
{
    int type;
    string requestData;
    string responseData;
    string imagePath;
    Parameter() {}
};

Parameter param;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::noticeCallBack(const char* strJsonData){
    cout << "callback function :" << strJsonData << endl;
    CallBackService::handleNotice(strJsonData);
}

//接口类型选择
void MainWindow::on_typeComboBox_activated(int index)
{
    param.type = index;

    if(index == 0){//初始化
        ui->requestPlainTextEdit->setPlainText("{\n\"manufacturer\":\"201808290001\",\n\"parkCode\":\"201808150001\",\n\"sysCode\":\"0001\",\n\"channelNumber\":\"A4\",\n\"key\":\"201822134513165313\",\n\"ssxUrl\":\"http://192.168.1.11:8080/miniprogram-web\"\n}");
    }else if(index == 1){//入场
        ui->requestPlainTextEdit->setPlainText("{\n\"carNumber\":\"陕A88888\",\n\"inTime\":\"20180831123056\",\n\"orderId\":\"201808310001\"\n}");
    }else if(index == 2){//离场前
        ui->requestPlainTextEdit->setPlainText("{\n\"carNumber\":\"陕A88888\",\n\"outTime\":\"20180831133056\",\n\"orderId\":\"201808310001\",\n\"orderAmount\":300,\n\"duration\":3600,\n\"scanNumber\":\"25de84afecb04c3a87670f4a7005ec49\",\n\"outType\":2\n}");
    }else if(index == 3){//离场后
        ui->requestPlainTextEdit->setPlainText("{\n\"carNumber\":\"陕A88888\",\n\"orderId\":\"201808310001\",\n\"finishTime\":\"20180831133156\"\n}");
    }else if(index == 4){//订单查询
        ui->requestPlainTextEdit->setPlainText("{\n\"carNumber\":\"陕A88888\",\n\"orderId\":\"201808310001\"\n}");
    }else if(index == 5){//附件上传
        ui->requestPlainTextEdit->setPlainText("{\n\"orderId\":\"201808310001\",\n\"attType\":\"entry\"\n}");
    }else if(index == 6){//订单补缴
        ui->requestPlainTextEdit->setPlainText("{\n\"carNumber\":\"陕A88888\",\n\"startTime\":\"20180831133056\",\n\"endTime\":\"20180831143056\",\n\"orderId\":\"201808310001\",\n\"orderAmount\":300,\n\"duration\":3600\n}");
    }else if(index == 7){//免费车辆
        ui->requestPlainTextEdit->setPlainText("{\n\"carNumber\":\"陕A88888\",\n\"startTime\":\"20180831133056\",\n\"endTime\":\"20180830143056\",\n\"remarks\":\"baoyueche\",\n\"delFlag\":0\n}");
    }
    cout << "you select interface is :" << index << endl;
}

//文件xua选择
void MainWindow::on_fileButton_clicked(){
    QFileInfo fi;
    QString filename=QFileDialog::getOpenFileName(this,tr("选择图像"),"",tr("Images (*.png *.bmp *.jpg)"));
    if(filename.isEmpty())
    {
        return;
    }
    else
    {
        QImage img;
        if(!(img.load(filename))) //加载图像
        {
            QMessageBox::information(this, tr("打开图像失败"),tr("打开图像失败!"));
            return;
        }
        ui->imgLabel->setPixmap(QPixmap::fromImage(img.scaled(ui->imgLabel->size())));
        param.imagePath = filename.toStdString();
    }
    fi = QFileInfo(filename);

    cout << "image filename is :" << filename.toStdString() << endl;
    cout << "image path is :" << fi.absolutePath().toStdString() << endl;
}
//提交点击事件
void MainWindow::on_submitButton_clicked(){
    cout << " ================= start request =================== " << endl;

    string manufacturer;
    string parkCode;
    string sysCode;
    string channelNumber;
    string key;
    string ssxUrl;
    string carNumber;
    string inTime;
    string orderId;
    int orderAmount;
    string outTime;
    string finishTime;
    string attType;
    long duration;

    bool delFlag = false;
    string startTime;
    string endTime;
    string remarks;

    int entryType;
    int outType;
    string scanNumber;

    //获取请求参数json格式数据  requestPlainTextEdit
    QString requestData = ui->requestPlainTextEdit->document()->toPlainText();
    QByteArray cdata = requestData.toLocal8Bit();
    string cstr = string(cdata);

    cout << " request data:  "<< cstr << endl;


    QJsonParseError error;
    //param.requestData.toUtf8() requestData.toUtf8()
    QJsonDocument document = QJsonDocument::fromJson(requestData.toUtf8(), &error);
    if(QJsonParseError::NoError == error.error)
    {   //map
        QVariantMap map = document.toVariant().toMap();
        if(map.contains("carNumber")||map.contains("parkCode") || map.contains("inTime") || map.contains("orderId") || map.contains("outTime") || map.contains("duration")
                || map.contains("orderAmount") || map.contains("sysCode") || map.contains("finishTime") || map.contains("manufacturer")  || map.contains("channelNumber")
                || map.contains("attType") || map.contains("delFlag") || map.contains("startTime") || map.contains("endTime") || map.contains("remarks")
                || map.contains("entryType") || map.contains("outType") || map.contains("scanNumber")
                ){


            manufacturer = map["manufacturer"].toString().toStdString();
            parkCode = map["parkCode"].toString().toStdString();
            carNumber = map["carNumber"].toString().toStdString();
            channelNumber = map["channelNumber"].toString().toStdString();

            QString str = map["carNumber"].toString();
            QByteArray cdata = str.toLocal8Bit();
            carNumber = string(cdata);


            sysCode = map["sysCode"].toString().toStdString();
            key = map["key"].toString().toStdString();
            ssxUrl = map["ssxUrl"].toString().toStdString();

            inTime = map["inTime"].toString().toStdString();
            orderId = map["orderId"].toString().toStdString();
            outTime = map["outTime"].toString().toStdString();
            duration = map["duration"].toLongLong();
            orderAmount = map["orderAmount"].toInt();
            finishTime = map["finishTime"].toString().toStdString();
            attType = map["attType"].toString().toStdString();

            delFlag = map["delFlag"].toBool();
            startTime = map["startTime"].toString().toStdString();
            endTime = map["endTime"].toString().toStdString();
            remarks = map["remarks"].toString().toStdString();

            entryType = map["entryType"].toInt();
            outType = map["outType"].toInt();
            scanNumber = map["scanNumber"].toString().toStdString();
        }
    }else{
        std::cout << " json addrqwqw " << std::endl;
    }

    int type = param.type;
    string responseData;

    CallBackImpl *cmd = new CallBackImpl();
//    SSXSDK::setCallBackFun((CallBackFun)noticeCallBack);
    SSXSDK::setCommandInterface(cmd);

    if(type == 0){
        cout << " request init() " << endl;
        responseData = SSXSDK::init(manufacturer,parkCode,sysCode,channelNumber,key ,ssxUrl);
    }else if(type == 1){
        string filePath = param.imagePath;
        responseData = SSXSDK::entry(carNumber,inTime,orderId,filePath,entryType,scanNumber);
        cout << " request in() " << endl;
    }else if(type == 2){
        cout << " carNumber is :  " << carNumber << endl;
        string filePath = param.imagePath;
        responseData = SSXSDK::leave(carNumber,outTime,orderId,duration,orderAmount,filePath,outType,scanNumber);
        cout << " request out() " << endl;
    }else if(type == 3){
        responseData = SSXSDK::finish(orderId,carNumber,finishTime);
        cout << " request finish() " << endl;
    }else if(type == 4){
        responseData = SSXSDK::queryOrder(orderId);
        cout << " request orderQuery() " << endl;
    }else if(type == 5){
        string filePath = param.imagePath;
        if (filePath.empty() || strcmp("", filePath.c_str()) == 0) {
            //_log->printLog("scanningOrder() scanNumner is empty!");
            responseData = "{\"code\":\"1001\",\"msg\":\"请选择车辆附件!\"}";
        }else{
            responseData = SSXSDK::uploadFile(orderId,filePath,attType);
        }
        cout << " request orderQuery() " << endl;
    }else if(type == 6){//补缴
        responseData = SSXSDK::suppOrder(carNumber, startTime, endTime,orderId,duration,orderAmount);
        cout << " request suppOrder() " << endl;
    }else if(type == 7){//免费车辆
        cout << " request freeCar()  carNumber " << carNumber << endl;
        cout << " request freeCar()  startTime " << startTime << endl;
        cout << " request freeCar()  endTime " << endTime << endl;
        cout << " request freeCar()  remarks " << remarks << endl;
        cout << " request freeCar()  delFlag " << delFlag << endl;
        responseData = SSXSDK::freeCar(carNumber,startTime,endTime,remarks,delFlag);
        cout << " request freeCar() " << endl;
    }

    cout << " responseData : " << responseData << endl;
    //responsePlainTextEdit
    QString respon = QString::fromLocal8Bit(responseData.c_str());
    ui->responsePlainTextEdit->setPlainText(respon.toUtf8());


    cout << " ================= end request =================== " << endl;
}
