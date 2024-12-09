#include <U8g2lib.h>

/*#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif*/


U8G2_SH1106_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

static const unsigned char image_Layer_27_bits[] U8X8_PROGMEM = {0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x03,0x00,0x06,0x00,0x0c,0x00,0x18,0x00,0x10,0x00,0x70,0x00,0xc0,0x03,0x00,0x06};
static const unsigned char image_Layer_28_bits[] U8X8_PROGMEM = {0x00,0x04,0x00,0x04,0x00,0x04,0x00,0x04,0x00,0x04,0x00,0x06,0x00,0x03,0x80,0x01,0xc0,0x00,0x40,0x00,0x70,0x00,0x1c,0x00,0x06,0x00,0x03,0x00};


void setup(void) {

  
  u8g2.begin();  
}

void loop(void) {
  u8g2.firstPage();
  do {
    u8g2.setBitmapMode(1);
u8g2.setFontMode(1);
u8g2.setFont(u8g2_font_lubR14_te);//u8g2_font_profont22_tr);
u8g2.drawStr(13, 37, "Auston");
u8g2.drawFrame(91, 11, 2, 24);
u8g2.drawFrame(92, 36, 26, 2);
u8g2.drawLine(94, 11, 117, 34);
u8g2.drawLine(95, 11, 118, 34);
u8g2.drawLine(95, 16, 95, 32);
u8g2.drawLine(96, 32, 96, 17);
u8g2.drawLine(97, 32, 97, 18);
u8g2.drawLine(98, 32, 98, 19);
u8g2.drawLine(99, 32, 99, 20);
u8g2.drawLine(100, 32, 100, 21);
u8g2.drawLine(101, 32, 101, 22);
u8g2.drawLine(103, 32, 103, 24);
u8g2.drawLine(102, 32, 102, 23);
u8g2.drawLine(105, 32, 105, 26);
u8g2.drawLine(104, 32, 104, 25);
u8g2.drawLine(107, 32, 107, 28);
u8g2.drawLine(106, 32, 106, 27);
u8g2.drawLine(108, 32, 108, 29);
u8g2.drawLine(109, 32, 109, 30);
u8g2.drawLine(110, 32, 110, 31);
u8g2.drawPixel(111, 32);
} while ( u8g2.nextPage() );
delay(2000);

 u8g2.firstPage();
  do {
u8g2.setBitmapMode(1);
u8g2.setFontMode(1);
u8g2.drawFrame(37, 13, 2, 24);
u8g2.drawFrame(38, 38, 26, 2);
u8g2.drawLine(40, 13, 63, 36);
u8g2.drawLine(41, 13, 64, 36);
u8g2.drawLine(41, 18, 41, 34);
u8g2.drawLine(42, 34, 42, 19);
u8g2.drawLine(43, 34, 43, 20);
u8g2.drawLine(44, 34, 44, 21);
u8g2.drawLine(45, 34, 45, 22);
u8g2.drawLine(46, 34, 46, 23);
u8g2.drawLine(47, 34, 47, 24);
u8g2.drawLine(49, 34, 49, 26);
u8g2.drawLine(48, 34, 48, 25);
u8g2.drawLine(51, 34, 51, 28);
u8g2.drawLine(50, 34, 50, 27);
u8g2.drawLine(53, 34, 53, 30);
u8g2.drawLine(52, 34, 52, 29);
u8g2.drawLine(54, 34, 54, 31);
u8g2.drawLine(55, 34, 55, 32);
u8g2.drawLine(56, 34, 56, 33);
u8g2.drawPixel(46, 29);
u8g2.drawFrame(71, 14, 20, 9);
u8g2.drawBox(76, 17, 2, 2);
u8g2.drawBox(84, 17, 2, 2);
u8g2.drawBox(80, 12, 2, 2);
u8g2.drawLine(70, 26, 91, 26);
u8g2.drawXBMP( 70, 27, 11, 13, image_Layer_27_bits);
u8g2.drawXBMP( 81, 26, 11, 14, image_Layer_28_bits);
u8g2.setFont(u8g2_font_press_mel_tr);//(u8g2_font_cube_mel_tr);
u8g2.drawStr(48, 56, "A-bot");
 } while ( u8g2.nextPage() );
  delay(2000);

}

