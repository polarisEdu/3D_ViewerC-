#pragma once
#include <QOpenGLWidget>
#include <QWidget>
#include <QtOpenGL>

#include "../Logic/ObjController.h"
#include "SettingsManager.h"

class MyOpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions {
  Q_OBJECT
 public:
  explicit MyOpenGLWidget(QWidget* parent = nullptr);
  void moveObj(s21::Action act, double value);
  void rotateObj(s21::Action act, double angle);
  void scaleObj(double value);
  void updateObj();

 protected:
  void initializeGL() override;
  void paintGL() override;
  void paintLines();
  void paintPoints();

 private:
  ~MyOpenGLWidget() override;
  s21::ObjController& control_ = s21::ObjController::getObjController();
  SettingsManager& settingsManager_ = SettingsManager::getSettingsManager();
  std::vector<unsigned int> edges_;
  std::vector<double> vert_;
  GLfloat normVec_;
  double translateX_, translateY_, translateZ_, rotateX_, rotateY_, rotateZ_,
      scale_ = 50;
};
