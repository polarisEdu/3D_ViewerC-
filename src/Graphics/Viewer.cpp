#include "Viewer.h"

#include <qboxlayout.h>
#include <qcolordialog.h>
#include <qfiledialog.h>

#include "../Extern/Gif.h"
#include "OpenGLWidget.h"
#include "SettingsManager.h"

Viewer::Viewer(QWidget* parent) : QMainWindow(parent) {
  ui.setupUi(this);
  ui.openGLWidget->setFixedSize(500, 500);
  ui.openGLWidget->show();

  settingsManager_.load();

  ui.horizontalSlider_8->setValue(settingsManager_.getVertThickness());
  ui.horizontalSlider_9->setValue(settingsManager_.getEdgeThickness());
  ui.comboBox->setCurrentIndex(settingsManager_.getVertState());
  ui.comboBox_2->setCurrentIndex(settingsManager_.getEdgeState());
  ui.comboBox_3->setCurrentIndex(settingsManager_.getRenderState());

  setupConnects();
  setupColors();
  resetAll();
}

void Viewer::setupConnects() {
  connect(ui.horizontalSlider, &QAbstractSlider::valueChanged, this,
          &Viewer::updateMoveObjX);
  connect(ui.horizontalSlider_2, &QAbstractSlider::valueChanged, this,
          &Viewer::updateMoveObjY);
  connect(ui.horizontalSlider_3, &QAbstractSlider::valueChanged, this,
          &Viewer::updateMoveObjZ);
  connect(ui.horizontalSlider_4, &QAbstractSlider::valueChanged, this,
          &Viewer::updateRotObjX);
  connect(ui.horizontalSlider_5, &QAbstractSlider::valueChanged, this,
          &Viewer::updateRotObjY);
  connect(ui.horizontalSlider_6, &QAbstractSlider::valueChanged, this,
          &Viewer::updateRotObjZ);
  connect(ui.horizontalSlider_7, &QAbstractSlider::valueChanged, this,
          &Viewer::updateScale);
  connect(ui.lineEdit, &QLineEdit::textChanged, this,
          &Viewer::textLineMoveXChanged);
  connect(ui.lineEdit_2, &QLineEdit::textChanged, this,
          &Viewer::textLineMoveYChanged);
  connect(ui.lineEdit_3, &QLineEdit::textChanged, this,
          &Viewer::textLineMoveZChanged);
  connect(ui.lineEdit_4, &QLineEdit::textChanged, this,
          &Viewer::textLineRotXChanged);
  connect(ui.lineEdit_5, &QLineEdit::textChanged, this,
          &Viewer::textLineRotYChanged);
  connect(ui.lineEdit_6, &QLineEdit::textChanged, this,
          &Viewer::textLineRotZChanged);
  connect(ui.lineEdit_7, &QLineEdit::textChanged, this,
          &Viewer::textLineScaleChanged);
  connect(ui.pushButton, &QPushButton::pressed, this, &Viewer::loadModel);
  connect(ui.pushButton_2, &QPushButton::pressed, this,
          &Viewer::changeColorBackRed);
  connect(ui.pushButton_3, &QPushButton::pressed, this,
          &Viewer::changeColorBackGreen);
  connect(ui.pushButton_4, &QPushButton::pressed, this,
          &Viewer::changeColorBackBlue);
  connect(ui.pushButton_5, &QPushButton::pressed, this,
          &Viewer::changeColorBackWhite);
  connect(ui.pushButton_6, &QPushButton::pressed, this,
          &Viewer::changeColorBackBlack);
  connect(ui.pushButton_7, &QPushButton::pressed, this,
          &Viewer::changeColorVertRed);
  connect(ui.pushButton_8, &QPushButton::pressed, this,
          &Viewer::changeColorVertGreen);
  connect(ui.pushButton_9, &QPushButton::pressed, this,
          &Viewer::changeColorVertBlue);
  connect(ui.pushButton_10, &QPushButton::pressed, this,
          &Viewer::changeColorVertWhite);
  connect(ui.pushButton_11, &QPushButton::pressed, this,
          &Viewer::changeColorVertBlack);
  connect(ui.pushButton_12, &QPushButton::pressed, this,
          &Viewer::changeColorEdgeRed);
  connect(ui.pushButton_13, &QPushButton::pressed, this,
          &Viewer::changeColorEdgeGreen);
  connect(ui.pushButton_14, &QPushButton::pressed, this,
          &Viewer::changeColorEdgeBlue);
  connect(ui.pushButton_15, &QPushButton::pressed, this,
          &Viewer::changeColorEdgeWhite);
  connect(ui.pushButton_16, &QPushButton::pressed, this,
          &Viewer::changeColorEdgeBlack);
  connect(ui.horizontalSlider_8, &QAbstractSlider::valueChanged, this,
          &Viewer::changeVertThickness);
  connect(ui.horizontalSlider_9, &QAbstractSlider::valueChanged, this,
          &Viewer::changeEdgeThickness);
  connect(ui.comboBox, static_cast<void(QComboBox::*)(int)>(&QComboBox::activated), 
        this, &Viewer::changeVertState);
connect(ui.comboBox_2, static_cast<void(QComboBox::*)(int)>(&QComboBox::activated), 
        this, &Viewer::changeEdgeState);
connect(ui.comboBox_3, static_cast<void(QComboBox::*)(int)>(&QComboBox::activated), 
        this, &Viewer::changeRenderState);
  connect(ui.pushButton_17, &QPushButton::pressed, this,
          &Viewer::saveScreenshot);
  connect(ui.pushButton_18, &QPushButton::pressed, this, &Viewer::saveGif);
}

