#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include "opencv2/videoio.hpp"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:
    void processFrameAndUpdateGUI();

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    cv::VideoCapture videoCapture;

    QTimer* timer;

    QImage convertOpenCVMatToQtQImage(cv::Mat mat);

    void exitProgram();
};

#endif // MAINWINDOW_H
