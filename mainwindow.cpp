#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , pButtonGroup(new QButtonGroup)
{
    ui->setupUi(this);
    pButtonGroup->setExclusive(true);
    initialize();
}

MainWindow::~MainWindow()
{
    delete ui,pButtonGroup;
}

void MainWindow::initialize()
{
    init_test_views();
    init_gallery_views();

    single_model = std::make_shared<SingleModel>();
    fusion_model = std::make_shared<FusionModel>();
    score_model = std::make_shared<ScoreModel>();

    pButtonGroup->addButton(ui->radioButton_face, 0);
    pButtonGroup->addButton(ui->radioButton_iris, 1);
    pButtonGroup->addButton(ui->radioButton_fp, 2);
    pButtonGroup->addButton(ui->radioButton_pixel, 3);
    pButtonGroup->addButton(ui->radioButton_feature, 4);
    pButtonGroup->addButton(ui->radioButton_score, 5);

    connect(pButtonGroup, &QButtonGroup::buttonToggled, this, &::MainWindow::slot_btnGroupToggled);

    int nId = pButtonGroup->checkedId();
    set_model(nId);
}

void MainWindow::init_test_views()
{
    QGraphicsScene* scene_face = new QGraphicsScene;
    scene_face->addText("人脸待选择");
    ui->graphicsView_face->setScene(scene_face);
    QGraphicsScene* scene_iris = new QGraphicsScene;
    scene_iris->addText("虹膜待选择");
    ui->graphicsView_iris->setScene(scene_iris);
    QGraphicsScene* scene_fp = new QGraphicsScene;
    scene_fp->addText("指纹待选择");
    ui->graphicsView_fp->setScene(scene_fp);
}

void MainWindow::init_gallery_views()
{
    QGraphicsScene* scene_face_g = new QGraphicsScene;
    scene_face_g->addText("人脸匹配结果");
    ui->graphicsView_face_g->setScene(scene_face_g);
    QGraphicsScene* scene_iris_g = new QGraphicsScene;
    scene_iris_g->addText("虹膜匹配结果");
    ui->graphicsView_iris_g->setScene(scene_iris_g);
    QGraphicsScene* scene_fp_g = new QGraphicsScene;
    scene_fp_g->addText("指纹匹配结果");
    ui->graphicsView_fp_g->setScene(scene_fp_g);
}

void MainWindow::set_model(int nId)
{
    switch (nId)
    {
    case 0:
        if (single_model->get_modal() != "face") {
            single_model->set_modal("face");
            single_model->set_model_name("resources\\model\\resnet50_face.pt");
        }
        ui->textBrowser->insertPlainText("加载人脸模型\n");
        if (gallery_path != "") {
            single_model->set_gallery_dir(gallery_path.toStdString());
        }
        break;
    case 1:
        if (single_model->get_modal() != "iris") {
            single_model->set_modal("iris");
            single_model->set_model_name("resources\\model\\resnet50_iris.pt");
        }
        ui->textBrowser->insertPlainText("加载虹膜模型\n");
        if (gallery_path != "") {
            single_model->set_gallery_dir(gallery_path.toStdString());
        }
        break;
    case 2:
        if (single_model->get_modal() != "fingerprint") {
            single_model->set_modal("fingerprint");
            single_model->set_model_name("resources\\model\\resnet50_fingerprint.pt");
        }
        ui->textBrowser->insertPlainText("加载指纹模型\n");
        if (gallery_path != "") {
            single_model->set_gallery_dir(gallery_path.toStdString());
        }
        break;
    case 3:
        if (fusion_model->get_mode() != "pixel") {
            fusion_model->set_mode("pixel");
            fusion_model->set_model_name("resources\\model\\resnet50_pixel_add.pt");
        }
        ui->textBrowser->insertPlainText("加载像素融合模型\n");
        if (gallery_path != "") {
            fusion_model->set_gallery_dir(gallery_path.toStdString());
        }
        break;
    case 4:
        if (fusion_model->get_mode() != "feature") {
            fusion_model->set_mode("feature");
            fusion_model->set_model_name("resources\\model\\resnet50_feature_add.pt");
        }
        ui->textBrowser->insertPlainText("加载特征融合模型\n");
        if (gallery_path != "") {
            fusion_model->set_gallery_dir(gallery_path.toStdString());
        }
        break;
    case 5:
        score_model->set_model_and_modals({ "resources\\model\\resnet50_face.pt" ,
            "resources\\model\\resnet50_iris.pt" ,"resources\\model\\resnet50_fingerprint.pt" },
            { "face","iris","fingerprint" });
        ui->textBrowser->insertPlainText("加载分数融合模型\n");
        if (gallery_path != "") {
            score_model->set_gallery_dir(gallery_path.toStdString());
        }
        break;
    default:
        qDebug() << nId;
        break;
    }
}

