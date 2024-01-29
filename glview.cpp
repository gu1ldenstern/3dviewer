#include "glview.h"

#include "mainwindow.h"

glView::glView(QWidget *parent) : QOpenGLWidget(parent) {
  initialize(&res, &vert);
}

glView::~glView() {
  cleanup(&res);
  s21_remove_matrix(&startPoints);
  free(arrayOfIndexes);
}

void glView::paintGL() {
  if (backgroundColor.isValid()) {
    glClearColor(backgroundColor.redF(), backgroundColor.greenF(),
                 backgroundColor.blueF(), 1);
  } else {
    glClearColor(1, 1, 0.96, 1);
  }
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  projection();
  drawLines();
  if (circlePoints || squarePoints) {
    drawPoints();
  }
}

void glView::drawLines() {
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, res.v->coord);
  if (edgeColor.isValid()) {
    glColor3d(edgeColor.redF(), edgeColor.greenF(), edgeColor.blueF());
  } else {
    glColor3d(0.83, 0.66, 0.5);
  }
  if (thicknessEdge) {
    glLineWidth(thicknessEdge);
  } else {
    glLineWidth(1);
  }

  if (dashedEdge) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x00F0);
  }

  glDrawElements(GL_LINES, countOfIndexes, GL_UNSIGNED_INT, arrayOfIndexes);

  if (dashedEdge) {
    glDisable(GL_LINE_STIPPLE);
  }

  glDisableClientState(GL_VERTEX_ARRAY);
}

void glView::drawPoints() {
  glEnableClientState(GL_VERTEX_ARRAY);
  if (sizePoint) {
    glPointSize(sizePoint);
  } else {
    glPointSize(5);
  }
  if (pointColor.isValid()) {
    glColor3d(pointColor.redF(), pointColor.greenF(), pointColor.blueF());
  } else {
    glColor3d(0.35, 0.53, 0.6);
  }
  if (circlePoints) {
    glEnable(GL_POINT_SMOOTH);
  }
  glEnableClientState(GL_VERTEX_ARRAY);
  glDrawArrays(GL_POINTS, 0, res.v->amount_vert);
  affine(&res, startPoints, xyRot, yzRot, xzRot, xTrans, yTrans, zTrans, Scale);

  if (circlePoints) {
    glDisable(GL_POINT_SMOOTH);
  }
  glDisableClientState(GL_VERTEX_ARRAY);
}

void glView::initializeGL() { glEnable(GL_DEPTH); }

void glView::initObj() {
  QByteArray ba = filename.toLocal8Bit();
  char *charFileName = ba.data();
  resetObj();
  initialize(&res, &vert);
  int error = parser(&res, charFileName);
  countOfIndexes = get_indexes(&arrayOfIndexes, &res, &error);
  s21_create_matrix(res.v->amount_vert, 3, &startPoints);
  if (!error) {
    normalize(&res, &startPoints);
    affine(&res, startPoints, xyRot, yzRot, xzRot, xTrans, yTrans, zTrans,
           Scale);
  }
  fill_matrix(&startPoints, &res);
}

void glView::initParam() {
  xyRot = 0;
  yzRot = 0;
  xzRot = 0;
  xTrans = 0;
  yTrans = 0;
  zTrans = 0;
  Scale = 1;
}

void glView::resetObj() {
  initialize(&res, &vert);
  initParam();
  update();
}

void glView::projection() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (centralProjection) {
    glFrustum(-1.2, 1.2, -1.2, 1.2, 3, 6);
    glTranslated(0, 0, -4);
  } else {
    glOrtho(-1.2, 1.2, -1.2, 1.2, -1.2, 1.2);
  }
}
void glView::resizeGL(int w, int h) {}

void glView::Affine() {
  affine(&res, startPoints, xyRot, yzRot, xzRot, xTrans, yTrans, zTrans, Scale);
  update();
}
