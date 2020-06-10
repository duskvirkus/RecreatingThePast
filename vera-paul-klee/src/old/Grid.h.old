#pragma once

#include "Cell.h"
#include "ofMain.h"

class Grid {
public:
  void setup(size_t rows, size_t cols, float x, float y, float w, float h);
  void draw();
  Cell getCell(size_t x, size_t y, size_t w, size_t h);
  size_t getRowCount() const;
  size_t getColumnCount() const;

private:
  size_t m_rows;
  size_t m_cols;
  float m_x;
  float m_y;
  float m_width;
  float m_height;
};
