/*

  PrintProgmem.ino
  
  AVR Architecture:
  Use the (Arduino compatible) u8g2 function "print"  to draw a string,
  which is located in PROGMEM.
  For string constants use the F() macro, but this example use global 
  strings instead.

  Universal 8bit Graphics Library (https://github.com/olikraus/u8g2/)

  Copyright (c) 2016, olikraus@gmail.com
  All rights reserved.

  Redistribution and use in source and binary forms, with or without modification, 
  are permitted provided that the following conditions are met:

  * Redistributions of source code must retain the above copyright notice, this list 
    of conditions and the following disclaimer.
    
  * Redistributions in binary form must reproduce the above copyright notice, this 
    list of conditions and the following disclaimer in the documentation and/or other 
    materials provided with the distribution.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND 
  CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, 
  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
  NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; 
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, 
  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF 
  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.  

*/

/*
	This demo can be displayed normally on OLED with a resolution of 128x64, 
	while it will be displayed incomplete in the 128x32 OLED.	
*/

#include <Arduino.h>
#include <U8g2lib.h>

#include <SPI.h>
#include <Wire.h>

/*
  U8g2lib Example Overview:
    Frame Buffer Examples: clearBuffer/sendBuffer. Fast, but may not work with all Arduino boards because of RAM consumption
    Page Buffer Examples: firstPage/nextPage. Less RAM usage, should work with all Arduino boards.
    U8x8 Text Only Example: No RAM usage, direct communication with display controller. No graphics, 8x8 Text only.
    
  This is a page buffer example.    
*/

// U8g2 Contructor List (Picture Loop Page Buffer)
// The complete list is available here: https://github.com/olikraus/u8g2/wiki/u8g2setupcpp
// Please update the pin numbers according to your setup. Use U8X8_PIN_NONE if the reset pin is not connected


/*
	Please use the corresponding instantiation-function when using the display 
	with different resolutions and communication ways.
*/
//  M0/ESP32/ESP8266/mega2560/Uno/Leonardo
//U8G2_SSD1306_128X64_NONAME_1_4W_HW_SPI u8g2(U8G2_R0, /* cs=*/ 10, /* dc=*/ 9);
//U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
//U8G2_SSD1306_128X32_UNIVISION_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);   



// End of constructor list


void setup(void) {
  u8g2.begin();
}

const char s[] PROGMEM = "Progmem";
const char s1[] PROGMEM  = "ABC" ;
const char s2[] PROGMEM  = "DEF" ;
const char s3[] PROGMEM  = "GHI" ;
const char s4[] PROGMEM  = "JKL" ;

const char *a[] = { s1, s2, s3, s4 };

int i = 0;

void loop(void) {
  u8g2.setFont(u8g2_font_ncenB14_tr);
  u8g2.firstPage();
  do {
  
    u8g2.setCursor(0, 20);
    u8g2.print((class __FlashStringHelper *)s);   // print a sting, located in PROGMEM
    
    u8g2.setCursor(0, 40);
    u8g2.print((class __FlashStringHelper *)a[i]);  // print a sting (PROGMEM) via RAM array.
    
  } while ( u8g2.nextPage() );
  delay(1000);
  i++;
  if ( i >= 4 )
    i = 0;
}

