#pragma once

#include "ofMain.h"
#include "Cell.h"

class DesignLibrary {
public:

  void setup();

  void addDesign(function<void(Cell)> design);
  
  function<void(Cell)> getRandom() const;

private:

  vector<function<void(Cell)>> m_designs;

};