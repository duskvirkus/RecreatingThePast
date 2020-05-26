#include "Grid.h"

void Grid::setup(size_t rows, size_t cols, float x, float y, float w, float h) {
  m_rows = rows;
  m_cols = cols;
  m_x = x;
  m_y = y;
  m_width = w;
  m_height = h;
}

void Grid::draw() {
  ofNoFill();
  ofSetColor(0, 0, 255, 10);

  const float xSize = m_width / m_rows;
  const float ySize = m_height / m_cols;
  for (size_t i = 0; i < m_rows; ++i) {
    for (size_t j = 0; j < m_cols; ++j) {
      ofDrawRectangle(m_x + i * xSize, m_y + j * ySize, xSize, ySize);
    }
  }
}

Cell Grid::getCell(size_t x, size_t y, size_t w, size_t h) {
  const float xSize = m_width / m_rows;
  const float ySize = m_height / m_cols;
  return {m_x + x * xSize, m_y + y * ySize, xSize * w, ySize * h};
}

size_t Grid::getRowCount() const {
  return m_rows;
}

size_t Grid::getColumnCount() const {
  return m_cols;
}
