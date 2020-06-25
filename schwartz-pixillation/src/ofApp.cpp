#include "ofApp.h"

constexpr const char* PROJECT_NAME = "Pixillation";
constexpr const char* CREATOR = "Lillian Schwartz";
constexpr const char* RECREATOR = "Violet Graham";

void ofApp::setup() {

  ofSetVerticalSync(true);

  gui.setup();
  gui.add(threshold.setup("Threshold", 50, 0, 100));

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

  capWidth = 640;
  capHeight = 360;

  bLearnBackground = false;

  colorImg.allocate(capWidth, capHeight);
  grayImage.allocate(capWidth, capHeight);
  grayBg.allocate(capWidth, capHeight);
  grayDiff.allocate(capWidth, capHeight);
}

void ofApp::update() {
  title();

  vidGrabber.update();

  if (vidGrabber.isFrameNew()) {
    colorImg.setFromPixels(vidGrabber.getPixels());

    grayImage = colorImg;
    if (bLearnBackground == true) {
      grayBg = grayImage;
      bLearnBackground = false;
    }

    grayDiff.absDiff(grayBg, grayImage);
    grayDiff.threshold(threshold);

    contourFinder.findContours(grayDiff, 20, (340 * 240) / 3, 10, true);
  }
}

void ofApp::draw() {
  ofBackground(0);

  vidGrabber.draw(0, 0, capWidth, capHeight);

  grayImage.draw(capWidth, 0);
  grayDiff.draw(0, capHeight);

  for (int i = 0; i < contourFinder.nBlobs; i++) {
    contourFinder.blobs[i].draw(0, capHeight);
  }

  gui.draw();
}

void ofApp::title() {
  stringstream titleStream;
  titleStream << PROJECT_NAME << " - " << CREATOR
    << " - FPS: " << static_cast<int>(ofGetFrameRate());
  ofSetWindowTitle(titleStream.str());
}

void ofApp::keyPressed(int key) {
  bLearnBackground = true;
}
