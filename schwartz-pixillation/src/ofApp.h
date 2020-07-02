#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp {
public:

  ofVideoGrabber vidGrabber;

  int capWidth;
  int capHeight;

  bool bLearnBackground;
  ofxCvColorImage colorImg;
  ofxCvGrayscaleImage grayImage, grayBg, grayDiff;
  ofxCvContourFinder contourFinder;

  ofxPanel gui;
  ofxIntSlider threshold;

  void setup();
  void update();
  void draw();

  void title();

  void keyPressed(int key);
};