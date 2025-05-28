#ifndef OBJ_FACADE_H_
#define OBJ_FACADE_H_

#include "ObjReader.h"
#include "TransformCom.h"

namespace s21 {
enum Action { kMoveX, kMoveY, kMoveZ, kRotX, kRotY, kRotZ, kScale };

class ObjFacade {
 public:
  inline FileStatus readFile(const std::string& filePath) {
    return objReader_.processFile(filePath);
  }

  inline void reset() { objReader_.reset(); }

  inline std::vector<double> getVerts() { return objReader_.getVerts(); }

  inline std::vector<unsigned int> getEdges() { return objReader_.getEdges(); }

  inline float getNormVec() { return objReader_.getNormVec(); }

  void transform(Action act, std::vector<double>& verts, double val) {
    switch (act) {
      case kMoveX: {
        MoveXCom mx;
        tController_.setCommand(&mx);
        break;
      }
      case kMoveY: {
        MoveYCom my;
        tController_.setCommand(&my);
        break;
      }
      case kMoveZ: {
        MoveZCom mz;
        tController_.setCommand(&mz);
        break;
      }
      case kRotX: {
        RotXCom rx;
        tController_.setCommand(&rx);
        break;
      }
      case kRotY: {
        RotYCom ry;
        tController_.setCommand(&ry);
        break;
      }
      case kRotZ: {
        RotZCom rz;
        tController_.setCommand(&rz);
        break;
      }
      case kScale: {
        ScaleCom sc;
        tController_.setCommand(&sc);
      }
    }
    tController_.transform(verts, val);
  }

 private:
  ObjReader& objReader_ = ObjReader::getObjReader();
  TransformController tController_;
};
}

#endif