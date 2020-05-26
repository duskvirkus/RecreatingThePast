#include "LineGroup.h"

LineGroup::LineGroup(Grid* parent_ptr, size_t grid_x, size_t grid_y, size_t grid_width, size_t grid_height, function<void(Cell)> design) :
  m_parent_ptr(parent_ptr),
  m_grid_x(grid_x),
  m_grid_y(grid_y),
  m_grid_width(grid_width),
  m_grid_height(grid_height),
  m_design(design)
{}

void LineGroup::draw() {
  const auto cell = m_parent_ptr->getCell(m_grid_x, m_grid_y, m_grid_width, m_grid_height);
  m_design(cell);
}
