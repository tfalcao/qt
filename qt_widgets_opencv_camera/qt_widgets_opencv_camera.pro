QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qt_widgets_opencv_hello
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

win32 {
    OPENCV_INCLUDE_DIR = C:\\dev\\opencv\\build\\include
    OPENCV_LIB_DIR = C:\\dev\\opencv\\mybuild\\lib\\Debug

    INCLUDEPATH += $${OPENCV_INCLUDE_DIR}

    LIBS += -L$${OPENCV_LIB_DIR} \
        -lopencv_imgcodecs320d \
        -lopencv_imgproc320d \
        -lopencv_ml320d \
        -lopencv_objdetect320d \
        -lopencv_photo320d \
        -lopencv_shape320d \
        -lopencv_stitching320d \
        -lopencv_superres320d \
        -lopencv_ts320d \
        -lopencv_video320d \
        -lopencv_videoio320d \
        -lopencv_videostab320d \
        -lopencv_calib3d320d \
        -lopencv_core320d \
        -lopencv_features2d320d \
        -lopencv_flann320d \
        -lopencv_highgui320d
}

unix {
    OPENCV_INCLUDE_DIR = /usr/local/include
    OPENCV_LIB_DIR = /usr/local/lib

    INCLUDEPATH += $${OPENCV_INCLUDE_DIR}
    LIBS += -L$${OPENCV_LIB_DIR} \
        -lopencv_core \
        -lopencv_imgcodecs \
        -lopencv_imgproc \
        -lopencv_highgui \
        -lopencv_videoio
}
