TEMPLATE = app
QT =
CONFIG += c++11 console
CONFIG -= app_bundle

QMAKE_CXXFLAGS += -pthread
QMAKE_LFLAGS += -pthread

SOURCES += \
        base/dataCenter.cpp \
        base/json/json_reader.cpp \
        base/json/json_value.cpp \
        base/json/json_writer.cpp \
        base/md5/md5.cpp \
        base/mmap/mmapWriter.cpp \
        core/_c_deviceSearch.cpp \
        core/_c_disasterRecovery.cpp \
        core/_c_udpService.cpp \
        core/_c_watchDog.cpp \
        core/fileUpload/_c_fileUploadRecv.cpp \
        core/fileUpload/_c_fileUploadSend.cpp \
        core/fileUpload/fileUpload.cpp \
        core/interface.cpp \
        main.cpp

HEADERS += \
    base/BlockQueue.h \
    base/baseInc.h \
    base/dataCenter.h \
    base/json/autolink.h \
    base/json/config.h \
    base/json/features.h \
    base/json/forwards.h \
    base/json/json.h \
    base/json/json_batchallocator.h \
    base/json/reader.h \
    base/json/value.h \
    base/json/writer.h \
    base/md5/md5.h \
    base/mmap/mmapReader.h \
    base/mmap/mmapWriter.h \
    core/_c_deviceSearch.h \
    core/_c_disasterRecovery.h \
    core/_c_udpService.h \
    core/_c_watchDog.h \
    core/fileUpload/_c_fileUploadRecv.h \
    core/fileUpload/_c_fileUploadSend.h \
    core/fileUpload/fileUpload.h \
    core/interface.h \
