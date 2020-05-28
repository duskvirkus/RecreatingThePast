#include "Cell.h"

Cell::Cell(const ofVec2f &position, float size)
    : m_position(move(position)), m_size(size) {
  // m_type = static_cast<CellType>(ofRandom(3));
  const auto rand = ofRandom(1);
  if (rand < 0.1) {
    m_type = FULL;
  } else if (rand > 0.1 && rand < 0.55) {
    m_type = HORIZONTAL;
  } else {
    m_type = VERTICAL;
  }
}

void Cell::draw(bool debug) const {
  ofPushMatrix();
  ofTranslate(m_position);

  if (m_type == FULL) {
    if (debug) {
      ofDrawEllipse(0, 0, 3, 3);
      ofDrawRectangle(-m_size / 2, -m_size / 2, m_size, m_size);
    } else {
      for (size_t i = 0; i < m_designs0.size(); ++i) {
        ofPushMatrix();
        ofRotateDeg(m_designs0[i].rotation());

        m_designs0[i].getDraw()(m_size, m_size);

        ofPopMatrix();
      }
    }
  } else {
    ofPushMatrix();
    if (m_type == VERTICAL) {
      ofRotateRad(PI / 2);
    }
    ofTranslate(m_size / 4, 0);

    if (debug) {
      ofDrawEllipse(0, 0, 3, 3);
      ofDrawRectangle(-m_size / 4, -m_size / 2, m_size / 2, m_size);
    } else {
      for (size_t i = 0; i < m_designs0.size(); ++i) {
        ofPushMatrix();
        const auto rot = m_designs0[i].rotation();
        ofRotateDeg(rot);

        if (rot == 90 || rot == 270) {
          m_designs0[i].getDraw()(m_size, m_size / 2);
        } else {
          m_designs0[i].getDraw()(m_size / 2, m_size);
        }

        ofPopMatrix();
      }
    }

    ofTranslate(-m_size / 2, 0);

    if (debug) {
      ofDrawEllipse(0, 0, 3, 3);
      ofDrawRectangle(-m_size / 4, -m_size / 2, m_size / 2, m_size);
    } else {
      for (size_t i = 0; i < m_designs1.size(); ++i) {
        ofPushMatrix();
        const auto rot = m_designs1[i].rotation();
        ofRotateDeg(rot);

        if (rot == 90 || rot == 270) {
          m_designs1[i].getDraw()(m_size, m_size / 2);
        } else {
          m_designs1[i].getDraw()(m_size / 2, m_size);
        }

        ofPopMatrix();
      }
    }

    ofPopMatrix();
  }

  ofPopMatrix();
}

void Cell::addDesign0(Design design) { m_designs0.push_back(design); }

void Cell::addDesign1(Design design) { m_designs1.push_back(design); }

void Cell::setDesigns0(const vector<Design> &designs) {
  m_designs0 = move(designs);
}

void Cell::setDesigns1(const vector<Design> &designs) {
  m_designs1 = move(designs);
}

void Cell::clearDesigns0() { m_designs0.clear(); }

void Cell::clearDesigns1() { m_designs1.clear(); }
