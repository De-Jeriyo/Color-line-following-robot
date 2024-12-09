

#include <U8g2lib.h>



U8G2_SH1106_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);


String ip = "190.23.3.333";


void setup(void) {

  u8g2.begin();  
}

void loop(void) {
  u8g2.firstPage();
  do {
    u8g2.setBitmapMode(1);
    u8g2.setFontMode(1);
    u8g2.setFont(u8g2_font_DigitalDisco_tf);
    u8g2.drawStr(6, 16, "Wi-Fi Connected!");
    u8g2.drawLine(0,23,128,23);
    u8g2.drawLine(10,25,118,25);
    u8g2.setFont(u8g2_font_t0_22b_me);//u8g2_font_tenthinguys_tf);
    u8g2.drawStr(0, 49, "IP- ");
    u8g2.setFont(u8g2_font_timB14_tn);//u8g2_font_DigitalDisco_tn);
    u8g2.setCursor(33, 49);
    u8g2.print(ip);
  } while ( u8g2.nextPage() );
  //delay(1000);
}

