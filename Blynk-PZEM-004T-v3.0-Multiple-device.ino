/*
   Blynk PZEM 004T v3.0 Multiple Device Connection Program 

   Source: https://github.com/pkarun/Blynk-PZEM-004T-v3.0-Multiple-device
   https://github.com/pkarun/Blynk-PZEM-004T-v3.0
   
   Reference: https://community.blynk.cc/t/pzem-004t-v3-0-and-nodemcu-wemos-mini-running-on-blynk-how-to-procedure/39338

   Wiring:
   
   PZEM 004T v3.0 to NodeMCU
   5v to vin
   RX to D6
   TX to D5
   GND to GND
   
   
*/

//#include "settings.h" //Make sure you UNCOMMENT this before you use. 
#include "my_settings.h" //This is my personal settings. You can remove this line or comment-out when you are using.

#include <ArduinoOTA.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>
#include <ModbusMaster.h>
#include <ESP8266WiFi.h>


#include <SoftwareSerial.h>  //  ( NODEMCU ESP8266 )
SoftwareSerial pzem(D5, D6); // (RX,TX) connect to TX,RX of PZEM for NodeMCU  
//SoftwareSerial pzem(D7,D8);  // (RX,TX) connect to TX,RX of PZEM
#include <ModbusMaster.h>
ModbusMaster node;

BlynkTimer timer;

double voltage_usage, current_usage, active_power, active_energy, frequency, power_factor, over_power_alarm; 

uint8_t result;  uint16_t data[6];


void setup() {
  Serial.begin(115200);
  Serial.println("Start serial");
  pzem.begin(9600);
  Serial.println("Start PZEM serial");
  node.begin(1, pzem);
  Serial.println("Start PZEM"); // 1 = ID MODBUS

#if defined(USE_LOCAL_SERVER) 
  Blynk.begin(AUTH, WIFI_SSID, WIFI_PASS, SERVER, PORT);
#else
  Blynk.begin(AUTH, WIFI_SSID, WIFI_PASS);
#endif
  ArduinoOTA.setHostname(OTA_HOSTNAME);
  ArduinoOTA.begin();


timer.setInterval(10000L, sendtoBlynk); // send values blynk server every 10 sec


}

void sendtoBlynk() {
  Blynk.virtualWrite(vPIN_VOLTAGE,               voltage_usage);
  Blynk.virtualWrite(vPIN_CURRENT_USAGE,         current_usage);
  Blynk.virtualWrite(vPIN_ACTIVE_POWER,          active_power);
  Blynk.virtualWrite(vPIN_ACTIVE_ENERGY,         active_energy);
  Blynk.virtualWrite(vPIN_FREQUENCY,             frequency);
  Blynk.virtualWrite(vPIN_POWER_FACTOR,          power_factor);
  Blynk.virtualWrite(vPIN_OVER_POWER_ALARM,      over_power_alarm);
}


void pzemdata(){

    result = node.readInputRegisters(0x0000, 10);
    
    if (result == node.ku8MBSuccess)  
    {
    voltage_usage      = (node.getResponseBuffer(0x00) / 10.0f);
    current_usage      = (node.getResponseBuffer(0x01) / 1000.000f);
    active_power       = (node.getResponseBuffer(0x03) / 10.0f);
    active_energy      = (node.getResponseBuffer(0x05) / 1000.0f);
    frequency          = (node.getResponseBuffer(0x07) / 10.0f);
    power_factor       = (node.getResponseBuffer(0x08) / 100.0f);
    over_power_alarm   = (node.getResponseBuffer(0x09));
    }

  Serial.print("VOLTAGE:           ");   Serial.println(voltage_usage);   // V
  Serial.print("CURRENT_USAGE:     ");   Serial.println(current_usage, 3);  //  A
  Serial.print("ACTIVE_POWER:      ");   Serial.println(active_power);   //  W
  Serial.print("ACTIVE_ENERGY:     ");   Serial.println(active_energy, 3);  // kWh
  Serial.print("FREQUENCY:         ");   Serial.println(frequency);    // Hz
  Serial.print("POWER_FACTOR:      ");   Serial.println(power_factor);
  Serial.print("OVER_POWER_ALARM:  ");   Serial.println(over_power_alarm, 0);
  Serial.println("====================================================");
}

void loop() {
  Blynk.run();
  ArduinoOTA.handle();
  timer.run();
  pzemdata();

  delay(1000);
}
