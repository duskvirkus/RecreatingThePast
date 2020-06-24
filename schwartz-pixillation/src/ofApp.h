#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp {
public:

  ofVideoGrabber vidGrabber;
  ofFbo capture;

  void setup();
  void update();
  void draw();

  void title();
};