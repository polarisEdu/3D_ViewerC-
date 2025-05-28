#include "TransformCom.h"

#define _USE_MATH_DEFINES

#include <cmath>
#include <thread>

namespace s21 {
void MoveXCom::transform(std::vector<double>& verts, int first, int last,
                         double val) {
  for (int i = first; i < last; i += 3) verts[i] += val;
}

void MoveYCom::transform(std::vector<double>& verts, int first, int last,
                         double val) {
  for (int i = first + 1; i < last; i += 3) verts[i] += val;
}

void MoveZCom::transform(std::vector<double>& verts, int first, int last,
                         double val) {
  for (int i = first + 2; i < last; i += 3) verts[i] += val;
}

void RotXCom::transform(std::vector<double>& verts, int first, int last,
                        double angle) {
  angle *= M_PI / 180;
  for (int i = first; i < last; i += 3) {
    double y = verts[i + 1];
    double z = verts[i + 2];
    verts[i + 1] = y * cos(angle) + z * sin(angle);
    verts[i + 2] = -y * sin(angle) + z * cos(angle);
  }
}

void RotYCom::transform(std::vector<double>& verts, int first, int last,
                        double angle) {
  angle *= M_PI / 180;
  for (int i = first; i < last; i += 3) {
    double x = verts[i];
    double z = verts[i + 2];
    verts[i] = x * cos(angle) + z * sin(angle);
    verts[i + 2] = -x * sin(angle) + z * cos(angle);
  }
}

void RotZCom::transform(std::vector<double>& verts, int first, int last,
                        double angle) {
  angle *= M_PI / 180;
  for (int i = first; i < last; i += 3) {
    double x = verts[i];
    double y = verts[i + 1];
    verts[i] = x * cos(angle) + y * sin(angle);
    verts[i + 1] = -x * sin(angle) + y * cos(angle);
  }
}

void ScaleCom::transform(std::vector<double>& verts, int first, int last,
                         double val) {
  for (int i = first; i < last; ++i) verts[i] *= val;
}

void TransformController::transform(std::vector<double>& verts, double val) {
  int procCount = std::thread::hardware_concurrency();
  if (!procCount) procCount = 1;
  std::vector<std::thread*> thrMas;
  thrMas.resize(procCount);
  s21::TransformCommand* commandCopy = command_;
  for (int i = 0; i < procCount; ++i) {
    thrMas[i] = new std::thread([&verts, i, procCount, commandCopy, val] {
      int step = ceil((double)(verts.size() / 3) / (double)procCount);
      int first = step * i * 3;
      int last = step * (i + 1) * 3;
      if (last > verts.size()) last = verts.size();
      commandCopy->transform(verts, first, last, val);
    });
  }
  for (int i = 0; i < procCount; ++i) {
    thrMas[i]->join();
    delete thrMas[i];
  }
}
}