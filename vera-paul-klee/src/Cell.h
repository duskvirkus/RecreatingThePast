#pragma once

#include "Design.h"
#include "ofMain.h"

class Cell {
public:
  enum CellType { FULL = 0, HORIZONTAL, VERTICAL };

  Cell(const ofVec2f &position, float size);

  void draw(bool debug) const;

  void addDesign0(Design design);
  void addDesign1(Design design);

private:
  ofVec2f m_position;
  float m_size;
  CellType m_type;

  vector<Design> m_designs0;
  vector<Design> m_designs1;
};
