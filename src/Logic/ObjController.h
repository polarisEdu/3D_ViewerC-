#ifndef OBJ_CONTROLLER_H_
#define OBJ_CONTROLLER_H_

#include "ObjFacade.h"

namespace s21 {
class ObjController {
 public:
  inline static ObjController& getObjController() {
    static ObjController objController;
    return objController;
  }

  inline FileStatus readObjFile(const std::string& filePath) {
    return objFacade_.readFile(filePath);
  }

  inline void resetObj() { objFacade_.reset(); }

  inline std::vector<double> getObjVerts() { return objFacade_.getVerts(); }

  std::vector<unsigned int> getObjEdges() { return objFacade_.getEdges(); }

  float getObjNormVec() { return objFacade_.getNormVec(); }

  void transformObj(Action act, std::vector<double>& verts, double val) {
    objFacade_.transform(act, verts, val);
  }

 private:
  ObjController() = default;
  ObjFacade objFacade_;
};
}

#endif