#pragma once

#include "ofMain.h"

class Cell {
public:
  enum CellType { FULL = 0, HORIZONTAL, VERTICAL };

  Cell(const ofVec2f &position, float size);

  void drawDebug() const;

private:
  ofVec2f m_position;
  float m_size;
  CellType m_type;
};
