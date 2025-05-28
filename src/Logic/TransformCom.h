#ifndef TRANSFORM_COMMAND_H_
#define TRANSFORM_COMMAND_H_

#include <vector>

namespace s21 {
class TransformCommand {
 public:
  virtual void transform(std::vector<double>& verts, int first, int last,
                         double val) = 0;
};

class MoveXCom : public TransformCommand {
 public:
  void transform(std::vector<double>& verts, int first, int last,
                 double val) override;
};

class MoveYCom : public TransformCommand {
 public:
  void transform(std::vector<double>& verts, int first, int last,
                 double val) override;
};

class MoveZCom : public TransformCommand {
 public:
  void transform(std::vector<double>& verts, int first, int last,
                 double val) override;
};

class RotXCom : public TransformCommand {
 public:
  void transform(std::vector<double>& verts, int first, int last,
                 double angle) override;
};

class RotYCom : public TransformCommand {
 public:
  void transform(std::vector<double>& verts, int first, int last,
                 double angle) override;
};

class RotZCom : public TransformCommand {
 public:
  void transform(std::vector<double>& verts, int first, int last,
                 double angle) override;
};

class ScaleCom : public TransformCommand {
 public:
  void transform(std::vector<double>& verts, int first, int last,
                 double val) override;
};

class TransformController {
 public:
  inline void setCommand(TransformCommand* command) noexcept {
    command_ = command;
  };
  void transform(std::vector<double>& verts, double val);

 private:
  TransformCommand* command_ = nullptr;
};
}

#endif