void MainWindow::on_pushButtond_face_clicked()
{
    auto image_file = QFileDialog::getOpenFileName(this, tr("选择图片"), ".", tr("Image Files(*.jpg *.png *.bmp)"));
    QImage* img = new QImage;
    if(!(img->load(image_file))) //加载图像
    {
       QMessageBox::information(this, tr("打开图像失败"), tr("打开图像失败!"));
       delete img;
       return;
    }
    face_path = image_file;
    QGraphicsScene *scene = new QGraphicsScene;
    scene->addPixmap(QPixmap(face_path).scaled(0.95*ui->graphicsView_face->size()));
    ui->graphicsView_face->setScene(scene);
    const QString msg = "人脸图片 " + face_path + " 加载成功\n";
    ui->textBrowser->insertPlainText(msg);
    init_gallery_views();
}


void MainWindow::on_pushButtond_iris_clicked()
{
    auto image_file = QFileDialog::getOpenFileName(this, tr("选择图片"), ".", tr("Image Files(*.jpg *.png *.bmp)"));
    QImage* img = new QImage;
    if(!(img->load(image_file))) //加载图像
    {
       QMessageBox::information(this, tr("打开图像失败"), tr("打开图像失败!"));
       delete img;
       return;
    }
    iris_path = image_file;
    QGraphicsScene *scene = new QGraphicsScene;
    scene->addPixmap(QPixmap(iris_path).scaled(0.95*ui->graphicsView_iris->size()));
    ui->graphicsView_iris->setScene(scene);
    const QString msg = "虹膜图片 " + iris_path + " 加载成功\n";
    ui->textBrowser->insertPlainText(msg);
    init_gallery_views();
}


void MainWindow::on_pushButtond_fp_clicked()
{
    auto image_file = QFileDialog::getOpenFileName(this, tr("选择图片"), ".", tr("Image Files(*.jpg *.png *.bmp)"));
    QImage* img = new QImage;
    if(!(img->load(image_file))) //加载图像
    {
       QMessageBox::information(this, tr("打开图像失败"), tr("打开图像失败!"));
       delete img;
       return;
    }
    fingerprint_path = image_file;
    QGraphicsScene *scene = new QGraphicsScene;
    scene->addPixmap(QPixmap(fingerprint_path).scaled(0.95*ui->graphicsView_fp->size()));
    ui->graphicsView_fp->setScene(scene);
    const QString msg = "指纹图片 " + fingerprint_path + " 加载成功\n";
    ui->textBrowser->insertPlainText(msg);
    init_gallery_views();
}


