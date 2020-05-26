#include "Cell.h"

Cell::Cell(const ofVec2f &position, float size)
    : m_position(move(position)), m_size(size) {}

void Cell::drawDebug() const {
  ofPushMatrix();
  ofTranslate(m_position);

  ofDrawRectangle(-m_size / 2, -m_size / 2, m_size, m_size);

  ofPopMatrix();
}
