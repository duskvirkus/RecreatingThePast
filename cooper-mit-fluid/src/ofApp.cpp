#include "ofApp.h"

constexpr const char *PROJECT_NAME = "MIT";
constexpr const char *CREATOR = "Muriel Cooper";
constexpr const char *RECREATOR = "Violet Graham";

void ofApp::setup() {

  ofEnableAlphaBlending();
  ofSetCircleResolution(100);

  ofSetBackgroundAuto(false);

  mit.loadImage("mit-media-lab-color.png");

  width = ofGetWidth();
  height = ofGetHeight();

  fluid.allocate(width, height, 0.5);

  fluid.dissipation = 0.99;
  fluid.velocityDissipation = 0.99;

  const auto mitPix = mit.getPixels();

  const int yScale = 10; // 10;
  const int xScale = 5;  // 10;

  for (int i = 0; i <= width / xScale; ++i) {
    for (int j = 0; j < height / yScale; ++j) {
      const auto c = mit.getColor((i * xScale * 4) + (j * yScale * 4) * width);
      if (c != ofColor::black) {
        fluid.addConstantForce(ofPoint(i * xScale, j * yScale), ofPoint(0, 0),
                               ofColor(255 - c.r, 255 - c.g, 255 - c.b), 1.f);
      }
    }
  }

  canvas.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
  invert.allocate(ofGetWidth(), ofGetHeight(), GL_RGB);
}

void ofApp::update() {
  title();

  fluid.setGravity(ofVec2f(ofRandom(-0.05, 0.05), ofRandom(0.03, 0.05)));

  fluid.update();
}

void ofApp::draw() {

  canvas.begin();
  fluid.draw();
  canvas.end();

  canvas.readToPixels(pix);
  for (size_t i = 0; i < pix.size(); ++i) {
    pix[i] = 255 - pix[i];
  }
  invert.loadData(pix);

  invert.draw(0, 0);
}

void ofApp::title() {
  stringstream titleStream;
  titleStream << PROJECT_NAME << " - " << CREATOR << " - " << RECREATOR
              << " - FPS: " << static_cast<int>(ofGetFrameRate());
  ofSetWindowTitle(titleStream.str());
}
