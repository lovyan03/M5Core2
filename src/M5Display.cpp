#include "M5Display.h"

#ifdef M5Stack_M5Core2
#include <M5Touch.h>
#endif /* M5Stack_M5Core2 */


// So we can use this instance without including all of M5Core2 / M5Stack
M5Display* M5Display::instance;

M5Display::M5Display() : LGFX() {
  if (!instance) instance = this;
}

void M5Display::progressBar(int x, int y, int w, int h, uint8_t val) {
  drawRect(x, y, w, h, 0x09F1);
  fillRect(x + 1, y + 1, w * (((float)val) / 100.0), h - 1, 0x09F1);
}

// Saves and restores font properties, datum, cursor, colors

void M5Display::pushState() {
  DisplayState s;
  s.gfxFont = _font;
  s.style = _text_style;
  s.metrics = _font_metrics;
  s.cursor_x = _cursor_x;
  s.cursor_y = _cursor_y;
  s.padX = _padding_x;
  _displayStateStack.push_back(s);
}

void M5Display::popState() {
  if (_displayStateStack.empty()) return;
  DisplayState s = _displayStateStack.back();
  _displayStateStack.pop_back();
  _font = s.gfxFont;
  _text_style = s.style;
  _font_metrics = s.metrics;
  _padding_x = s.padX;
  _cursor_x = s.cursor_x;
  _cursor_y = s.cursor_y;
}

#ifdef M5Stack_M5Core2

#ifdef TFT_eSPI_TOUCH_EMULATION

// Emulates the native (resistive) TFT_eSPI touch interface using M5.Touch

uint8_t M5Display::getTouchRaw(uint16_t *x, uint16_t *y) {
  return getTouch(x, y);
}

uint16_t M5Display::getTouchRawZ(void) {
  return (TOUCH->ispressed()) ? 1000 : 0;
}

void M5Display::convertRawXY(uint16_t *x, uint16_t *y) { return; }

uint8_t M5Display::getTouch(uint16_t *x, uint16_t *y,
                            uint16_t threshold /* = 600 */) {
  TOUCH->read();
  if (TOUCH->points) {
    *x = TOUCH->point[0].x;
    *y = TOUCH->point[0].y;
    return true;
  }
  return false;
}

void M5Display::calibrateTouch(uint16_t *data, uint32_t color_fg,
                               uint32_t color_bg, uint8_t size) {
  return;
}

void M5Display::setTouch(uint16_t *data) { return; }

#endif /* TFT_eSPI_TOUCH_EMULATION */

#endif /* M5Stack_M5Core2 */
