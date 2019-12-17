#include <sevenSeg.h>
#include <Button.h>

#define SEGA 11
#define SEGB 12
#define SEGC 6
#define SEGD 7
#define SEGE 8
#define SEGF 10
#define SEGG 9
#define SEGDP 5
#define POWER 4
sevenSeg disp(SEGA,SEGB,SEGC,SEGD,SEGE,SEGF,SEGG,SEGDP,CA);
Button S1(2, 2000);
Button S2(3, 2000);

bool powerOn=true, blinkOn=false;
#define TIMEOUT 500
int timeOut=TIMEOUT;

SIGNAL(TIMER2_COMPA_vect) 
{
  togglePower();
}
void dispOn(){
    powerOn=true;
    digitalWrite(POWER, powerOn);
}
void toggleBlink(){
  blinkOn = !blinkOn;
  if(blinkOn){
    TIMSK2 |= _BV(OCIE2A); //Bittitason matikkaa. Otetaan ajastin käyttöön
  }else{
    TIMSK2 &= ~_BV(OCIE2A);//Bittitason matikkaa. Otetaan ajastin pois käytöstä
    dispOn();
  }
}
void togglePower(){
  if(timeOut++ == TIMEOUT){
    timeOut=0;
    powerOn = !powerOn;
    digitalWrite(POWER, powerOn);
  }
}
void setup() {
  pinMode(POWER, OUTPUT);
  digitalWrite(POWER, powerOn);
  disp.blank(); //
  OCR2A=0x01; //Yhden millisekunnin välein tapahtuva ajastin-keskeytys.
}
int count=0; // Globaali muuttuja lasketun arvon ylläpitoon
void loop(){
  if(S1.pressed() && count < 9){
    count++;
  }
  if(S2.pressed() && count > 0){
    count--;
  }
  if(S1.kept()){
    toggleBlink();
  }
  if(S2.kept()){
    count=0;
  }
  disp.showNum(count);
}
