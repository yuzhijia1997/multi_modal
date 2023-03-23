#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QButtonGroup>

#include "single_model.h"
#include "fusion_model.h"
#include "score_model.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void initialize();

    void init_test_views();
    void init_gallery_views();

    void set_model(int nId);

private slots:
    void on_pushButtond_face_clicked();

    void on_pushButtond_iris_clicked();

    void on_pushButtond_fp_clicked();

    void on_pushButtond_gallery_clicked();

    void on_pushButtond_res_clicked();

    void on_textBrowser_textChanged();

    void slot_btnGroupToggled(QAbstractButton* button, bool flag);

private:
    Ui::MainWindow *ui;
    QButtonGroup *pButtonGroup;
    QString face_path;
    QString iris_path;
    QString fingerprint_path;
    QString gallery_path;

    std::shared_ptr<SingleModel> single_model;
    std::shared_ptr<FusionModel> fusion_model;
    std::shared_ptr<ScoreModel> score_model;
};
#endif // MAINWINDOW_H
