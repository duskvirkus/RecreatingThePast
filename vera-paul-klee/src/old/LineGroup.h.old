#pragma once

#include "Grid.h"
#include "ofMain.h"

class LineGroup {
public:

  LineGroup(Grid* parent, size_t grid_x, size_t grid_y, size_t grid_width, size_t grid_height, function<void(Cell)> design);
  void draw();

private:

  Grid* m_parent_ptr;
  size_t m_grid_x;
  size_t m_grid_y;
  size_t m_grid_width;
  size_t m_grid_height;
  function<void(Cell)> m_design;

};