void MainWindow::on_pushButtond_gallery_clicked()
{
    auto path = QFileDialog::getExistingDirectory(this, tr("选择文件夹"), ".");
    int nId = pButtonGroup->checkedId();
    switch (nId)
    {
    case 0:
    case 1:
    case 2:
        single_model->set_gallery_dir(path.toStdString());
        if (!single_model->IsExistGallery()) {
            const QString msg = "底库 " + path + " 不存在\n";
            ui->textBrowser->insertPlainText(msg);
        }
        else 
        {
            gallery_path = path;
            const QString msg = "底库 " + gallery_path + " 加载成功\n";
            ui->textBrowser->insertPlainText(msg);
        }
        break;
    case 3:
    case 4:
        fusion_model->set_gallery_dir(path.toStdString());
        if (!fusion_model->IsExistGallery()) {
            const QString msg = "底库 " + path + " 不存在\n";
            ui->textBrowser->insertPlainText(msg);
        }
        else
        {
            gallery_path = path;
            const QString msg = "底库 " + gallery_path + " 加载成功\n";
            ui->textBrowser->insertPlainText(msg);
        }
        break;
    case 5:
        score_model->set_gallery_dir(path.toStdString());
        if (!score_model->IsExistGallery()) {
            const QString msg = "底库 " + path + " 不存在\n";
            ui->textBrowser->insertPlainText(msg);
        }
        else {
            gallery_path = path;
            const QString msg = "底库 " + gallery_path + " 加载成功\n";
            ui->textBrowser->insertPlainText(msg);
        }
        break;
    default:
        break;
    }

}

