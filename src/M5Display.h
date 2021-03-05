#ifndef _M5DISPLAY_H_
  #define _M5DISPLAY_H_

  #define LGFX_M5STACK_CORE2
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

};
#endif /* _M5DISPLAY_H_ */
