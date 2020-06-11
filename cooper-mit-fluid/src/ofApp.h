#pragma once

#include "ofMain.h"
#include "ofxFluid.h"

class ofApp : public ofBaseApp {
public:
  ofxFluid fluid;
  int width, height;

  ofImage mit;

  ofFbo canvas;
  ofPixels pix;
  ofTexture invert;

  void setup();
  void update();
  void draw();

  void title();
};
