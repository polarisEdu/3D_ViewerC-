#ifndef SETTINGS_MANAGER_H_
#define SETTINGS_MANAGER_H_

struct Color {
  float r, g, b;
};

enum VertState { kNone, kCircle, kSquare };

enum EdgeState { kSolid, kDotted };

enum RenderState { kParralel, kCentral };

class SettingsManager {
 public:
  inline static SettingsManager& getSettingsManager() {
    static SettingsManager settingsManager;
    return settingsManager;
  }

  void load();

  inline Color getBackgroundColor() { return backgroundColor_; };
  inline Color getVertColor() { return vertColor_; };
  inline Color getEdgeColor() { return edgeColor_; };
  inline int getVertThickness() { return vertThickness_; };
  inline int getEdgeThickness() { return edgeThickness_; };
  inline VertState getVertState() { return vertState_; };
  inline EdgeState getEdgeState() { return edgeState_; };
  inline RenderState getRenderState() { return renderState_; };

  void setBackgroundColor(Color col);
  void setVertColor(Color col);
  void setEdgeColor(Color col);
  void setVertThickness(int val);
  void setEdgeThickness(int val);
  void setVertState(VertState state);
  void setEdgeState(EdgeState state);
  void setRenderState(RenderState state);

 private:
  SettingsManager() = default;
  Color backgroundColor_ = {0, 0, 0};
  Color vertColor_ = {0, 1, 0};
  Color edgeColor_ = {1, 1, 1};
  int edgeThickness_ = 2;
  int vertThickness_ = 10;
  VertState vertState_ = kNone;
  EdgeState edgeState_ = kSolid;
  RenderState renderState_ = kParralel;

  void save();
};

#endif