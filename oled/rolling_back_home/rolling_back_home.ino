#include <U8g2lib.h>



U8G2_SH1106_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);


u8g2_uint_t offset;			// current offset for the scrolling text
u8g2_uint_t width;			// pixel width of the scrolling text (must be lesser than 128 unless U8G2_16BIT is defined
const char *text = "Rollin' Back Home                    ";	// scroll this text from right to left

static const unsigned char image_FaceCharging_29x14_bits[] U8X8_PROGMEM = {0x40,0x00,0x00,0x02,0x60,0x00,0x00,0x03,0x30,0x00,0x80,0x01,0x18,0x00,0xc0,0x00,0xfc,0x00,0xe0,0x07,0xfc,0x00,0xe0,0x07,0x60,0x00,0x00,0x03,0x30,0x00,0x80,0x01,0x18,0x00,0xc0,0x00,0x08,0x00,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x04,0x04,0x00,0x00,0x08,0x02,0x00,0x00,0xf0,0x01,0x00};

void setup(void) {	

  u8g2.begin();  
  
  u8g2.setFont(u8g2_font_tenthinnerguys_t_all);	// set the target font to calculate the pixel width
  width = u8g2.getUTF8Width(text);		// calculate the pixel width of the text
  
  u8g2.setFontMode(0);		// enable transparent mode, which is faster
}


void loop(void) {
  u8g2_uint_t x;
  
  u8g2.firstPage();
  do {
  
    // draw the scrolling text at current offset
    x = offset;
    u8g2.setFont(u8g2_font_tenthinnerguys_t_all);		// set the target font
    do {								// repeated drawing of the scrolling text...
      u8g2.drawUTF8(x, 13, text);			// draw the scolling text
      x += width;						// add the pixel width of the scrolling text
    } while( x < u8g2.getDisplayWidth() );		// draw again until the complete display is filled
    u8g2.setFont(u8g2_font_prospero_bold_nbp_tf );
    u8g2.drawStr(15, 56, "Home Sweet Home");
    u8g2.drawPixel(4, 47);
    u8g2.drawPixel(6, 49);
    u8g2.drawPixel(4, 55);
    u8g2.drawPixel(5, 48);
    u8g2.drawPixel(3, 54);
    u8g2.drawPixel(1, 51);
    u8g2.drawPixel(1, 52);
    u8g2.drawPixel(1, 50);
    u8g2.drawPixel(2, 49);
    u8g2.drawPixel(3, 48);
    u8g2.drawPixel(2, 53);
    u8g2.drawPixel(7, 50);
    u8g2.drawPixel(11, 48);
    u8g2.drawPixel(9, 48);
    u8g2.drawPixel(8, 49);
    u8g2.drawPixel(10, 47);
    u8g2.drawPixel(13, 51);
    u8g2.drawPixel(13, 52);
    u8g2.drawPixel(13, 50);
    u8g2.drawPixel(12, 49);
    u8g2.drawPixel(12, 53);
    u8g2.drawPixel(7, 58);
    u8g2.drawPixel(6, 57);
    u8g2.drawPixel(5, 56);
    u8g2.drawPixel(9, 56);
    u8g2.drawPixel(10, 55);
    u8g2.drawPixel(11, 54);
    u8g2.drawPixel(8, 57);
    u8g2.drawPixel(114, 50);
    u8g2.drawPixel(114, 51);
    u8g2.drawPixel(114, 52);
    u8g2.drawPixel(115, 53);
    u8g2.drawPixel(116, 54);
    u8g2.drawPixel(117, 55);
    u8g2.drawPixel(118, 56);
    u8g2.drawPixel(119, 57);
    u8g2.drawPixel(120, 58);
    u8g2.drawPixel(121, 57);
    u8g2.drawPixel(122, 56);
    u8g2.drawPixel(123, 55);
    u8g2.drawPixel(124, 54);
    u8g2.drawPixel(125, 53);
    u8g2.drawPixel(126, 52);
    u8g2.drawPixel(126, 51);
    u8g2.drawPixel(126, 50);
    u8g2.drawPixel(119, 49);
    u8g2.drawPixel(120, 50);
    u8g2.drawPixel(121, 49);
    u8g2.drawPixel(122, 48);
    u8g2.drawPixel(123, 47);
    u8g2.drawPixel(124, 48);
    u8g2.drawPixel(125, 49);
    u8g2.drawPixel(116, 48);
    u8g2.drawPixel(117, 47);
    u8g2.drawPixel(118, 48);
    u8g2.drawPixel(115, 49);
    u8g2.drawXBMP( 45, 25, 29, 14, image_FaceCharging_29x14_bits);
    
  } while ( u8g2.nextPage() );
  
  offset-=5;							// scroll by one pixel
  if ( (u8g2_uint_t)offset < (u8g2_uint_t)-width )	
    offset = 0;							// start over again
    
  delay(10);							// do some small delay
}

