#include "ofApp.h"

constexpr const char *PROJECT_NAME = "A la Recherche de Paul Klee";
constexpr const char *CREATOR = "Vera Molnár";
constexpr const char *RECREATOR = "Violet Graham";

void ofApp::setup() {
  ofBackground(255);

  gui.setup();
  gui.add(showControls.set("Show Controls", false));
  gui.add(showGrid.set("Show Grid", false));

  lc.setup();
  lc.toggle(0, showControls);
  lc.toggle(1, showGrid);

  grid.setup(30, 30, 0, 0, ofGetWidth(), ofGetHeight());

  groups.emplace_back(&grid, 5, 3, 2, 1, [](Cell cell) {
    ofPushMatrix();
    ofTranslate(cell.x, cell.y);
    for (int i = 0; i < 5; i++) {
      int x = ofMap(i, 0, 5, 0, cell.w);
      ofDrawLine(x, 0, x, cell.h);
    }
    ofPopMatrix();
  });
}

void ofApp::update() { title(); }

void ofApp::draw() {
  ofSetColor(0);
  for (auto group : groups) {
    group.draw();
  }
  if (showGrid) {
    grid.draw();
  }
  if (showControls) {
    gui.draw();
  }
}

void ofApp::title() {
  stringstream titleStream;
  titleStream << PROJECT_NAME << " - " << CREATOR << " - " << RECREATOR
              << " - FPS: " << static_cast<int>(ofGetFrameRate());
  ofSetWindowTitle(titleStream.str());
}
