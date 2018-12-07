#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    static void noticeCallBack(const char* strJsonData);

private slots:
    //接口类型选择
    void on_typeComboBox_activated(int index);
    //文件xua选择
    void on_fileButton_clicked();
    //提交点击事件
    void on_submitButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
