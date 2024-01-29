#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAction>
#include <QColor>
#include <QColorDialog>
#include <QFileDialog>
#include <QMainWindow>
#include <QMenuBar>
#include <QSettings>
#include <QWidget>
#include <iostream>

#include "glview.h"

extern "C" {
#include "./backend.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void on_openFile_clicked();

  void on_rotation_xy_textChanged(const QString &arg1);
  void on_rotation_xz_textChanged(const QString &arg1);
  void on_rotation_yz_textChanged(const QString &arg1);
  void on_trans_x_textChanged(const QString &arg1);
  void on_trans_y_textChanged(const QString &arg1);
  void on_trans_z_textChanged(const QString &arg1);
  void on_scale_textChanged(const QString &arg1);

  void resetBoxes();

  void on_solid_edge_clicked();
  void on_dashed_edge_clicked();
  void on_thickness_edge_textChanged(const QString &arg1);

  void on_size_point_textChanged(const QString &arg1);
  void on_circle_point_clicked();
  void on_square_point_clicked();
  void on_none_point_clicked();

  void on_coloredge_clicked();
  void on_colorvert_clicked();
  void on_colorback_clicked();

  void on_parallel_clicked();
  void on_central_clicked();

  void saveConfig();
  void loadConfig();

 private:
  Ui::MainWindow *ui;
  glView *glview;
  QSettings *settings;
};
#endif  // MAINWINDOW_H
