#include "ObjReader.h"

#include <fstream>
#include <sstream>

namespace s21 {

FileStatus ObjReader::processFile(const std::string& fileStr) {
  reset();
  std::ifstream fl(fileStr);
  FileStatus fStatus = kErrorFileNotFound;
  if (fl.is_open()) {
    fStatus = allocateSpace(fl);
    std::string line;
    while (fStatus == kSuccess && std::getline(fl, line))
      fStatus = readLine(line);
    if (verts_.empty() || edges_.empty()) fStatus = kErrorEmptyFile;
    if (fStatus != kSuccess) reset();
    fl.close();
  }
  return fStatus;
}

void ObjReader::reset() {
  vertsCount_ = 0;
  xMax_ = yMax_ = zMax_ = -10;
  vectorSet_.clear();
  verts_.clear();
  edges_.clear();
}

FileStatus ObjReader::allocateSpace(std::ifstream& file) {
  FileStatus fStatus = kSuccess;
  size_t vertCount = 0;
  size_t edgeCount = 0;
  std::string line;
  while (std::getline(file, line)) {
    if (!(line.length() > 2)) continue;
    std::istringstream iss(line);
    std::string type;
    iss >> type;
    if (type == "v") {
      vertCount += 3;
    } else if (type == "f") {
      std::string edgesLine = line.substr(2);
      std::istringstream issF(edgesLine);
      std::string indexStr;
      while (issF >> indexStr) edgeCount += 2;
    }
  }
  if (vertCount > 0 && edgeCount > 0) {
    verts_.reserve(vertCount);
    edges_.reserve(edgeCount);
  } else
    fStatus = kErrorEmptyFile;
  file.clear();
  file.seekg(0, std::ios::beg);
  return fStatus;
}

FileStatus ObjReader::readLine(const std::string& line) {
  FileStatus fStatus = kSuccess;
  if (line.length() > 2) {
    std::string type;
    std::istringstream iss(line);
    iss >> type;
    if (type == "v") {
      std::string rawData = line.substr(2);
      fStatus = readVert(rawData);
    } else if (type == "f") {
      std::string rawData = line.substr(2);
      fStatus = readFace(rawData);
    }
  }
  return fStatus;
}

FileStatus ObjReader::readVert(const std::string& rawData) {
  double x, y, z;
  std::istringstream iss(rawData);
  FileStatus fStatus = kReadError;
  if (iss >> x >> y >> z) {
    fStatus = kSuccess;
    if (abs(x) > xMax_) xMax_ = abs(x);
    if (abs(y) > yMax_) yMax_ = abs(y);
    if (abs(z) > yMax_) zMax_ = abs(z);
    verts_.push_back(x);
    verts_.push_back(y);
    verts_.push_back(z);
    ++vertsCount_;
  } else
    reset();
  return fStatus;
}

FileStatus ObjReader::readFace(const std::string& rawData) {
  FileStatus fStatus = kSuccess;
  std::string indexStr;
  std::istringstream iss(rawData);
  int firstIndex = -1;
  std::vector<unsigned int> facesMas;
  while (iss >> indexStr) {
    int index = 0;
    try {
      index = std::stoi(indexStr);
    } catch (...) {
      fStatus = kReadError;
      break;
    }
    if (std::abs(index) > verts_.size()) {
      fStatus = kReadError;
      break;
    }
    if (index < 0)
      index += vertsCount_;
    else
      index -= 1;
    if (firstIndex == -1) {
      firstIndex = index;
      facesMas.push_back(index);
    } else {
      facesMas.push_back(index);
      facesMas.push_back(index);
    }
  }
  facesMas.push_back(firstIndex);
  insertUniquePair(facesMas);
  return fStatus;
}

void ObjReader::insertUniquePair(const std::vector<unsigned int>& faces) {
  if (faces.size() % 2 == 0) {
    for (int i = 0; i < faces.size() - 1; ++i) {
      std::pair<unsigned int, unsigned int> vector(faces[i], faces[i + 1]);
      std::pair<unsigned int, unsigned int> inverseVector(faces[i + 1],
                                                          faces[i]);
      if (vectorSet_.find(vector) == vectorSet_.end() &&
          vectorSet_.find(inverseVector) == vectorSet_.end()) {
        edges_.push_back(faces[i]);
        edges_.push_back(faces[i + 1]);
        vectorSet_.insert(vector);
      }
    }
  }
}
}