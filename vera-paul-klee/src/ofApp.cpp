#include "ofApp.h"

constexpr const char *PROJECT_NAME = "A la Recherche de Paul Klee";
constexpr const char *CREATOR = "Vera Molnár";
constexpr const char *RECREATOR = "Violet Graham";

void ofApp::setup() {
  ofBackground(255);

  // ofDisableAntiAliasing();

  gui.setup();
  gui.add(showControls.set("Show Controls", false));
  gui.add(showDebug.set("Show Debug", false));
  gui.add(regenerate.set("Regenerate", false));
  gui.add(linesProbability.set("Lines", 0.3, 0, 1));
  gui.add(blocksProbability.set("Blocks", 0.5, 0, 1));
  gui.add(trianglesProbability.set("Triangles", 0.05, 0, 1));
  gui.add(fullProbability.set("Full", 0.05, 0, 1));

  lc.setup();
  lc.toggle(0, showControls);
  lc.toggle(1, showDebug);
  lc.toggle(2, regenerate);

  lc.knob(0, linesProbability);
  lc.knob(1, blocksProbability);
  lc.knob(2, trianglesProbability);
  lc.knob(3, fullProbability);

  proabilities.push_back(0.3);
  proabilities.push_back(0.5);
  proabilities.push_back(0.05);
  proabilities.push_back(0.05);

  createLayers();

  createBlueprints();

  createDesignSets();

  for (size_t i = 0; i < LayerName::max; ++i) {
    populateLayer(static_cast<LayerName>(i));
  }
}

void ofApp::update() {
  title();
  if (regenerate) {
    for (size_t i = 0; i < LayerName::max; ++i) {
      populateLayer(static_cast<LayerName>(i));
    }
    regenerate = false;
  }

  proabilities[0] = linesProbability;
  proabilities[1] = blocksProbability;
  proabilities[2] = trianglesProbability;
  proabilities[3] = fullProbability;
}

void ofApp::draw() {

  ofSetColor(0);
  for (const auto &layer : layers) {
    for (const auto &cell : layer) {
      cell.draw(false);
    }
  }

  if (showDebug) {
    ofNoFill();

    ofSetColor(0, 0, 255, 50);
    for (const auto &cell : layers[0]) {
      cell.draw(true);
    }

    ofSetColor(0, 255, 0, 100);
    for (const auto &cell : layers[1]) {
      cell.draw(true);
    }
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

void ofApp::createLayers() {
  for (size_t i = 0; i < LayerName::max; ++i) {
    vector<Cell> cells;
    generateCells(cells, 15, i == LayerName::Full);
    layers.push_back(cells);
  }
}

void ofApp::generateCells(vector<Cell> &cells, int cellNum, bool fullCells) {
  const float cellSize = ofGetWidth() / static_cast<float>(cellNum);
  for (int i = 0; i < cellNum; ++i) {
    for (int j = 0; j < cellNum; ++j) {
      if (fullCells) {
        cells.emplace_back(
            ofVec2f(i * cellSize + cellSize / 2, j * cellSize + cellSize / 2),
            cellSize, Cell::CellType::FULL);
      } else {
        cells.emplace_back(
            ofVec2f(i * cellSize + cellSize / 2, j * cellSize + cellSize / 2),
            cellSize,
            ofRandom(1) > 0.5 ? Cell::CellType::HORIZONTAL
                              : Cell::CellType::VERTICAL);
      }
    }
  }
}

#define addDiagonalBlueprint(numLines)                                         \
  blueprints.push_back([](float width, float height) {                         \
    for (int i = 0; i < numLines; ++i) {                                       \
      float x = ofLerp(0, width, static_cast<float>(i) / numLines);            \
      float y = ofLerp(0, height, static_cast<float>(i) / numLines);           \
      ofDrawLine(x - width / 2, -height / 2, width / 2, height / 2 - y);       \
    }                                                                          \
  });

void ofApp::createBlueprints() {

  addDiagonalBlueprint(1);
  addDiagonalBlueprint(2);
  addDiagonalBlueprint(3);
  addDiagonalBlueprint(5);
  addDiagonalBlueprint(7);
  addDiagonalBlueprint(11);

  blueprints.push_back([](float width, float height) {
    for (int i = 0; i < 7; ++i) {
      const float x1 = ofMap(i, 0, 6, 0, width / 2);
      const float y1 = ofMap(i, 0, 6, -height / 2, height / 2);
      const float x2 = ofMap(i, -1, 6, -width / 2, width / 2);
      ofDrawLine(x1, y1, x2, height / 2);
    }
  });
}

void ofApp::createDesignSets() {
  for (size_t i = 0; i <= LayerName::max; ++i) {
    designSets.emplace_back();
  }

  // cout << designSets.size() << '\n';

  for (int i = 0; i < 4; ++i) {
    vector<vector<Design>> set;
    for (size_t j = 0; j < 6; ++j) {
      vector<Design> d;

      d.emplace_back(blueprints[j], i * 90);

      set.push_back(d);
    }
    designSets[DiagonalLines] = set;
  }

  for (int i = 0; i < 2; ++i) {
    vector<vector<Design>> set;
    for (size_t j = 0; j < 6; ++j) {
      vector<Design> d;

      d.emplace_back(blueprints[j], i * 90);
      d.emplace_back(blueprints[j], i * 90 + 180);

      set.push_back(d);
    }
    designSets[DiagonalBlocks] = set;
  }

  {
    vector<vector<Design>> set;
    for (int i = 0; i < 4; ++i) {
      vector<Design> d;

      d.emplace_back(blueprints[6], i * 90);

      set.push_back(d);
    }
    designSets[Triangles] = set;
  }

  designSets[Full] = designSets[DiagonalLines];

  // for (size_t k = 0; k < layers.size(); ++k) {
  //   for (size_t i = 0; i < layers[k].size(); ++i) {
  //     if (ofRandom(1) < 0.6) {
  //       layers[k][i].setDesigns0(
  //           possibleDesigns[int(ofRandom(possibleDesigns.size()))]);
  //     } else {
  //       layers[k][i].clearDesigns0();
  //     }
  //     if (ofRandom(1) < 0.6) {
  //       layers[k][i].setDesigns1(
  //           possibleDesigns[int(ofRandom(possibleDesigns.size()))]);
  //     } else {
  //       layers[k][i].clearDesigns1();
  //     }
  //   }
  // }
}

void ofApp::populateLayer(LayerName layer) {
  for (size_t i = 0; i < layers[layer].size(); ++i) {
    if (ofRandom(1) < proabilities[layer]) {
      layers[layer][i].setDesigns0(
          designSets[layer][int(ofRandom(designSets[layer].size()))]);
    } else {
      layers[layer][i].clearDesigns0();
    }
    if (ofRandom(1) < proabilities[layer]) {
      layers[layer][i].setDesigns1(
          designSets[layer][int(ofRandom(designSets[layer].size()))]);
    } else {
      layers[layer][i].clearDesigns1();
    }
  }
}
