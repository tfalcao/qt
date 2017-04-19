TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

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
        -lopencv_highgui
}

SOURCES += main.cpp
