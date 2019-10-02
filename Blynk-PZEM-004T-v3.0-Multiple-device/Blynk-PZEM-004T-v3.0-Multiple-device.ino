/*
   Blynk PZEM 004T v3.0 Multiple Device (Here 2 Pzem) Connection Program

   Source: https://github.com/pkarun/Blynk-PZEM-004T-v3.0-Multiple-device
   https://github.com/pkarun/Blynk-PZEM-004T-v3.0

   Reference:

    https://community.blynk.cc/t/pzem-004t-v3-0-and-nodemcu-wemos-mini-running-on-blynk-how-to-procedure/39338
    https://asndiy.wordpress.com/2019/03/02/pzem-016-nodemcu-thingspeak/
    http://evertdekker.com/?p=1307
    https://didactronica.com/medidas-electricas-en-corriente-alterna-con-arduino-y-un-solo-dispositivo-pzem-004t/
    http://solar4living.com/pzem-arduino-modbus.htm
    http://www.desert-home.com/2018/07/pzem-016-another-chinese-power-monitor.html
    https://www.youtube.com/watch?v=gJRhfs6A1SA

   Wiring:

   PZEM 004T v3.0 to NodeMCU
   5v to vin
   RX to D6 (TX Pin)
   TX to D5 (RX Pin)
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
SoftwareSerial pzemSerial(RX_PIN_NODEMCU, TX_PIN_NODEMCU); // (RX,TX) NodeMCU connect to (TX,RX) of PZEM 
//SoftwareSerial pzem(D7,D8);  // (RX,TX) connect to TX,RX of PZEM
#include <ModbusMaster.h>

/*
   This is the address of Pzem devices on the network. Each pzem device has to set unique
   address when we are working with muliple pzem device (multiple modbus devices/multiple slaves)
   You can use the changeAddress(OldAddress, Newaddress) function below in the code to assign new
   address to each pzem device first time.
   
*/
static uint8_t pzemSlave1Addr = PZEM_SLAVE_1_ADDRESS; 
static uint8_t pzemSlave2Addr = PZEM_SLAVE_2_ADDRESS;


//ModbusMaster node;

ModbusMaster node1;
ModbusMaster node2;

BlynkTimer timer;

double voltage_usage_1 = 0; 
double current_usage_1 = 0;
double active_power_1 = 0;
double active_energy_1 = 0;
double frequency_1 = 0;
double power_factor_1 = 0; 
double over_power_alarm_1 = 0;
 
double voltage_usage_2 = 0;
double current_usage_2 = 0;
double active_power_2 = 0;
double active_energy_2 = 0;
double frequency_2 = 0;
double power_factor_2 = 0; 
double over_power_alarm_2 = 0;


void setup() {
  Serial.begin(115200);

  pzemSerial.begin(9600);

  // start Modbus/RS-485 serial communication
  node1.begin(pzemSlave1Addr, pzemSerial);
  node2.begin(pzemSlave2Addr, pzemSerial);


  /* changeAddress(OldAddress, Newaddress)
     By Uncomment the function in the below line you can change the slave address from one of the nodes (pzem device),
     only need to be done ones. Preverable do this only with 1 slave in the network.
     If you forgot or don't know the new address anymore, you can use the broadcast address 0XF8 as OldAddress to change the slave address.
     Use this with one slave ONLY in the network.
     This is the first step you have to do when connecting muliple pzem devices. If you haven't set the pzem address, then this program won't
     works.

  */

  //changeAddress(0x01, 0x02);  //uncomment to set pzem address


  //resetEnergy(0x01);
  /* By Uncomment the function in the above line you can reset the energy counter (Wh) back to zero from one of the slaves.
      //resetEnergy(pzemSlaveAddr);
  */



#if defined(USE_LOCAL_SERVER)
  Blynk.begin(AUTH, WIFI_SSID, WIFI_PASS, SERVER, PORT);
#else
  Blynk.begin(AUTH, WIFI_SSID, WIFI_PASS);
#endif
  ArduinoOTA.setHostname(OTA_HOSTNAME);
  ArduinoOTA.begin();


  timer.setInterval(10000L, sendtoBlynk); // send values blynk server every 10 sec

  //delay(1000);

}



