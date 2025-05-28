#include "SettingsManager.h"

#include <fstream>

void SettingsManager::load() {
  std::fstream fl("settings.bin", std::ios::binary | std::ios::in);
  if (fl.is_open()) {
    SettingsManager& settingsManager = getSettingsManager();
    fl.read(reinterpret_cast<char*>(&settingsManager), sizeof(settingsManager));
    fl.close();
  }
}

void SettingsManager::save() {
  std::fstream fl("settings.bin",
                  std::ios::trunc | std::ios::binary | std::ios::out);
  if (fl.is_open()) {
    SettingsManager& settingsManager = getSettingsManager();
    fl.write(reinterpret_cast<char*>(&settingsManager),
             sizeof(settingsManager));
    fl.close();
  }
}

void SettingsManager::setBackgroundColor(Color col) {
  backgroundColor_ = col;
  save();
}

void SettingsManager::setVertColor(Color col) {
  vertColor_ = col;
  save();
}

void SettingsManager::setEdgeColor(Color col) {
  edgeColor_ = col;
  save();
}

void SettingsManager::setVertThickness(int val) {
  vertThickness_ = val;
  save();
}

void SettingsManager::setEdgeThickness(int val) {
  edgeThickness_ = val;
  save();
}

void SettingsManager::setVertState(VertState state) {
  vertState_ = state;
  save();
}

void SettingsManager::setEdgeState(EdgeState state) {
  edgeState_ = state;
  save();
}

void SettingsManager::setRenderState(RenderState state) {
  renderState_ = state;
  save();
}