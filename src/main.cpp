/*
 An example digital clock using a TFT LCD screen to show the time.
 Demonstrates use of the font printing routines. (Time updates but date does not.)

 It uses the time of compile/upload to set the time
 For a more accurate clock, it would be better to use the RTClib library.
 But this is just a demo...

 Make sure all the display driver and pin comnenctions are correct by
 editting the User_Setup.h file in the TFT_eSPI library folder.

 #########################################################################
 ###### DON'T FORGET TO UPDATE THE User_Setup.h FILE IN THE LIBRARY ######
 #########################################################################

 Based on clock sketch by Gilchrist 6/2/2014 1.0

A few colour codes:

code	color
0x0000	Black
0xFFFF	White
0xBDF7	Light Gray
0x7BEF	Dark Gray
0xF800	Red
0xFFE0	Yellow
0xFBE0	Orange
0x79E0	Brown
0x7E0	Green
0x7FF	Cyan
0x1F	Blue
0xF81F	Pink

 */

#include <M5Stack.h>
#include "Aruduino_Timer.h"

#define TFT_GREY 0x5AEB

Aruduino_Timer timer; 
TaskHandle_t timer_task;

//static uint8_t conv2d(const char* p); // Forward declaration needed for IDE 1.6.x



byte omm = 99, oss = 99;
byte xcolon = 0, xsecs = 0;
unsigned int colour = 0;

void draw_lcd(int min, int sec) {
  int xpos = 0;
  int ypos = 85; // Top left corner ot clock text, about half way down
  int ysecs = ypos + 24;
  
  if (omm != min) { // Redraw hours and minutes time every minute
    omm = min;
    
    if (min < 10) xpos += M5.Lcd.drawChar('0', xpos, ypos, 8); // Add minutes leading zero
    xpos += M5.Lcd.drawNumber(min, xpos, ypos, 8);             // Draw minutes
    xsecs = xpos; // Sae seconds 'x' position for later display updates
  }
  if (oss != sec) { // Redraw seconds time every second
    oss = sec;
    xpos = xsecs;

    if (sec % 2) { // Flash the colons on/off
      M5.Lcd.setTextColor(0x39C4, TFT_BLACK);        // Set colour to grey to dim colon
      xpos += M5.Lcd.drawChar(':', xsecs, ysecs, 6); // Seconds colon
      M5.Lcd.setTextColor(TFT_YELLOW, TFT_BLACK);    // Set colour back to yellow
    }
    else {
      xpos += M5.Lcd.drawChar(':', xsecs, ysecs, 6); // Seconds colon
    }

    //Draw seconds
    if (sec < 10) xpos += M5.Lcd.drawChar('0', xpos, ysecs, 6); // Add leading zero
    M5.Lcd.drawNumber(sec, xpos, ysecs, 6);                     // Draw seconds
  }
}

void setup(void) {
  //Serial.begin(115200);
  M5.begin();
  // M5.Lcd.setRotation(1);
  M5.Lcd.fillScreen(TFT_BLACK);

  M5.Lcd.setTextSize(1);
  M5.Lcd.setTextColor(TFT_YELLOW, TFT_BLACK); 
}

void loop() {
  timer.timer_run();
  M5.update();
  if (M5.BtnA.wasReleased()) {
    timer.plus_min();
    delay(5);
  }
  if (M5.BtnB.wasReleased()) {
    timer.plus_sec();
    delay(5);
  }
  if (M5.BtnC.wasReleased()) {
    timer.status_change();
    delay(5);
  }

  // Update digital time
  int min = timer.get_min();
  int sec = timer.get_sec();

  draw_lcd(min, sec);
  if(timer.get_status() == TIMER_STATUS_FINISH) {
    M5.Lcd.fillTriangle(random(M5.Lcd.width()-1), random(M5.Lcd.height()-1), random(M5.Lcd.width()-1), random(M5.Lcd.height()-1), random(M5.Lcd.width()-1), random(M5.Lcd.height()-1), random(0xfffe));
  }
}


// Function to extract numbers from compile time string

/*
static uint8_t conv2d(const char* p) {
  uint8_t v = 0;
  if ('0' <= *p && *p <= '9')
    v = *p - '0';
  return 10 * v + *++p - '0';
}
*/


