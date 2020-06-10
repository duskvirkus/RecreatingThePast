#include "ofApp.h"

constexpr const char *PROJECT_NAME = "A la Recherche de Paul Klee";
constexpr const char *CREATOR = "Vera Molnár";
constexpr const char *RECREATOR = "Violet Graham";

void ofApp::setup() {
  ofBackground(255);

  dl.setup();

  gui.setup();
  gui.add(showControls.set("Show Controls", false));
  gui.add(showGrid.set("Show Grid", false));

  lc.setup();
  lc.toggle(0, showControls);
  lc.toggle(1, showGrid);

  grid.setup(30, 30, 0, 0, ofGetWidth(), ofGetHeight());

  for (int i = 0; i < 400; ++i) {
    const int width = ofRandom(1) < 0.5 ? 1 : 2;
    const int height = width == 1 ? 2 : 1;
    int posX = ofRandom(grid.getRowCount() - (width - 1));
    int posY = ofRandom(grid.getColumnCount() - (height - 1));
    if (width == 2) {
      posX &= ~1;
    }
    if (height == 2) {
      posY &= ~1;
    }
    groups.emplace_back(&grid, posX, posY, width, height, dl.getRandom());
  }
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
