#pragma once

#include "ofxGui.h"
#include "ofxLaunchControllers.h"
#include "Grid.h"
#include "LineGroup.h"
#include "ofMain.h"
#include "Cell.h"

class ofApp : public ofBaseApp {
public:
  ofxLaunchControl lc;
  ofxPanel gui;

  ofParameter<bool> showControls;
  ofParameter<bool> showGrid;

  Grid grid;
  vector<LineGroup> groups;

  void setup();
  void update();
  void draw();

  void title();
};
