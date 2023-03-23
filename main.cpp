#include "mainwindow.h"
#include <QApplication>

#include "single_model.h"
#include <io.h>
#include <iostream>
#include <memory>

int main(int argc,char* argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();

    //std::shared_ptr<SingleModel> single_model;
    //single_model = std::make_shared<SingleModel>();
    //single_model->set_modal("face");
    //single_model->set_model_name("resources\\model\\resnet50_face.pt");
    //return 0;
}
