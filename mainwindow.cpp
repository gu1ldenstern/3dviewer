#include "mainwindow.h"

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  setWindowTitle("3D_Viewer");
  settings = new QSettings(QApplication::applicationDirPath() + "/config",
                           QSettings::IniFormat, this);
  loadConfig();
}

MainWindow::~MainWindow() {
  saveConfig();
  delete ui;
}

void MainWindow::on_openFile_clicked() {
  ui->label->setText("");
  resetBoxes();
  QString fileName =
      QFileDialog::getOpenFileName(this, "Open a file", "/Users", "*.obj", 0,
                                   QFileDialog::DontUseNativeDialog);

  ui->view->filename = fileName;
  ui->label->setText(ui->label->text() + fileName.split('/').last() + ';');
  ui->view->initParam();
  ui->view->initObj();
  ui->label->setText(ui->label->text() + " Number of edges: " +
                     QString::number(ui->view->res.total_edges) + ';');
  ui->label->setText(ui->label->text() + " Number of vertices: " +
                     QString::number(ui->view->res.v->amount_vert));
}

void MainWindow::on_rotation_xy_textChanged(const QString &arg1) {
  if (!ui->view->filename.isEmpty()) {
    ui->view->xyRot = (M_PI * ui->rotation_xy->value()) / 180;
    ui->view->Affine();
    ui->view->update();
  }
}

void MainWindow::on_rotation_xz_textChanged(const QString &arg1) {
  if (!ui->view->filename.isEmpty()) {
    ui->view->xzRot = (M_PI * ui->rotation_xz->value()) / 180;
    ui->view->Affine();
    ui->view->update();
  }
}

void MainWindow::on_rotation_yz_textChanged(const QString &arg1) {
  if (!ui->view->filename.isEmpty()) {
    ui->view->yzRot = (M_PI * ui->rotation_yz->value()) / 180;
    ui->view->Affine();
    ui->view->update();
  }
}

void MainWindow::on_trans_x_textChanged(const QString &arg1) {
  if (!ui->view->filename.isEmpty()) {
    ui->view->xTrans = ui->trans_x->value();
    ui->view->Affine();
    ui->view->update();
  }
}

void MainWindow::on_trans_y_textChanged(const QString &arg1) {
  if (!ui->view->filename.isEmpty()) {
    ui->view->yTrans = ui->trans_y->value();
    ui->view->Affine();
    ui->view->update();
  }
}

void MainWindow::on_trans_z_textChanged(const QString &arg1) {
  if (!ui->view->filename.isEmpty()) {
    ui->view->zTrans = ui->trans_z->value();
    ui->view->Affine();
    ui->view->update();
  }
}

void MainWindow::on_scale_textChanged(const QString &arg1) {
  if (!ui->view->filename.isEmpty()) {
    ui->view->Scale = ui->scale->value();
    ui->view->Affine();
    ui->view->update();
  }
}

void MainWindow::resetBoxes() {
  ui->rotation_xy->setValue(0);
  ui->rotation_xz->setValue(0);
  ui->rotation_yz->setValue(0);
  ui->trans_x->setValue(0);
  ui->trans_y->setValue(0);
  ui->trans_z->setValue(0);
  ui->scale->setValue(0.1);
}

void MainWindow::on_dashed_edge_clicked() {
  ui->view->dashedEdge = 1;
  ui->view->update();
}

void MainWindow::on_solid_edge_clicked() {
  ui->view->dashedEdge = 0;
  ui->view->update();
}

void MainWindow::on_thickness_edge_textChanged(const QString &arg1) {
  ui->view->thicknessEdge = ui->thickness_edge->value();
  ui->view->update();
}

void MainWindow::on_size_point_textChanged(const QString &arg1) {
  ui->view->sizePoint = ui->size_point->value();
  ui->view->update();
}

void MainWindow::on_circle_point_clicked() {
  ui->view->circlePoints = 1;
  ui->view->squarePoints = 0;
  ui->view->update();
}

void MainWindow::on_square_point_clicked() {
  ui->view->circlePoints = 0;
  ui->view->squarePoints = 1;
  ui->view->update();
}

void MainWindow::on_none_point_clicked() {
  ui->view->circlePoints = 0;
  ui->view->squarePoints = 0;
  ui->view->update();
}

void MainWindow::on_coloredge_clicked() {
  QColor Edge = QColorDialog::getColor(Qt::white, this, "Set Edges` Color");
  if (Edge.isValid()) {
    ui->view->edgeColor = Edge;
    ui->view->update();
  }
}

void MainWindow::on_colorvert_clicked() {
  QColor Vert = QColorDialog::getColor(Qt::white, this, "Set Edges` Color");
  if (Vert.isValid()) {
    ui->view->pointColor = Vert;
    ui->view->update();
  }
}

void MainWindow::on_colorback_clicked() {
  QColorDialog color;
  ui->view->backgroundColor = color.getColor();
  ui->view->update();
}

void MainWindow::saveConfig() {
  settings->setValue("thicknessEdge", ui->view->thicknessEdge);
  settings->setValue("centralProjection", ui->view->centralProjection);
  settings->setValue("dashedEdge", ui->view->dashedEdge);
  settings->setValue("circlePoints", ui->view->circlePoints);
  settings->setValue("squarePoints", ui->view->squarePoints);
  settings->setValue("sizePoint", ui->view->sizePoint);
  settings->setValue("backgroundColor", ui->view->backgroundColor);
  settings->setValue("edgeColor", ui->view->edgeColor);
  settings->setValue("pointColor", ui->view->pointColor);
}

void MainWindow::loadConfig() {
  ui->view->thicknessEdge = settings->value("thicknessEdge").toFloat();
  ui->view->centralProjection = settings->value("centralProjection").toInt();
  ui->view->dashedEdge = settings->value("dashedEdge").toInt();
  ui->view->circlePoints = settings->value("dashedEdge").toInt();
  ui->view->squarePoints = settings->value("squarePoints").toInt();
  ui->view->sizePoint = settings->value("sizePoint").toInt();
  ui->view->backgroundColor =
      settings->value("backgroundColor").value<QColor>();
  ui->view->edgeColor = settings->value("edgeColor").value<QColor>();
  ui->view->pointColor = settings->value("pointColor").value<QColor>();
}

void MainWindow::on_parallel_clicked() {
  ui->view->centralProjection = 0;
  ui->view->update();
}

void MainWindow::on_central_clicked() {
  ui->view->centralProjection = 1;
  ui->view->update();
}
