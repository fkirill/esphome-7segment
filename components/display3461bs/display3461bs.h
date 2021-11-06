#pragma once

#include "esphome/core/component.h"
#include "esphome/core/hal.h"

namespace esphome {
namespace display3461bs {

class Display3461BSComponent;

class Display3461BSComponent : public PollingComponent {
 public:
  void setup() override;
  void dump_config() override;
  void update() override;
  float get_setup_priority() const override;
  void display();
  void set_pin_a(GPIOPin *pin) { pin_a = pin; }
  void set_pin_b(GPIOPin *pin) { pin_b = pin; }
  void set_pin_c(GPIOPin *pin) { pin_c = pin; }
  void set_pin_d(GPIOPin *pin) { pin_d = pin; }
  void set_pin_e(GPIOPin *pin) { pin_e = pin; }
  void set_pin_f(GPIOPin *pin) { pin_f = pin; }
  void set_pin_g(GPIOPin *pin) { pin_g = pin; }
  void set_pin_dp(GPIOPin *pin) { pin_dp = pin; }
  void set_pin_d1(GPIOPin *pin) { pin_d1 = pin; }
  void set_pin_d2(GPIOPin *pin) { pin_d2 = pin; }
  void set_pin_d3(GPIOPin *pin) { pin_d3 = pin; }
  void set_pin_d4(GPIOPin *pin) { pin_d4 = pin; }
  void set_common_anode(bool common_anode) { this->common_anode = common_anode; }
  void set_delay(uint16_t delay) { this->del = delay; }
  bool is_pattern1() { return pattern1; }
  void set_pattern1(bool pattern) { pattern1 = pattern; }
  bool is_pattern2() { return pattern2; }
  void set_pattern2(bool pattern) { pattern2 = pattern; }
  bool is_pattern3() { return pattern3; }
  void set_pattern3(bool pattern) { pattern3 = pattern; }
  bool is_pattern4() { return pattern4; }
  void set_pattern4(bool pattern) { pattern4 = pattern; }
  void set_tick(uint16_t tick) { this->tick = tick; }
  bool is_progress1() { return progress1; }
  void set_progress1(bool progress) { progress1 = progress; }
  bool is_progress2() { return progress2; }
  void set_progress2(bool progress) { progress2 = progress; }
  bool is_progress3() { return progress3; }
  void set_progress3(bool progress) { progress3 = progress; }
  bool is_progress4() { return progress4; }
  void set_progress4(bool progress) { progress4 = progress; }

 private:
  GPIOPin* pin_a;
  GPIOPin* pin_b;
  GPIOPin* pin_c;
  GPIOPin* pin_d;
  GPIOPin* pin_e;
  GPIOPin* pin_f;
  GPIOPin* pin_g;
  GPIOPin* pin_dp;
  GPIOPin* pin_d1;
  GPIOPin* pin_d2;
  GPIOPin* pin_d3;
  GPIOPin* pin_d4;
  bool common_anode;
  uint16_t del;
  bool pattern1;
  bool pattern2;
  bool pattern3;
  bool pattern4;
  bool progress1;
  bool progress2;
  bool progress3;
  bool progress4;
  uint32_t segments;
  uint16_t tick;
  uint64_t current_tick;

  void pickDigit(uint8_t digit);
  void setDigitSegments(uint8_t segs);
  uint32_t calculateSegments(uint32_t now_tick);
};

}  // namespace max7219
}  // namespace esphome
