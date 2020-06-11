#include "ofApp.h"

constexpr const char *PROJECT_NAME = "MIT";
constexpr const char *CREATOR = "Muriel Cooper";
constexpr const char *RECREATOR = "Violet Graham";

void ofApp::setup() {

  ofEnableAlphaBlending();
  ofSetCircleResolution(100);

  ofSetBackgroundAuto(false);

  mit.loadImage("mit-media-lab.png");

  width = ofGetWidth();
  height = ofGetHeight();

  fluid.allocate(width, height, 0.5);

  fluid.dissipation = 0.99;
  fluid.velocityDissipation = 0.99;

  fluid.setGravity(ofVec2f(0.0, 0.05));

  fluid.begin();
  // ofSetColor(0, 0);
  // ofSetColor(255);
  // ofDrawBitmapString("MIT", width * 0.5, height * 0.5);
  // for (int i = 0; i < width; ++i) {
  //   ofSetColor(ofRandom(127), ofRandom(127));
  //   ofDrawLine(i, 0, i, height);
  // }
  // for (int i = 0; i < height; ++i) {
  //   ofSetColor(ofRandom(127), ofRandom(127));
  //   ofDrawLine(0, i, width, i);
  // }
  // paper.draw(0, 0);
  // ofCircle(width * 0.5, height * 0.35, 40);
  fluid.end();
  fluid.setUseObstacles(true);

  const auto mitPix = mit.getPixels();

  // for (int i = 0; i <= width / 20; ++i) {
  //   for (int j = 0; j <= height / 20; ++j) {
  //     cout << mit.getColor(i + j * width) << '\n';
  //     if (mit.getColor(i + j * width) == ofColor(0, 0, 0, 255)) {
  //       cout << "hello" << '\n';
  //       fluid.addConstantForce(ofPoint(i * 20, j * 20), ofPoint(0, 0),
  //                              ofFloatColor(0.5, 0.1, 0.0), 5.f);
  //     }
  //   }
  // }

  const int scale = 10;
  const int yScale = 20;
  const int xScale = 4;

  for (int i = 0; i <= width / xScale; ++i) {
    for (int j = 0; j <= height / yScale; ++j) {
      if (mit.getColor((i * xScale * 4) + (j * yScale * 4) * width) ==
          ofColor::white) {
        fluid.addConstantForce(ofPoint(i * xScale, j * yScale), ofPoint(0, 0),
                               ofFloatColor(0.5, 0.1, 0.0), 1.f);
      }
    }
  }

  canvas.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
  invert.allocate(ofGetWidth(), ofGetHeight(), GL_RGB);
}

void ofApp::update() {
  title();
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

  // for (int i = 0; i <= width / 20; ++i) {
  //   for (int j = 0; j <= height / 20; ++j) {
  //     ofSetColor(mit.getColor((i * 20 * 4) + (j * 20 * 4) * width));

  //     cout << mit.getColor((i * 20 * 4) + (j * 20 * 4) * width) << '\n';
  //     ofDrawEllipse(i * 20, j * 20, 20, 20);
  //   }
  // }
}

void ofApp::title() {
  stringstream titleStream;
  titleStream << PROJECT_NAME << " - " << CREATOR << " - " << RECREATOR
              << " - FPS: " << static_cast<int>(ofGetFrameRate());
  ofSetWindowTitle(titleStream.str());
}
