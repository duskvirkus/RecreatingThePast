#include "DesignLibrary.h"

void DesignLibrary::setup() {

  // addDesign([](Cell cell) {
  //   ofPushMatrix();
  //   ofTranslate(cell.x, cell.y);

  //   ofDrawLine(0, 0, cell.w, cell.h);

  //   ofPopMatrix();
  // });

  // addDesign([](Cell cell) {
  //   ofPushMatrix();
  //   ofTranslate(cell.x, cell.y);

  //   ofDrawLine(0, cell.h, cell.w, 0);

  //   ofPopMatrix();
  // });

  addDesign([](Cell cell) {
    ofPushMatrix();
    ofTranslate(cell.x, cell.y);

    for (int i = 0; i < 3; ++i) {
      float x = ofLerp(0, cell.w, i/3.0);
      float y = ofLerp(0, cell.h, i/3.0);
      ofDrawLine(x, 0, cell.w, cell.h - y);
    }

    ofPopMatrix();
  });

  addDesign([](Cell cell) {
    ofPushMatrix();
    ofTranslate(cell.x, cell.y);

    for (int i = 0; i < 3; ++i) {
      float x = ofLerp(0, cell.w, i/3.0);
      float y = ofLerp(0, cell.h, i/3.0);
      ofDrawLine(x, cell.h, cell.w, y);
    }

    ofPopMatrix();
  });

}

void DesignLibrary::addDesign(function<void(Cell)> design) {
  m_designs.push_back(design);
}

function<void(Cell)> DesignLibrary::getRandom() const {
  int index = ofRandom(m_designs.size());
  return m_designs[index];
}
