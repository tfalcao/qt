#include "mainwindow.h"
#include "ui_mainwindow.h"

#include<QFileDialog>
#include<QtCore>

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

QImage MainWindow::ConvertOpenCVMatToQtQImage(cv::Mat mat) {
    if(mat.channels() == 1) { // if grayscale
        return QImage((uchar*)mat.data, mat.cols, mat.rows, mat.step, QImage::Format_Indexed8);
    } else if(mat.channels() == 3) { // if 3 channel color image
        cv::cvtColor(mat, mat, CV_BGR2RGB); // invert BGR to RGB
        return QImage((uchar*)mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
    } else {
        qDebug() << "in ConvertOpenCVMatToQtQImage, image was not 1 channel or 3 channel, should never get here";
    }

    return QImage(); // blank QImage
}

void MainWindow::on_btnOpenFile_clicked()
{
    QString strFileName = QFileDialog::getOpenFileName();

    if (strFileName.isEmpty()) {
        ui->lblChosenFile->setText("file not chosen");
        return;
    }

                 // intermediate blured image
    cv::Mat imgCanny;               // Canny edge image

    cv::Mat imgOriginal = cv::imread(strFileName.toStdString());        // open image

    if (imgOriginal.empty()) {									// if unable to open image
        ui->lblChosenFile->setText("error: image not read from file");      // update lable with error message
        return;
    }
    // if we get to this point image was opened successfully
    ui->lblChosenFile->setText(strFileName);                // update label with file name

    cv::Mat imgGrayscale;
    // convert to grayscale
    cv::cvtColor(imgOriginal, imgGrayscale, CV_BGR2GRAY);
    cv::Mat imgBlurred;
    // blur
    cv::GaussianBlur(imgGrayscale, imgBlurred, cv::Size(5, 5), 1.5);
    // canny
    cv::Canny(imgBlurred, imgCanny, 100, 200);

    QImage qimgOriginal = ConvertOpenCVMatToQtQImage(imgOriginal);
    QImage qimgCanny = ConvertOpenCVMatToQtQImage(imgCanny);

    ui->lblOriginal->setPixmap(QPixmap::fromImage(qimgOriginal));
    ui->lblCanny->setPixmap(QPixmap::fromImage(qimgCanny));
}
