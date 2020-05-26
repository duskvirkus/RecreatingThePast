#include "Cell.h"

Cell::Cell(const ofVec2f &position, float size)
    : m_position(move(position)), m_size(size) {
  m_type = static_cast<CellType>(ofRandom(3));
}

void Cell::drawDebug() const {
  ofPushMatrix();
  ofTranslate(m_position);

  if (m_type == FULL) {
    ofDrawEllipse(0, 0, 3, 3);
    ofDrawRectangle(-m_size / 2, -m_size / 2, m_size, m_size);
  } else {
    ofPushMatrix();
    if (m_type == VERTICAL) {
      ofRotateRad(PI / 2);
    }
    ofTranslate(m_size / 4, 0);

    ofDrawEllipse(0, 0, 3, 3);
    ofDrawRectangle(-m_size / 4, -m_size / 2, m_size / 2, m_size);

    ofTranslate(-m_size / 2, 0);

    ofDrawEllipse(0, 0, 3, 3);
    ofDrawRectangle(-m_size / 4, -m_size / 2, m_size / 2, m_size);

    ofPopMatrix();
  }

  ofPopMatrix();
}
