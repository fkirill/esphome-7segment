#include "display3461bs.h"
#include "esphome/core/log.h"
#include "esphome/core/helpers.h"
#include "esphome/core/hal.h"

namespace esphome {
namespace display3461bs {

static const char *const TAG = "display3461bs";

float Display3461BSComponent::get_setup_priority() const { return setup_priority::PROCESSOR; }
void Display3461BSComponent::setup() {
  ESP_LOGCONFIG(TAG, "Setting up Display3461BS...");
  this->pin_a->setup();
  this->pin_b->setup();
  this->pin_c->setup();
  this->pin_d->setup();
  this->pin_e->setup();
  this->pin_f->setup();
  this->pin_g->setup();
  this->pin_dp->setup();
  this->pin_d1->setup();
  this->pin_d2->setup();
  this->pin_d3->setup();
  this->pin_d4->setup();
  display();
}

void Display3461BSComponent::dump_config() {
  ESP_LOGCONFIG(TAG, "3461BS:");
  LOG_PIN("  Pin A: ", this->pin_a);
  LOG_PIN("  Pin B: ", this->pin_b);
  LOG_PIN("  Pin C: ", this->pin_c);
  LOG_PIN("  Pin D: ", this->pin_d);
  LOG_PIN("  Pin E: ", this->pin_e);
  LOG_PIN("  Pin F: ", this->pin_f);
  LOG_PIN("  Pin G: ", this->pin_g);
  LOG_PIN("  Pin DP: ", this->pin_dp);
  LOG_PIN("  Pin D1: ", this->pin_d1);
  LOG_PIN("  Pin D2: ", this->pin_d2);
  LOG_PIN("  Pin D3: ", this->pin_d3);
  LOG_PIN("  Pin D4: ", this->pin_d4);
  ESP_LOGCONFIG(TAG, "  Delay: %u", this->del);
  ESP_LOGCONFIG(TAG, "  Common anode: %u", this->common_anode);
  ESP_LOGCONFIG(TAG, "  Common segments: %u", this->segments);
  LOG_UPDATE_INTERVAL(this);
}

void Display3461BSComponent::display() {
  pickDigit(0);
  setDigitSegments((segments & 0xff000000) >> 24);
  delay(del);//delay 5ms

  pickDigit(1);
  setDigitSegments((segments & 0xff0000) >> 16);
  delay(del);

  pickDigit(2);
  setDigitSegments((segments & 0xff00) >> 8);
  delay(del);

  pickDigit(3);//Light up 7-segment display d4
  setDigitSegments(segments & 0xff);
  delay(del);//delay 5ms
}

void Display3461BSComponent::pickDigit(uint8_t digit) {
  pin_d1->digital_write(digit == 0);
  pin_d2->digital_write(digit == 1);
  pin_d3->digital_write(digit == 2);
  pin_d4->digital_write(digit == 3);
}

void Display3461BSComponent::setDigitSegments(uint8_t segs) {
  pin_a->digital_write((segs &  0b10000000) == 0);
  pin_b->digital_write((segs &  0b01000000) == 0);
  pin_c->digital_write((segs &  0b00100000) == 0);
  pin_d->digital_write((segs &  0b00010000) == 0);
  pin_e->digital_write((segs &  0b00001000) == 0);
  pin_f->digital_write((segs &  0b00000100) == 0);
  pin_g->digital_write((segs &  0b00000010) == 0);
  pin_dp->digital_write((segs & 0b00000001) == 0);
}

void Display3461BSComponent::update() {
  auto now_tick = millis() / tick;
  if (now_tick != current_tick) {
    current_tick = now_tick;
    segments = calculateSegments(now_tick);
  }
  this->display();
}

#define A 0x80
#define B 0x40
#define C 0x20
#define D 0x10
#define E 0x08
#define F 0x04
#define G 0x02
#define DP 0x01

uint32_t pattern1_segments(uint32_t now_tick) {
    auto tick = now_tick % 12;
    uint32_t d1 = 0;
    uint32_t d2 = 0;
    uint32_t d3 = 0;
    uint32_t d4 = 0;

    switch(tick) {
      case 0: d1 |= A; break;
      case 1: d2 |= A; break;
      case 2: d3 |= A; break;
      case 3: d4 |= A; break;
      case 4: d4 |= B; break;
      case 5: d4 |= C; break;
      case 6: d4 |= D; break;
      case 7: d3 |= D; break;
      case 8: d2 |= D; break;
      case 9: d1 |= D; break;
      case 10: d1 |= E; break;
      case 11: d1 |= F; break;
    }
  return (d1 << 24) + (d2 << 16) + (d3 << 8) + d4;
}

uint32_t pattern2_segments(uint32_t now_tick) {
    auto tick = now_tick % 14;
    uint32_t d1 = 0;
    uint32_t d2 = 0;
    uint32_t d3 = 0;
    uint32_t d4 = 0;

    switch(tick) {
      case 0: d1 |= E + F; break;
      case 1: d1 |= B + C; break;
      case 2: d2 |= E + F; break;
      case 3: d2 |= B + C; break;
      case 4: d3 |= E + F; break;
      case 5: d3 |= B + C; break;
      case 6: d4 |= E + F; break;
      case 7: d4 |= B + C; break;
      case 8: d4 |= E + F; break;
      case 9: d3 |= B + C; break;
      case 10: d3 |= E + F; break;
      case 11: d2 |= B + C; break;
      case 12: d2 |= E + F; break;
      case 13: d1 |= B + C; break;
    }
  return (d1 << 24) + (d2 << 16) + (d3 << 8) + d4;
}

uint32_t pattern3_segments(uint32_t now_tick) {
    auto tick = now_tick % 4;
    uint32_t d1 = 0;
    uint32_t d2 = 0;
    uint32_t d3 = 0;
    uint32_t d4 = 0;

    switch(tick) {
      case 0: d1 |= A; d2 |= A; d3 |= A; d4 |= A; break;
      case 1: d1 |= G; d2 |= G; d3 |= G; d4 |= G; break;
      case 2: d1 |= D; d2 |= D; d3 |= D; d4 |= D; break;
      case 3: d1 |= G; d2 |= G; d3 |= G; d4 |= G; break;
    }
  return (d1 << 24) + (d2 << 16) + (d3 << 8) + d4;
}

uint32_t pattern4_segments(uint32_t now_tick) {
    auto tick = now_tick % 6;
    uint32_t d1 = 0;
    uint32_t d2 = 0;
    uint32_t d3 = 0;
    uint32_t d4 = 0;

    switch(tick) {
      case 0: d1 |= A + B + C + D + E + F; break;
      case 1: d2 |= A + B + C + D + E + F; break;
      case 2: d3 |= A + B + C + D + E + F; break;
      case 3: d4 |= A + B + C + D + E + F; break;
      case 4: d3 |= A + B + C + D + E + F; break;
      case 5: d2 |= A + B + C + D + E + F; break;
    }
  return (d1 << 24) + (d2 << 16) + (d3 << 8) + d4;
}

uint32_t Display3461BSComponent::calculateSegments(uint32_t now_tick) {
  uint32_t segments = 0;

  if (pattern1) {
    segments |= pattern1_segments(now_tick);
  }
  if (pattern2) {
    segments |= pattern2_segments(now_tick);
  }
  if (pattern3) {
    segments |= pattern3_segments(now_tick);
  }
  if (pattern4) {
    segments |= pattern4_segments(now_tick);
  }
  if ((now_tick & 0x1) == 0) {
    if (progress1) {
      segments |= 0x01000000;
    }
    if (progress2) {
      segments |= 0x00010000;
    }
    if (progress3) {
      segments |= 0x00000100;
    }
    if (progress4) {
      segments |= 0x00000001;
    }
  }

  return segments;
}

}  // namespace max7219
}  // namespace esphome
