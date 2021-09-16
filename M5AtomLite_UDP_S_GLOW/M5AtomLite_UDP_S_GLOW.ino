
#include "M5Atom.h"

CRGB dispColor(uint8_t r, uint8_t g, uint8_t b) {
  return (CRGB)((r << 16) | (g << 8) | b);
}


void setup()
{ 
  M5.begin(true, false, true);
  delay(10);  //delay10ms.
  M5.dis.drawpix(0, dispColor(255,0,0));
  Serial.begin(115200);
  init_BLE("GlowSDK");
  delay(100);
  init_udp();
  delay(100);
  M5.dis.drawpix(0, dispColor(0,0,255));
}

void loop()
{
  int func;
  int group;
  int id;
  unsigned int comm;

  if(receive_udp(&func,&group,&id,&comm)){
    if(comm>0x7fff)comm=0;
    serial_display(func,group,id,comm);
    sendGlowData(func,group,id,comm);
    M5.dis.drawpix(0, dispColor(0,255,255));
  }
  if(receive_serial(&func,&group,&id,&comm)){
    if(comm>0x7fff)comm=0;
    serial_display(func,group,id,comm);
    sendGlowData(func,group,id,comm);
    M5.dis.drawpix(0, dispColor(255,0,0));
  }

  if (M5.Btn.wasPressed()){ 
    sendGlowData(0,group,id,0x0);
    M5.dis.drawpix(0, dispColor(0,0,255));
  }
  M5.update();
  delay(100);
}

void serial_display(int func,int group,int id,int comm){
  Serial.print("function = ");
  Serial.println(func);
  Serial.print("group    = ");
  Serial.println(group);
  Serial.print("id       = ");
  Serial.println(id);
  Serial.print("command  = ");
  Serial.println(comm);
}