void MainWindow::on_pushButtond_res_clicked()
{
    int nId = pButtonGroup->checkedId();
    switch (nId)
    {
    case 0:
        if (!face_path.size())
        {
            ui->textBrowser->insertPlainText("人脸图片未选择\n");
        }
        else if (!single_model->IsExistGallery()) {
            const QString msg = "底库 " + gallery_path + " 不存在\n";
            ui->textBrowser->insertPlainText(msg);
        }
        else
        {
            auto results = single_model->GetMatchResult(face_path.toStdString());
            std::string msg = "最优匹配人员序号：" + results[0][0] + "\n";
            ui->textBrowser->insertPlainText(QString::fromStdString(msg));
            QGraphicsScene* scene = new QGraphicsScene;
            scene->addPixmap(QPixmap(QString::fromStdString(results[0][1])).scaled(0.95 * ui->graphicsView_face_g->size()));
            ui->graphicsView_face_g->setScene(scene);
        }
        break;
    case 1:
        if (!iris_path.size())
        {
            ui->textBrowser->insertPlainText("虹膜图片未选择\n");
        }
        else if (!single_model->IsExistGallery()) {
            const QString msg = "底库 " + gallery_path + " 不存在\n";
            ui->textBrowser->insertPlainText(msg);
        }
        else
        {
            auto results = single_model->GetMatchResult(iris_path.toStdString());
            std::string msg = "最优匹配人员序号：" + results[0][0] + "\n";
            ui->textBrowser->insertPlainText(QString::fromStdString(msg));
            QGraphicsScene* scene = new QGraphicsScene;
            scene->addPixmap(QPixmap(QString::fromStdString(results[0][1])).scaled(0.95 * ui->graphicsView_iris_g->size()));
            ui->graphicsView_iris_g->setScene(scene);
        }
        break;
    case 2:
        if (!fingerprint_path.size())
        {
            ui->textBrowser->insertPlainText("指纹图片未选择\n");
        }
        else if (!single_model->IsExistGallery()) {
            const QString msg = "底库 " + gallery_path + " 不存在\n";
            ui->textBrowser->insertPlainText(msg);
        }
        else
        {
            auto results = single_model->GetMatchResult(fingerprint_path.toStdString());
            std::string msg = "最优匹配人员序号：" + results[0][0] + "\n";
            ui->textBrowser->insertPlainText(QString::fromStdString(msg));
            QGraphicsScene* scene = new QGraphicsScene;
            scene->addPixmap(QPixmap(QString::fromStdString(results[0][1])).scaled(0.95 * ui->graphicsView_fp_g->size()));
            ui->graphicsView_fp_g->setScene(scene);
        }
        break;
    case 3:
    case 4:
        if (!face_path.size())
        {
            ui->textBrowser->insertPlainText("人脸图片未选择\n");
        }
        else if (!iris_path.size())
        {
            ui->textBrowser->insertPlainText("虹膜图片未选择\n");
        }
        else if (!fingerprint_path.size())
        {
            ui->textBrowser->insertPlainText("指纹图片未选择\n");
        }
        else if (!fusion_model->IsExistGallery()) {
            const QString msg = "底库 " + gallery_path + " 不存在\n";
            ui->textBrowser->insertPlainText(msg);
        }
        else
        {
            const std::vector<std::string> image_paths({ face_path.toStdString(),iris_path.toStdString(),fingerprint_path.toStdString() });
            auto results = fusion_model->GetMatchResult(image_paths);
            std::string msg = "最优匹配人员序号：" + results[0][0] + "\n";
            ui->textBrowser->insertPlainText(QString::fromStdString(msg));
            QGraphicsScene* scene1 = new QGraphicsScene;
            scene1->addPixmap(QPixmap(QString::fromStdString(results[0][1])).scaled(0.95 * ui->graphicsView_face_g->size()));
            ui->graphicsView_face_g->setScene(scene1);
            QGraphicsScene* scene2 = new QGraphicsScene;
            scene2->addPixmap(QPixmap(QString::fromStdString(results[0][2])).scaled(0.95 * ui->graphicsView_iris_g->size()));
            ui->graphicsView_iris_g->setScene(scene2);
            QGraphicsScene* scene3 = new QGraphicsScene;
            scene3->addPixmap(QPixmap(QString::fromStdString(results[0][3])).scaled(0.95 * ui->graphicsView_fp_g->size()));
            ui->graphicsView_fp_g->setScene(scene3);
        }
        break;
    case 5:
        if (!face_path.size())
        {
            ui->textBrowser->insertPlainText("人脸图片未选择\n");
        }
        else if (!iris_path.size())
        {
            ui->textBrowser->insertPlainText("虹膜图片未选择\n");
        }
        else if (!fingerprint_path.size())
        {
            ui->textBrowser->insertPlainText("指纹图片未选择\n");
        }
        else if (!score_model->IsExistGallery()) {
            const QString msg = "底库 " + gallery_path + " 不存在\n";
            ui->textBrowser->insertPlainText(msg);
        }
        else
        {
            const std::vector<std::string> image_paths({ face_path.toStdString(),iris_path.toStdString(),fingerprint_path.toStdString() });
            auto results = score_model->GetMatchResult(image_paths);
            std::string msg = "最优匹配人员序号：" + results[0][0] + "\n";
            ui->textBrowser->insertPlainText(QString::fromStdString(msg));
            QGraphicsScene* scene1 = new QGraphicsScene;
            scene1->addPixmap(QPixmap(QString::fromStdString(results[0][1])).scaled(0.95 * ui->graphicsView_face_g->size()));
            ui->graphicsView_face_g->setScene(scene1);
            QGraphicsScene* scene2 = new QGraphicsScene;
            scene2->addPixmap(QPixmap(QString::fromStdString(results[0][2])).scaled(0.95 * ui->graphicsView_iris_g->size()));
            ui->graphicsView_iris_g->setScene(scene2);
            QGraphicsScene* scene3 = new QGraphicsScene;
            scene3->addPixmap(QPixmap(QString::fromStdString(results[0][3])).scaled(0.95 * ui->graphicsView_fp_g->size()));
            ui->graphicsView_fp_g->setScene(scene3);
        }
        break;
    default:
        break;
    }
}

void MainWindow::slot_btnGroupToggled(QAbstractButton* button, bool flag)
{
    if (flag) {
        init_test_views();
        init_gallery_views();
        int nId = pButtonGroup->id(button);
        set_model(nId);
    }
}

void MainWindow::on_textBrowser_textChanged()
{
    ui->textBrowser->moveCursor(QTextCursor::End);
}

