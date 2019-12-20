QT       += core gui sql printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addclients.cpp \
    addproducts.cpp \
    clientswindow.cpp \
    companywindow.cpp \
    editclients.cpp \
    editproducts.cpp \
    main.cpp \
    entrywindow.cpp \
    mainwindow.cpp \
    productswindow.cpp \
    salesappenditem.cpp \
    salescreate.cpp \
    salesdetail.cpp \
    salesview.cpp \
    saleswindow.cpp \
    sql.cpp \
    storagewindow.cpp \
    supplieswindow.cpp

HEADERS += \
    addclients.h \
    addproducts.h \
    clientswindow.h \
    companywindow.h \
    editclients.h \
    editproducts.h \
    entrywindow.h \
    mainwindow.h \
    productswindow.h \
    salesappenditem.h \
    salescreate.h \
    salesdetail.h \
    salesview.h \
    saleswindow.h \
    sql.h \
    storagewindow.h \
    supplieswindow.h

FORMS += \
    addclients.ui \
    addproducts.ui \
    clientswindow.ui \
    companywindow.ui \
    editclients.ui \
    editproducts.ui \
    entrywindow.ui \
    mainwindow.ui \
    productswindow.ui \
    salesappenditem.ui \
    salescreate.ui \
    salesdetail.ui \
    salesview.ui \
    saleswindow.ui \
    storagewindow.ui \
    supplieswindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
