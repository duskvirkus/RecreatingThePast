#include "Design.h"

Design::Design(function<void(float, float)> draw) : m_draw(draw) {
  // switch (int(ofRandom(4))) {
  // case 0:
  //   m_rotation = 0;
  //   break;
  // case 1:
  //   m_rotation = PI / 2;
  //   break;
  // case 2:
  //   m_rotation = PI;
  //   break;
  // case 3:
  //   m_rotation = 3 * PI / 2;
  //   break;
  // }
  m_rotation = int(ofRandom(4)) * 90;
}

int Design::rotation() const { return m_rotation; }

function<void(float, float)> Design::getDraw() const { return m_draw; }