void Viewer::setupColors() {
  ui.pushButton_2->setStyleSheet("background-color: red");
  ui.pushButton_3->setStyleSheet("background-color: green");
  ui.pushButton_4->setStyleSheet("background-color: blue");
  ui.pushButton_5->setStyleSheet("background-color: white");
  ui.pushButton_6->setStyleSheet("background-color: black");
  ui.pushButton_7->setStyleSheet("background-color: red");
  ui.pushButton_8->setStyleSheet("background-color: green");
  ui.pushButton_9->setStyleSheet("background-color: blue");
  ui.pushButton_10->setStyleSheet("background-color: white");
  ui.pushButton_11->setStyleSheet("background-color: black");
  ui.pushButton_12->setStyleSheet("background-color: red");
  ui.pushButton_13->setStyleSheet("background-color: green");
  ui.pushButton_14->setStyleSheet("background-color: blue");
  ui.pushButton_15->setStyleSheet("background-color: white");
  ui.pushButton_16->setStyleSheet("background-color: black");
}

void Viewer::updateMoveObjX(int val) {
  ui.lineEdit->setText(QString::number(val));
  ui.openGLWidget->moveObj(s21::kMoveX, val);
  ui.openGLWidget->update();
}

void Viewer::updateMoveObjY(int val) {
  ui.lineEdit_2->setText(QString::number(val));
  ui.openGLWidget->moveObj(s21::kMoveY, val);
  ui.openGLWidget->update();
}

void Viewer::updateMoveObjZ(int val) {
  ui.lineEdit_3->setText(QString::number(val));
  ui.openGLWidget->moveObj(s21::kMoveZ, val);
  ui.openGLWidget->update();
}

void Viewer::updateRotObjX(int val) {
  ui.lineEdit_4->setText(QString::number(val));
  ui.openGLWidget->rotateObj(s21::kRotX, val);
  ui.openGLWidget->update();
}

void Viewer::updateRotObjY(int val) {
  ui.lineEdit_5->setText(QString::number(val));
  ui.openGLWidget->rotateObj(s21::kRotY, val);
  ui.openGLWidget->update();
}

void Viewer::updateRotObjZ(int val) {
  ui.lineEdit_6->setText(QString::number(val));
  ui.openGLWidget->rotateObj(s21::kRotZ, val);
  ui.openGLWidget->update();
}

