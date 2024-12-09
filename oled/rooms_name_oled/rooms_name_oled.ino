#include <U8g2lib.h>

/*#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif*/


U8G2_SH1106_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

static const unsigned char image_ButtonRight_4x7_bits[] U8X8_PROGMEM = {0x01,0x03,0x07,0x0f,0x07,0x03,0x01};
static const unsigned char image_ButtonLeft_4x7_bits[] U8X8_PROGMEM = {0x08,0x0c,0x0e,0x0f,0x0e,0x0c,0x08};

void setup(void) {

  u8g2.begin();  
}

void loop(void) {
  u8g2.firstPage();
  do {
 
u8g2.setBitmapMode(1);
u8g2.setFontMode(1);
u8g2.setFont( u8g2_font_HelvetiPixelOutline_tr);
u8g2.drawStr(15, 45, "Classroom-1");
u8g2.setFont(u8g2_font_sticker100complete_tr);//u8g2_font_greenbloodserif2_tr);//u8g2_font_cupcakemetoyourleader_tr);//u8g2_font_jinxedwizards_tr);
u8g2.drawStr(20, 19, "Duty Call!");
u8g2.drawXBMP(5, 37, 4, 7, image_ButtonRight_4x7_bits);
u8g2.drawXBMP( 120, 37, 4, 7, image_ButtonLeft_4x7_bits);
} while ( u8g2.nextPage() );
delay(1000);
u8g2.firstPage();
  do {
 
u8g2.setBitmapMode(1);
u8g2.setFontMode(1);
u8g2.setFont(u8g2_font_sticker100complete_tr);
u8g2.drawStr(15, 45, "Classroom-1");
u8g2.setFont(u8g2_font_HelvetiPixelOutline_tr);//u8g2_font_greenbloodserif2_tr);//u8g2_font_cupcakemetoyourleader_tr);//u8g2_font_jinxedwizards_tr);
u8g2.drawStr(25, 19, "Rollin' To");
u8g2.drawXBMP(5, 37, 4, 7, image_ButtonRight_4x7_bits);
u8g2.drawXBMP( 120, 37, 4, 7, image_ButtonLeft_4x7_bits);
} while ( u8g2.nextPage() );
delay(2000);


u8g2.firstPage();
  do {
 
u8g2.setBitmapMode(1);
u8g2.setFontMode(1);
u8g2.setFont( u8g2_font_jinxedwizards_tr);
u8g2.drawStr(20, 45, "Classroom-2");
u8g2.setFont(u8g2_font_moosenooks_tr);//u8g2_font_greenbloodserif2_tr);//u8g2_font_cupcakemetoyourleader_tr);//u8g2_font_jinxedwizards_tr);
u8g2.drawStr(25, 19, "Duty Call!");
u8g2.drawXBMP(5, 37, 4, 7, image_ButtonRight_4x7_bits);
u8g2.drawXBMP( 120, 37, 4, 7, image_ButtonLeft_4x7_bits);
} while ( u8g2.nextPage() );
delay(1000);

u8g2.firstPage();
  do {
u8g2.setBitmapMode(1);
u8g2.setFontMode(1);
u8g2.setFont(u8g2_font_moosenooks_tr);
u8g2.drawStr(13, 45, "Classroom-2");
u8g2.setFont(u8g2_font_jinxedwizards_tr);//u8g2_font_greenbloodserif2_tr);//u8g2_font_cupcakemetoyourleader_tr);//u8g2_font_jinxedwizards_tr);
u8g2.drawStr(25, 19, "Rollin' To");
u8g2.drawXBMP(5, 37, 4, 7, image_ButtonRight_4x7_bits);
u8g2.drawXBMP( 120, 37, 4, 7, image_ButtonLeft_4x7_bits);
} while ( u8g2.nextPage() );
delay(2000);

u8g2.firstPage();
  do {
 
u8g2.setBitmapMode(1);
u8g2.setFontMode(1);
u8g2.setFont(u8g2_font_cube_mel_tr);
u8g2.drawStr(30, 45, "Labroom");
u8g2.setFont(u8g2_font_press_mel_tr);
u8g2.drawStr(28, 19, "Duty Call!");
u8g2.drawXBMP(15, 37, 4, 7, image_ButtonRight_4x7_bits);
u8g2.drawXBMP( 110, 37, 4, 7, image_ButtonLeft_4x7_bits);
} while ( u8g2.nextPage() );
delay(1000);

u8g2.firstPage();
  do {
u8g2.setBitmapMode(1);
u8g2.setFontMode(1);
u8g2.setFont(u8g2_font_press_mel_tr);
u8g2.drawStr(30, 45, "Labroom");
u8g2.setFont(u8g2_font_cube_mel_tr);
u8g2.drawStr(20, 19, "Rollin' To");
u8g2.drawXBMP(15, 37, 4, 7, image_ButtonRight_4x7_bits);
u8g2.drawXBMP( 110, 37, 4, 7, image_ButtonLeft_4x7_bits);
} while ( u8g2.nextPage() );
delay(2000);
}

