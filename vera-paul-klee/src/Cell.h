#pragma once

#include "ofMain.h"

class Cell {
public:
  Cell(const ofVec2f &position, float size);

  void drawDebug() const;

private:
  ofVec2f m_position;
  float m_size;
};
