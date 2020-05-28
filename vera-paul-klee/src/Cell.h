#pragma once

#include "Design.h"
#include "ofMain.h"

class Cell {
public:
  enum CellType { FULL = 0, HORIZONTAL, VERTICAL };

  Cell(const ofVec2f &position, float size);
  Cell(const ofVec2f &position, float size, CellType type);

  void draw(bool debug) const;

  void addDesign0(Design design);
  void addDesign1(Design design);

  void setDesigns0(const vector<Design> &designs);
  void setDesigns1(const vector<Design> &designs);

  void clearDesigns0();
  void clearDesigns1();

private:
  ofVec2f m_position;
  float m_size;
  CellType m_type;

  vector<Design> m_designs0;
  vector<Design> m_designs1;
};