void Viewer::updateScale(int val) {
  ui.lineEdit_7->setText(QString::number(val));
  ui.openGLWidget->scaleObj(val);
  ui.openGLWidget->update();
}

void Viewer::textLineMoveXChanged(const QString& val) {
  bool isSuccess = false;
  int num = val.toInt(&isSuccess);
  if (isSuccess) {
    ui.horizontalSlider->setValue(num);
    ui.openGLWidget->moveObj(s21::kMoveX, num);
    ui.openGLWidget->update();
  }
}

void Viewer::textLineMoveYChanged(const QString& val) {
  bool isSuccess = false;
  int num = val.toInt(&isSuccess);
  if (isSuccess) {
    ui.horizontalSlider_2->setValue(num);
    ui.openGLWidget->moveObj(s21::kMoveY, num);
    ui.openGLWidget->update();
  }
}

void Viewer::textLineMoveZChanged(const QString& val) {
  bool isSuccess = false;
  int num = val.toInt(&isSuccess);
  if (isSuccess) {
    ui.horizontalSlider_3->setValue(num);
    ui.openGLWidget->moveObj(s21::kMoveZ, num);
    ui.openGLWidget->update();
  }
}

void Viewer::textLineRotXChanged(const QString& val) {
  bool isSuccess = false;
  int num = val.toInt(&isSuccess);
  if (isSuccess) {
    ui.horizontalSlider_4->setValue(num);
    ui.openGLWidget->rotateObj(s21::kRotX, num);
    ui.openGLWidget->update();
  }
}

void Viewer::textLineRotYChanged(const QString& val) {
  bool isSuccess = false;
  int num = val.toInt(&isSuccess);
  if (isSuccess) {
    ui.horizontalSlider_5->setValue(num);
    ui.openGLWidget->rotateObj(s21::kRotY, num);
    ui.openGLWidget->update();
  }
}

void Viewer::textLineRotZChanged(const QString& val) {
  bool isSuccess = false;
  int num = val.toInt(&isSuccess);
  if (isSuccess) {
    ui.horizontalSlider_6->setValue(num);
    ui.openGLWidget->rotateObj(s21::kRotZ, num);
    ui.openGLWidget->update();
  }
}

void Viewer::textLineScaleChanged(const QString& val) {
  bool isSuccess = false;
  int num = val.toInt(&isSuccess);
  if (isSuccess && num > 0) {
    ui.horizontalSlider_7->setValue(num);
    ui.openGLWidget->scaleObj(num);
    ui.openGLWidget->update();
  }
}

void Viewer::changeColorBackRed() {
  settingsManager_.setBackgroundColor({1, 0, 0});
  ui.openGLWidget->update();
}

void Viewer::changeColorBackGreen() {
  settingsManager_.setBackgroundColor({0, 1, 0});
  ui.openGLWidget->update();
}

void Viewer::changeColorBackBlue() {
  settingsManager_.setBackgroundColor({0, 0, 1});
  ui.openGLWidget->update();
}

void Viewer::changeColorBackWhite() {
  settingsManager_.setBackgroundColor({1, 1, 1});
  ui.openGLWidget->update();
}

void Viewer::changeColorBackBlack() {
  settingsManager_.setBackgroundColor({0, 0, 0});
  ui.openGLWidget->update();
}

void Viewer::changeColorVertRed() {
  settingsManager_.setVertColor({1, 0, 0});
  ui.openGLWidget->update();
}

void Viewer::changeColorVertGreen() {
  settingsManager_.setVertColor({0, 1, 0});
  ui.openGLWidget->update();
}

void Viewer::changeColorVertBlue() {
  settingsManager_.setVertColor({0, 0, 1});
  ui.openGLWidget->update();
}

void Viewer::changeColorVertWhite() {
  settingsManager_.setVertColor({1, 1, 1});
  ui.openGLWidget->update();
}

void Viewer::changeColorVertBlack() {
  settingsManager_.setVertColor({0, 0, 0});
  ui.openGLWidget->update();
}

