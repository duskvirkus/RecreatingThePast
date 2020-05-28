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

  ofParameter<float> linesProbability;
  ofParameter<float> blocksProbability;
  ofParameter<float> trianglesProbability;
  ofParameter<float> fullProbability;

  enum LayerName {
    DiagonalLines = 0,
    DiagonalBlocks,
    Triangles,
    Full,
    max = Full,
  };
  vector<vector<Cell>> layers;

  vector<function<void(float, float)>> blueprints;

  vector<vector<vector<Design>>> designSets;

  vector<float> proabilities;

  void setup();
  void update();
  void draw();

  void title();

  void createLayers();
  void generateCells(vector<Cell> &cells, int cellNum, bool fullCells);
  void createBlueprints();
  void createDesignSets();

  void populateLayer(LayerName layer);
};
