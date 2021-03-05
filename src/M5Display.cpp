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