//Here we are sending data to blynk 
void sendtoBlynk() {
          
  Blynk.virtualWrite(vPIN_VOLTAGE_1,               voltage_usage_1);
  Blynk.virtualWrite(vPIN_CURRENT_USAGE_1,         current_usage_1);
  Blynk.virtualWrite(vPIN_ACTIVE_POWER_1,          active_power_1);
  Blynk.virtualWrite(vPIN_ACTIVE_ENERGY_1,         active_energy_1);
  Blynk.virtualWrite(vPIN_FREQUENCY_1,             frequency_1);
  Blynk.virtualWrite(vPIN_POWER_FACTOR_1,          power_factor_1);
  Blynk.virtualWrite(vPIN_OVER_POWER_ALARM_1,      over_power_alarm_1);

  Blynk.virtualWrite(vPIN_VOLTAGE_2,               voltage_usage_2);
  Blynk.virtualWrite(vPIN_CURRENT_USAGE_2,         current_usage_2);
  Blynk.virtualWrite(vPIN_ACTIVE_POWER_2,          active_power_2);
  Blynk.virtualWrite(vPIN_ACTIVE_ENERGY_2,         active_energy_2);
  Blynk.virtualWrite(vPIN_FREQUENCY_2,             frequency_2);
  Blynk.virtualWrite(vPIN_POWER_FACTOR_2,          power_factor_2);
  Blynk.virtualWrite(vPIN_OVER_POWER_ALARM_2,      over_power_alarm_2);  
}


void pzemdevice1()
{
  // PZEM Device 1 data fetching
  Serial.println("===================================================="); 
  Serial.println("Now checking Modbus 1");
  uint8_t result1;

  ESP.wdtDisable();     //disable watchdog during modbus read or else ESP crashes when no slave connected                                               
  result1 = node1.readInputRegisters(0x0000, 10);
  ESP.wdtEnable(1);    //enable watchdog during modbus read  
  
  if (result1 == node1.ku8MBSuccess)
  {
    voltage_usage_1      = (node1.getResponseBuffer(0x00) / 10.0f);
    current_usage_1      = (node1.getResponseBuffer(0x01) / 1000.000f);
    active_power_1       = (node1.getResponseBuffer(0x03) / 10.0f);
    active_energy_1      = (node1.getResponseBuffer(0x05) / 1000.0f);
    frequency_1          = (node1.getResponseBuffer(0x07) / 10.0f);
    power_factor_1       = (node1.getResponseBuffer(0x08) / 100.0f);
    over_power_alarm_1   = (node1.getResponseBuffer(0x09));

    Serial.println("Modbus 1 Data");
    Serial.print("VOLTAGE:           ");   Serial.println(voltage_usage_1);   // V
    Serial.print("CURRENT_USAGE:     ");   Serial.println(current_usage_1, 3);  //  A
    Serial.print("ACTIVE_POWER:      ");   Serial.println(active_power_1);   //  W
    Serial.print("ACTIVE_ENERGY:     ");   Serial.println(active_energy_1, 3);  // kWh
    Serial.print("FREQUENCY:         ");   Serial.println(frequency_1);    // Hz
    Serial.print("POWER_FACTOR:      ");   Serial.println(power_factor_1);
    Serial.print("OVER_POWER_ALARM:  ");   Serial.println(over_power_alarm_1, 0);
    Serial.println("====================================================");
  }

  else {
    Serial.println("Failed to read modbus 1");
   
  }
}

 void pzemdevice2()
 {
   
  // PZEM Device 2 data fetching
  Serial.println("===================================================="); 
  Serial.println("Now checking Modbus 2");
  uint8_t result2;
  
  ESP.wdtDisable();
  result2 = node2.readInputRegisters(0x0000, 10);
  ESP.wdtEnable(1);
  
  if (result2 == node2.ku8MBSuccess)
  {
    voltage_usage_2      = (node2.getResponseBuffer(0x00) / 10.0f);
    current_usage_2      = (node2.getResponseBuffer(0x01) / 1000.000f);
    active_power_2       = (node2.getResponseBuffer(0x03) / 10.0f);
    active_energy_2      = (node2.getResponseBuffer(0x05) / 1000.0f);
    frequency_2          = (node2.getResponseBuffer(0x07) / 10.0f);
    power_factor_2       = (node2.getResponseBuffer(0x08) / 100.0f);
    over_power_alarm_2   = (node2.getResponseBuffer(0x09));

    Serial.println("Modbus 2 Data");
    Serial.print("VOLTAGE:           ");   Serial.println(voltage_usage_2);   // V
    Serial.print("CURRENT_USAGE:     ");   Serial.println(current_usage_2, 3);  //  A
    Serial.print("ACTIVE_POWER:      ");   Serial.println(active_power_2);   //  W
    Serial.print("ACTIVE_ENERGY:     ");   Serial.println(active_energy_2, 3);  // kWh
    Serial.print("FREQUENCY:         ");   Serial.println(frequency_2);    // Hz
    Serial.print("POWER_FACTOR:      ");   Serial.println(power_factor_2);
    Serial.print("OVER_POWER_ALARM:  ");   Serial.println(over_power_alarm_2, 0);
    Serial.println("====================================================");

    
  }

  else {
    Serial.println("Failed to read modbus 2");
    //delay(6000);

  }
}



