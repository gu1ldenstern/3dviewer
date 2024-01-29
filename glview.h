#ifndef GLVIEW_H
#define GLVIEW_H

#include <QtOpenGLWidgets>

extern "C" {
#include "./backend.h"
}
namespace Ui {
class glView;
}

class glView : public QOpenGLWidget {
  Q_OBJECT

 public:
  glView(QWidget *parent = nullptr);
  QString filename;
  ~glView();
  results res;
  float xyRot, yzRot, xzRot, xTrans, yTrans, zTrans, Scale;
  float sizePoint, thicknessEdge;

  QColor backgroundColor, edgeColor, pointColor;

  int circlePoints, squarePoints, dashedEdge, centralProjection;

  int *arrayOfIndexes = {0};
  float *arrayOfVerteces = {0};
  int countOfIndexes;
  vertex vert;
  matrix_t startPoints;
  void initObj();
  void initParam();
  void resetObj();
  void Affine();
  void drawLines();
  void projection();
  void drawPoints();

 protected:
  void initializeGL() override;
  void paintGL() override;
  void resizeGL(int w, int h) override;

 private:
  Ui::glView *ui;
};

#endif  // GLVIEW_H
