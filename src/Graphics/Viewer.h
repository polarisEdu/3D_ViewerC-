#pragma once

#include <QtWidgets/QMainWindow>

#include "../Logic/ObjController.h"
#include "SettingsManager.h"
#include "ui_Viewer.h"

class Viewer : public QMainWindow {
  Q_OBJECT

 public:
  Viewer(QWidget* parent = nullptr);
  ~Viewer();

 private slots:
  void updateMoveObjX(int val);
  void updateMoveObjY(int val);
  void updateMoveObjZ(int val);
  void updateRotObjX(int val);
  void updateRotObjY(int val);
  void updateRotObjZ(int val);
  void updateScale(int val);
  void textLineMoveXChanged(const QString& val);
  void textLineMoveYChanged(const QString& val);
  void textLineMoveZChanged(const QString& val);
  void textLineRotXChanged(const QString& val);
  void textLineRotYChanged(const QString& val);
  void textLineRotZChanged(const QString& val);
  void textLineScaleChanged(const QString& val);
  void changeColorBackRed();
  void changeColorBackGreen();
  void changeColorBackBlue();
  void changeColorBackWhite();
  void changeColorBackBlack();
  void changeColorVertRed();
  void changeColorVertGreen();
  void changeColorVertBlue();
  void changeColorVertWhite();
  void changeColorVertBlack();
  void changeColorEdgeRed();
  void changeColorEdgeGreen();
  void changeColorEdgeBlue();
  void changeColorEdgeWhite();
  void changeColorEdgeBlack();
  void changeVertThickness(int val);
  void changeEdgeThickness(int val);
  void changeVertState(int state);
  void changeEdgeState(int state);
  void changeRenderState(int state);
  void saveScreenshot();
  void saveGif();
  void loadModel();

 private:
  void setupConnects();
  void setupColors();
  void resetAll();

  Ui::ViewerClass ui;
  s21::ObjController& control_ = s21::ObjController::getObjController();
  SettingsManager& settingsManager_ = SettingsManager::getSettingsManager();
};
