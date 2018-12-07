#ifndef CALLBACKSERVICE_H
#define CALLBACKSERVICE_H

class CallBackService{
public:
    CallBackService();
    ~CallBackService();

    /**
     * @brief handleNotice
     * @param strJsonData
     * 处理通知相关的方法
     */
    static void handleNotice(const char * strJsonData);

};
#endif // CALLBACKSERVICE_H
