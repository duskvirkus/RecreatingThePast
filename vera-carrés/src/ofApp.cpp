#include "ofApp.h"

constexpr const char *PROJECT_NAME = "25 Carrés";
constexpr const char *CREATOR = "Vera Molnár";
constexpr const char *RECREATOR = "Violet Graham";

void ofApp::setup() {
  border = ofGetWidth() / 16;
  sqNum = 5;
  noisePosition = 0;

  generatePositions();
  generateOffsets();
  generateAccents();

  gui.setup();
  gui.add(showControls.set("Show Controls", false));
  gui.add(magintude.set("Magnitude", ofGetWidth() / 16, 0, ofGetWidth() / 8));
  gui.add(divisions.set("Divisions", 5, 1, 20));
  gui.add(accentChance.set("Accent Chance", 0.4, 0, 1));
  gui.add(regenerate.set("Regenetate", false));
  gui.add(cycleColor.set("Cycle Color", false));

  gui.add(forgroundRed.set("Forground Red", 0, 0, 255));
  gui.add(forgroundGreen.set("Forground Green", 130, 0, 255));
  gui.add(forgroundBlue.set("Forground Blue", 120, 0, 255));
  gui.add(forgroundAlpha.set("Forground Alpha", 216, 0, 255));

  gui.add(backgroundRed.set("Background Red", 255, 0, 255));
  gui.add(backgroundGreen.set("Background Green", 255, 0, 255));
  gui.add(backgroundBlue.set("Background Blue", 255, 0, 255));

  gui.add(accentRed.set("Accent Red", 178, 0, 255));
  gui.add(accentGreen.set("Accent Green", 90, 0, 255));
  gui.add(accentBlue.set("Accent Blue", 0, 0, 255));
  gui.add(accentAlpha.set("Accent Alpha", 128, 0, 255));

  lc.setup();
  lc.toggle(0, showControls);
  lc.knob(0, magintude);
  lc.knob(1, divisions);
  lc.knob(2, accentChance);
  lc.momentary(1, regenerate);
  lc.momentary(2, cycleColor);

  lc.knob(8, forgroundRed);
  lc.knob(9, forgroundGreen);
  lc.knob(10, forgroundBlue);
  lc.knob(11, forgroundAlpha);

  lc.knob(4, backgroundRed);
  lc.knob(5, backgroundGreen);
  lc.knob(6, backgroundBlue);

  lc.knob(12, accentRed);
  lc.knob(13, accentGreen);
  lc.knob(14, accentBlue);
  lc.knob(15, accentAlpha);

  currentColor = 0;
  colors.push_back({ofColor(0, 240), ofColor(255), ofColor(0, 240)});
  colors.push_back({ofColor(120, 65, 67, 240), ofColor(200, 220, 230),
                    ofColor(140, 45, 75, 240)});

  colors.push_back({ofColor::white, ofColor::white, ofColor::white});
  controlColors = &colors[colors.size() - 1];

  previousAccentChance = accentChance;
}

void ofApp::update() {
  title();
  if (divisions != sqNum) {
    sqNum = divisions;
    generatePositions();
    generateOffsets();
  }
  if (regenerate) {
    generateOffsets();
    generateAccents();
    regenerate = false;
  }
  if (cycleColor) {
    currentColor++;
    if (currentColor >= colors.size()) {
      currentColor = 0;
    }
    cycleColor = false;
  }
  if (currentColor == colors.size() - 1) {
    controlColors->forground.set(forgroundRed, forgroundGreen, forgroundBlue,
                                 forgroundAlpha);
    controlColors->background.set(backgroundRed, backgroundGreen,
                                  backgroundBlue);
    controlColors->accent.set(accentRed, accentGreen, accentBlue, accentAlpha);
  }
  if (accentChance != previousAccentChance) {
    previousAccentChance = accentChance;
    generateAccents();
  }
}

void ofApp::draw() {

  ofBackground(colors[currentColor].background);

  for (size_t i = 0; i < positions.size() && i < offsets.size(); ++i) {
    ofSetColor(accents[i] ? colors[currentColor].accent
                          : colors[currentColor].forground);

    ofPushMatrix();

    ofTranslate(positions[i]);
    ofTranslate(offsets[i] * magintude);

    ofDrawRectangle(0, 0, sqSize, sqSize);

    ofPopMatrix();
  }

  if (showControls) {
    gui.draw();
  }
}

void ofApp::keyPressed(int) { showControls = !showControls; }

void ofApp::title() {
  stringstream titleStream;
  titleStream << PROJECT_NAME << " - " << CREATOR << " - " << RECREATOR
              << " - FPS: " << static_cast<int>(ofGetFrameRate());
  ofSetWindowTitle(titleStream.str());
}

void ofApp::generatePositions() {

  sqSize = (ofGetWidth() - border * 2) / sqNum;

  const int sqTotal = sqNum * sqNum;
  positions.clear();
  positions.reserve(sqTotal);
  for (int i = 0; i < sqTotal; ++i) {
    positions.emplace_back(
        ofMap(i % sqNum, 0, sqNum, border, ofGetWidth() - border),
        ofMap(i / sqNum, 0, sqNum, border, ofGetHeight() - border));
  }
}

void ofApp::generateOffsets() {
  offsets.clear();
  offsets.reserve(positions.size());
  for (size_t i = 0; i < positions.size(); ++i) {
    offsets.emplace_back(ofRandom(-1, 1), ofRandom(-1, 1));
  }
}

void ofApp::generateAccents() {
  accents.clear();
  accents.reserve(positions.size());
  for (size_t i = 0; i < positions.size(); ++i) {
    accents.push_back(ofRandom(1) < accentChance);
  }
}
