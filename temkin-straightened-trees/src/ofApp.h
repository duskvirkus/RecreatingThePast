#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp {
public:

  vector<ofImage> sources;
  vector<ofImage> lines;

  vector<vector<int>> offsets;

  void setup();
  void update();
  void draw();

  void title();

  void calculateOffsets();
  void extendOffsets();
  void applyOffsets();

};
