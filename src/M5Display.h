#ifndef _M5DISPLAY_H_
  #define _M5DISPLAY_H_

  #define LGFX_USE_V1
  #define LGFX_M5STICK
  #define LGFX_M5STACK_CORE2
  #define LGFX_M5STICK_C
  #define LGFX_M5STACK_COREINK
  #define LGFX_M5PAPER
  #include "utility/Config.h"
  #include <SD.h>
  #include <SPIFFS.h>
  #include <LGFX_TFT_eSPI.h>
  #include <vector>

  struct DisplayState {
    const lgfx::IFont *gfxFont;
    lgfx::TextStyle style;
    lgfx::FontMetrics metrics;
    int32_t cursor_x, cursor_y, padX;
  };

  class M5Display : public LGFX {
    public:
      static M5Display* instance;
      M5Display();

      void progressBar(int x, int y, int w, int h, uint8_t val);

    // Saves and restores font properties, datum, cursor and colors so
    // code can be non-invasive. Just make sure that every push is also
    // popped when you're done to prevent stack from growing.
    //
    // (User code can never do this completely because the gfxFont
    // class variable of TFT_eSPI is protected.)
    #define M5DISPLAY_HAS_PUSH_POP
     public:
      void pushState();
      void popState();

     private:
      std::vector<DisplayState> _displayStateStack;

    #ifdef M5Stack_M5Core2

      #ifdef TFT_eSPI_TOUCH_EMULATION
        // Emulates the TFT_eSPI touch interface using M5.Touch
       public:
        uint8_t getTouchRaw(uint16_t *x, uint16_t *y);
        uint16_t getTouchRawZ(void);
        void convertRawXY(uint16_t *x, uint16_t *y);
        uint8_t getTouch(uint16_t *x, uint16_t *y, uint16_t threshold = 600);
        void calibrateTouch(uint16_t *data, uint32_t color_fg, uint32_t color_bg,
                            uint8_t size);
        void setTouch(uint16_t *data);
      #endif /* TFT_eSPI_TOUCH_EMULATION */

    #endif /* M5Stack_M5Core2 */
};
#endif /* _M5DISPLAY_H_ */
