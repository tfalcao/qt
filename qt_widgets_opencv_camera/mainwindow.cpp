#include "mainwindow.h"
#include "ui_mainwindow.h"

#include<QFileDialog>
#include<QtCore>
#include<QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    videoCapture.open(0);

    if(videoCapture.isOpened() == false) {
        QMessageBox::information(this, "", "error: capWebcam not accessed successfully \n\n exiting program\n");
        exitProgram();
        return;
    }

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(processFrameAndUpdateGUI()));
    // cycle every 20 msec (50x per sec)
    timer->start(20);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::exitProgram() {
    if(timer->isActive()) timer->stop();
    QApplication::quit();
}

void MainWindow::processFrameAndUpdateGUI() {
    cv::Mat imgOriginal;
    // get next frame
    bool blnFrameReadSuccessfully = videoCapture.read(imgOriginal);

    if (!blnFrameReadSuccessfully || imgOriginal.empty()) {
        QMessageBox::information(this, "", "unable to read from webcam \n\n exiting program\n");
        exitProgram();
        return;
    }

    // grayscale
    cv::Mat imgGrayscale;
    cv::cvtColor(imgOriginal, imgGrayscale, CV_BGR2GRAY);

    // blur
    cv::Mat imgBlurred;
    cv::GaussianBlur(imgGrayscale, imgBlurred, cv::Size(5, 5), 1.8);

    // canny
    cv::Mat imgCanny;
    cv::Canny(imgBlurred, imgCanny, 50, 100);

    QImage qimgOriginal = convertOpenCVMatToQtQImage(imgOriginal);
    QImage qimgCanny = convertOpenCVMatToQtQImage(imgCanny);

    ui->lblOriginal->setPixmap(QPixmap::fromImage(qimgOriginal));
    ui->lblCanny->setPixmap(QPixmap::fromImage(qimgCanny));
}

QImage MainWindow::convertOpenCVMatToQtQImage(cv::Mat mat) {
    if(mat.channels() == 1) {
        return QImage((uchar*)mat.data, mat.cols, mat.rows, mat.step, QImage::Format_Indexed8);
    } else if(mat.channels() == 3) {
        cv::cvtColor(mat, mat, CV_BGR2RGB);
        return QImage((uchar*)mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
    } else {
        qDebug() << "in convertOpenCVMatToQtQImage, image was not 1 channel or 3 channel, should never get here";
    }

    // blank QImage
    return QImage();
}
