#include "ofApp.h"

constexpr const char* PROJECT_NAME = "Pixillation";
constexpr const char* CREATOR = "Lillian Schwartz";
constexpr const char* RECREATOR = "Violet Graham";

void ofApp::setup() {

  ofSetVerticalSync(true);

  vector<ofVideoDevice> devices = vidGrabber.listDevices();

  for (size_t i = 0; i < devices.size(); i++) {
    if (devices[i].bAvailable) {
      ofLogNotice() << devices[i].id << ": " << devices[i].deviceName;
    }
    else {
      ofLogNotice() << devices[i].id << ": " << devices[i].deviceName << " - unavailable ";
    }
  }

  vidGrabber.setDeviceID(0);
  vidGrabber.setDesiredFrameRate(30);
  vidGrabber.initGrabber(640, 360);

  capture.allocate(480, 360, GL_RGBA);
}

void ofApp::update() {
  title();

  vidGrabber.update();
}

void ofApp::draw() {
  ofBackground(0);

  capture.begin();
  vidGrabber.draw(0, 0, 480, 360);
  capture.end();

  capture.draw(0, 0);
}

void ofApp::title() {
  stringstream titleStream;
  titleStream << PROJECT_NAME << " - " << CREATOR
    << " - FPS: " << static_cast<int>(ofGetFrameRate());
  ofSetWindowTitle(titleStream.str());
}
