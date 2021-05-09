#include <Adafruit_GFX.h>  
#include <Adafruit_ST7735.h>  display



#define TFT_CS     10
#define TFT_RST    9  
#define TFT_DC     8


Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

#include <Fonts/FreeSerif18pt7b.h>  // Add a custom font

int Variable1; 

void setup() 
{
  tft.initR(INITR_BLACKTAB);  // Initialize a ST7735S chip, black tab

  tft.fillScreen(ST7735_BLACK); 

  tft.setTextWrap(true); 

 
  tft.setFont(&FreeSerif18pt7b);  // Set a custom font
  tft.setTextSize(0);  
  tft.setCursor(0, 30);  // Set position (x,y)
  tft.setTextColor(ST7735_WHITE);  // Set color of text. We are using custom font so there is no background color supported
  tft.println("Happy");  // Print a text or value 
  tft.println("mother's");  // Print a text or value
  tft.println("day!!!");

  
  tft.setTextColor(ST7735_WHITE);  // Set color of text. We are using custom font so there is no background color supported
  tft.drawLine(0, 125, 127, 125, ST7735_CYAN);  // Draw line (x0,y0,x1,y1,color)
  tft.setCursor(0, 130);  // Set position (x,y)
  tft.println("From your son who    loves you so much!");  // Print a text or value

}  

void loop() {}  