void Viewer::changeColorEdgeRed() {
  settingsManager_.setEdgeColor({1, 0, 0});
  ui.openGLWidget->update();
}

void Viewer::changeColorEdgeGreen() {
  settingsManager_.setEdgeColor({0, 1, 0});
  ui.openGLWidget->update();
}

void Viewer::changeColorEdgeBlue() {
  settingsManager_.setEdgeColor({0, 0, 1});
  ui.openGLWidget->update();
}

void Viewer::changeColorEdgeWhite() {
  settingsManager_.setEdgeColor({1, 1, 1});
  ui.openGLWidget->update();
}

void Viewer::changeColorEdgeBlack() {
  settingsManager_.setEdgeColor({0, 0, 0});
  ui.openGLWidget->update();
}

void Viewer::changeVertThickness(int val) {
  settingsManager_.setVertThickness(val);
  ui.openGLWidget->update();
}

void Viewer::changeEdgeThickness(int val) {
  settingsManager_.setEdgeThickness(val);
  ui.openGLWidget->update();
}

void Viewer::changeVertState(int state) {
  settingsManager_.setVertState((VertState)state);
  ui.openGLWidget->update();
}

void Viewer::changeEdgeState(int state) {
  settingsManager_.setEdgeState((EdgeState)state);
  ui.openGLWidget->update();
}

void Viewer::changeRenderState(int state) {
  settingsManager_.setRenderState((RenderState)state);
  ui.openGLWidget->update();
}

void Viewer::saveScreenshot() {
  QString file_path = QFileDialog::getSaveFileName(
      this, "Save Screenshot", "Screenshot", "JPEG (*.jpeg);;BMP (*.bmp)");
  if (!file_path.isEmpty()) {
    QPixmap screenshot = ui.openGLWidget->grab();
    if (file_path.endsWith(".JPEG"))
      screenshot.save(file_path, "JPEG");
    else
      screenshot.save(file_path, "BMP");
  }
}

void Viewer::saveGif() {
  QString file_path =
      QFileDialog::getSaveFileName(this, "Save Gif", "Gif", "GIF (*.gif)");
  if (!file_path.isEmpty()) {
    QImage baseImg(ui.openGLWidget->size(), QImage::Format_RGB32), resultImg;
    GifWriter gifWriter;
    QPainter painter(&baseImg);
    GifBegin(&gifWriter, file_path.toLatin1(), 640, 480, 10);
    for (int i = 0; i < 50; ++i) {
      ui.openGLWidget->render(&painter);
      resultImg = baseImg.scaled(QSize(640, 480));
      GifWriteFrame(&gifWriter, resultImg.bits(), 640, 480, 10);
    }
    GifEnd(&gifWriter);
  }
}

void Viewer::loadModel() {
  QString filePath = QFileDialog::getOpenFileName(this, "Choose a model");
  if (!filePath.isEmpty()) {
    resetAll();
    QFileInfo fileInfo(filePath);
    ui.label_fileName->setText(fileInfo.fileName());
    control_.readObjFile(filePath.toStdString());
    ui.label_Edges->setText(QString::number(control_.getObjEdges().size()));
    ui.label_Vertices->setText(QString::number(control_.getObjVerts().size()));
    ui.openGLWidget->updateObj();
    ui.openGLWidget->update();
  }
}

void Viewer::resetAll() {
  ui.horizontalSlider->setValue(0);
  ui.lineEdit->setText("0");
  ui.horizontalSlider_2->setValue(0);
  ui.lineEdit_2->setText("0");
  ui.horizontalSlider_3->setValue(0);
  ui.lineEdit_3->setText("0");
  ui.horizontalSlider_4->setValue(0);
  ui.lineEdit_4->setText("0");
  ui.horizontalSlider_5->setValue(0);
  ui.lineEdit_5->setText("0");
  ui.horizontalSlider_6->setValue(0);
  ui.lineEdit_6->setText("0");
  ui.horizontalSlider_7->setValue(50);
  ui.lineEdit_7->setText("50");
}

Viewer::~Viewer() {}
