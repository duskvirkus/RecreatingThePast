#pragma once

#include "Cell.h"
#include "ofMain.h"
#include "ofxGui.h"
#include "ofxLaunchControllers.h"

class ofApp : public ofBaseApp {
public:
  ofxLaunchControl lc;
  ofxPanel gui;

  ofParameter<bool> showControls;
  ofParameter<bool> showDebug;
  ofParameter<bool> regenerate;

  vector<function<void(float, float)>> blueprints;

  enum LayerName {
    DiagonalLines = 0,
    DiagonalBlocks,
    Triangles,
    Full,
  };
  vector<vector<Cell>> layers;

  void setup();
  void update();
  void draw();

  void title();

  void generateCells(vector<Cell> &cells, int cellNum);
  void createBlueprints();
  void generateDesigns();
};
