#pragma once

#include "ofMain.h"

class Design {
public:
  Design(function<void(float, float)> draw, int rotation);

  int rotation() const;
  function<void(float, float)> getDraw() const;

private:
  function<void(float, float)> m_draw;
  int m_rotation;
};
