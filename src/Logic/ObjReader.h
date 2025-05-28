#ifndef FILE_READER_H_
#define FILE_READER_H_

#include <set>
#include <string>
#include <vector>

namespace s21 {
enum FileStatus { kSuccess, kErrorFileNotFound, kReadError, kErrorEmptyFile };

class ObjReader {
 public:
  inline static ObjReader& getObjReader() {
    static ObjReader objReader;
    return objReader;
  }
  FileStatus processFile(const std::string& fileStr);
  void reset();

  inline std::vector<double> getVerts() noexcept { return verts_; };
  inline std::vector<unsigned int> getEdges() noexcept { return edges_; };
  inline float getNormVec() const noexcept {
    return (xMax_ + yMax_ + zMax_) / 3;
  };

 private:
  ObjReader() = default;
  FileStatus allocateSpace(std::ifstream& file);
  FileStatus readLine(const std::string& line);
  FileStatus readVert(const std::string& rawData);
  FileStatus readFace(const std::string& rawData);
  void insertUniquePair(const std::vector<unsigned int>& faces);

  float xMax_ = -10, yMax_ = -10, zMax_ = -10;
  std::set<std::pair<unsigned int, unsigned int>> vectorSet_;
  std::size_t vertsCount_ = 0;
  std::vector<double> verts_;
  std::vector<unsigned> edges_;
};
}

#endif
