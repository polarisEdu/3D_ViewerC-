#include "OpenGLWidget.h"

MyOpenGLWidget::MyOpenGLWidget(QWidget* parent) {
  edges_ = control_.getObjEdges();
  vert_ = control_.getObjVerts();
  normVec_ = control_.getObjNormVec();
}

MyOpenGLWidget::~MyOpenGLWidget() {}

void MyOpenGLWidget::initializeGL() {
  initializeOpenGLFunctions();
  glEnable(GL_DEPTH_TEST);
}

void MyOpenGLWidget::paintGL() {
  Color background = settingsManager_.getBackgroundColor();
  glClearColor(background.r, background.g, background.b, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glVertexPointer(3, GL_DOUBLE, 0, vert_.data());
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (settingsManager_.getRenderState() == kCentral) {
    glOrtho(-1 * normVec_, 1 * normVec_, -1 * normVec_, 1 * normVec_,
            -1 * normVec_, 1000 * normVec_);
    glTranslatef(0, -normVec_ / 2, 0);
  } else {
    glFrustum(-1 * normVec_, 1 * normVec_, -1 * normVec_, 1 * normVec_,
              normVec_, 1000 * normVec_);
    glTranslatef(0, 0, -2 * normVec_);
    glRotatef(30, 1, 0, 0);
  }

  glEnableClientState(GL_VERTEX_ARRAY);
  if (settingsManager_.getVertState() != kNone) paintPoints();
  paintLines();
  glDisableClientState(GL_VERTEX_ARRAY);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void MyOpenGLWidget::paintLines() {
  if (settingsManager_.getEdgeState() == kDotted) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x00FF);
  } else
    glDisable(GL_LINE_STIPPLE);
  glLineWidth(settingsManager_.getEdgeThickness());
  Color edge = settingsManager_.getEdgeColor();
  glColor3f(edge.r, edge.g, edge.b);
  glEnableClientState(GL_VERTEX_ARRAY);
  glDrawElements(GL_LINES, static_cast<GLsizei>(edges_.size()), GL_UNSIGNED_INT,
                 edges_.data());
  glDisableClientState(GL_VERTEX_ARRAY);
}

void MyOpenGLWidget::paintPoints() {
  if (settingsManager_.getVertState() == kCircle) glEnable(GL_POINT_SMOOTH);
  glPointSize(settingsManager_.getVertThickness());
  Color vert = settingsManager_.getVertColor();
  glColor3f(vert.r, vert.g, vert.b);
  glVertexPointer(3, GL_DOUBLE, 0, vert_.data());
  glEnableClientState(GL_VERTEX_ARRAY);
  glDrawArrays(GL_POINTS, 0, static_cast<GLsizei>(vert_.size() / 3));
  glDisableClientState(GL_VERTEX_ARRAY);
  glDisable(GL_POINT_SMOOTH);
}

void MyOpenGLWidget::moveObj(s21::Action act, double value) {
  double k = 0;
  switch (act) {
    case s21::kMoveX:
      k = translateX_;
      translateX_ = value;
      break;
    case s21::kMoveY:
      k = translateY_;
      translateY_ = value;
      break;
    case s21::kMoveZ:
      k = translateZ_;
      translateZ_ = value;
  }
  value = (value - k) * normVec_ * 0.01;
  control_.transformObj(act, vert_, value);
}

void MyOpenGLWidget::rotateObj(s21::Action act, double angle) {
  double k = 0;
  switch (act) {
    case s21::kRotX:
      k = rotateX_;
      rotateX_ = angle;
      break;
    case s21::kRotY:
      k = rotateY_;
      rotateY_ = angle;
      break;
    case s21::kRotZ:
      k = rotateZ_;
      rotateZ_ = angle;
  }
  angle -= k;
  control_.transformObj(act, vert_, angle);
}

void MyOpenGLWidget::scaleObj(double value) {
  double k = scale_;
  scale_ = value;
  control_.transformObj(s21::kScale, vert_, value / k);
}

void MyOpenGLWidget::updateObj() {
  edges_ = control_.getObjEdges();
  vert_ = control_.getObjVerts();
  normVec_ = control_.getObjNormVec();
}