void resetEnergy(uint8_t slaveAddr) {
  //The command to reset the slave's energy is (total 4 bytes):
  //Slave address + 0x42 + CRC check high byte + CRC check low byte.
  uint16_t u16CRC = 0xFFFF;
  static uint8_t resetCommand = 0x42;
  u16CRC = crc16_update(u16CRC, slaveAddr);
  u16CRC = crc16_update(u16CRC, resetCommand);
  Serial.println("Resetting Energy");
  pzemSerial.write(slaveAddr);
  pzemSerial.write(resetCommand);
  pzemSerial.write(lowByte(u16CRC));
  pzemSerial.write(highByte(u16CRC));
  delay(1000);
}


//function to change/assign pzem address

void changeAddress(uint8_t OldslaveAddr, uint8_t NewslaveAddr)
{
  static uint8_t SlaveParameter = 0x06;
  static uint16_t registerAddress = 0x0002; // Register address to be changed
  uint16_t u16CRC = 0xFFFF;
  u16CRC = crc16_update(u16CRC, OldslaveAddr);
  u16CRC = crc16_update(u16CRC, SlaveParameter);
  u16CRC = crc16_update(u16CRC, highByte(registerAddress));
  u16CRC = crc16_update(u16CRC, lowByte(registerAddress));
  u16CRC = crc16_update(u16CRC, highByte(NewslaveAddr));
  u16CRC = crc16_update(u16CRC, lowByte(NewslaveAddr));

  Serial.println("Changing Slave Address");

  pzemSerial.write(OldslaveAddr);
  pzemSerial.write(SlaveParameter);
  pzemSerial.write(highByte(registerAddress));
  pzemSerial.write(lowByte(registerAddress));
  pzemSerial.write(highByte(NewslaveAddr));
  pzemSerial.write(lowByte(NewslaveAddr));
  pzemSerial.write(lowByte(u16CRC));
  pzemSerial.write(highByte(u16CRC));
  delay(1000);
}


void loop() {
  Blynk.run();
  ArduinoOTA.handle();
  timer.run();
  pzemdevice1();
  pzemdevice2();
  delay(1000);
}
