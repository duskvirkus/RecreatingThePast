#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxLaunchControllers.h"

struct ColorScheme {
  ofColor forground;
  ofColor background;
  ofColor accent;
};

class ofApp : public ofBaseApp {
public:
  ofxLaunchControl lc;
  ofxPanel gui;
  ofParameter<bool> showControls;
  ofParameter<float> magintude;
  ofParameter<int> divisions;
  ofParameter<float> accentChance;
  ofParameter<bool> regenerate;
  ofParameter<bool> cycleColor;

  ofParameter<int> forgroundRed;
  ofParameter<int> forgroundGreen;
  ofParameter<int> forgroundBlue;
  ofParameter<int> forgroundAlpha;

  ofParameter<int> backgroundRed;
  ofParameter<int> backgroundGreen;
  ofParameter<int> backgroundBlue;

  ofParameter<int> accentRed;
  ofParameter<int> accentGreen;
  ofParameter<int> accentBlue;
  ofParameter<int> accentAlpha;

  int border;

  int sqNum;
  int sqSize;
  float noisePosition;
  vector<ofVec2f> positions;
  vector<ofVec2f> offsets;
  vector<bool> accents;
  float previousAccentChance;

  vector<ColorScheme> colors;
  size_t currentColor;
  ColorScheme *controlColors;

  void setup();
  void update();
  void draw();

  void keyPressed(int);

  void title();

  void generatePositions();
  void generateOffsets();
  void generateAccents();
};
