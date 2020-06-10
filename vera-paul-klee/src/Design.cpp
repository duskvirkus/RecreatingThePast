#include "Design.h"

Design::Design(function<void(float, float)> draw, int rotation)
    : m_draw(draw), m_rotation(rotation) {
  // m_rotation = int(ofRandom(4)) * 90;
}

int Design::rotation() const { return m_rotation; }

function<void(float, float)> Design::getDraw() const { return m_draw; }
