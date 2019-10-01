                           /////////////////////////////////////////////////////////////////
                          //                           Settings                          //
                         /////////////////////////////////////////////////////////////////
 



/***************************************************
 *        NodeMCU Pin Assignment
 **************************************************/

#define RX_PIN_NODEMCU     D5        //Nodemcu pin, used has RX pin
#define TX_PIN_NODEMCU     D6       //Nodemcu pin, used has TX pin

/***************************************************
 *        PZEM address value assignment 
 **************************************************/

 #define PZEM_SLAVE_1_ADDRESS     0x01     //make sure you assign address to pzem first before you use
 #define PZEM_SLAVE_2_ADDRESS     0x02
 
/***************************************************
 *        Blynk Virtual Pin Assignment
 **************************************************/
 
#define vPIN_VOLTAGE_1                V11
#define vPIN_CURRENT_USAGE_1          V12
#define vPIN_ACTIVE_POWER_1           V13
#define vPIN_ACTIVE_ENERGY_1          V14
#define vPIN_FREQUENCY_1              V15
#define vPIN_POWER_FACTOR_1           V16
#define vPIN_OVER_POWER_ALARM_1       V17

#define vPIN_VOLTAGE_2                V21
#define vPIN_CURRENT_USAGE_2          V22
#define vPIN_ACTIVE_POWER_2           V23
#define vPIN_ACTIVE_ENERGY_2          V24
#define vPIN_FREQUENCY_2              V25
#define vPIN_POWER_FACTOR_2           V26
#define vPIN_OVER_POWER_ALARM_2       V27

/***************************************************
 *       Blynk Settings 
 **************************************************/
 
#define AUTH "Your Blynk Auth Token"                //You should get Auth Token in the Blynk App. 


/***************************************************
 *        WiFi Settings
 **************************************************/
  
#define WIFI_SSID "Your WiFi Network Name"
#define WIFI_PASS "Your Wifi Password"

/***************************************************
 *        Server Settings
 **************************************************/
      
#define OTA_HOSTNAME "PZEM-004T v3.0 Multiple Slave"


// Remove/comment-out below 2 lines when use Blynk hosted server
 
#define USE_LOCAL_SERVER                           //Use local Blynk Server - comment-out if use Blynk hosted cloud service
#define SERVER "xxx.xxx.xx.xxx"                   //comment-out if use Blynk hosted cloud service

#define PORT 8080
