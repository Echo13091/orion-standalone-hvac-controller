#pragma once

#include <Arduino.h>

enum class HvacMode {
  Standby,
  Cool,
  Heat,
  FanOnly,
  Fault,
};

struct RelayState {
  bool coolStage1 = false;
  bool coolStage2 = false;
  bool heatStage1 = false;
  bool heatStage2 = false;
  bool fan = false;
};
