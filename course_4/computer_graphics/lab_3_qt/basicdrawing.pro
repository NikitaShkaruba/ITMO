QT += widgets

HEADERS       = renderarea.h \
                window.h
SOURCES       = main.cpp \
                renderarea.cpp \
                window.cpp
RESOURCES     = basicdrawing.qrc

# install
target.path = /Users/sigma/code/ITMO/course_4/computer_graphics/lab_3_qt
INSTALLS += target
