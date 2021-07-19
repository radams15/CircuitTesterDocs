/** @file main.cpp
 * This is the main entry point of the program.
 */
#include <iostream>


#include <QApplication>

#include "UI/MainWindow.h"


/** @brief Main GUI method.
 * This method runs the QT GUI code and
 * returns the status code of it.
 */
int guiMain(int argc, char** argv){
    Q_INIT_RESOURCE(resources);

    QApplication a(argc, argv);
    MainWindow w;
    w.setGeometry(100, 100, 800, 500);
    w.show();
    return QApplication::exec();
}

/** @brief Main method.
 * This is the main program entry point.
 */
int main(int argc, char** argv){
    return guiMain(argc, argv);
}
