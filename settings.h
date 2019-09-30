                           /////////////////////////////////////////////////////////////////
                          //                           Settings                          //
                         /////////////////////////////////////////////////////////////////
 


/***************************************************
 *        Blynk Virtual Pin Assignment
 **************************************************/
 
#define vPIN_VOLTAGE                V0
#define vPIN_CURRENT_USAGE          V1
#define vPIN_ACTIVE_POWER           V2
#define vPIN_ACTIVE_ENERGY          V3
#define vPIN_FREQUENCY              V4
#define vPIN_POWER_FACTOR           V5
#define vPIN_OVER_POWER_ALARM       V6


/***************************************************
 *       Blynk Settings 
 **************************************************/
 
#define AUTH "Your Blynk Auth Token" //You should get Auth Token in the Blynk App. 


/***************************************************
 *        WiFi Settings
 **************************************************/
  
#define WIFI_SSID "Your WiFi Network Name"
#define WIFI_PASS "Your Wifi Password"

/***************************************************
 *        Server Settings
 **************************************************/
      
#define OTA_HOSTNAME "PZEM-004v3"


// Remove/comment-out below 2 lines when use Blynk hosted server
 
#define USE_LOCAL_SERVER       //Use local Blynk Server - comment-out if use Blynk hosted cloud service
#define SERVER "xxx.xxx.xx.xxx" //comment-out if use Blynk hosted cloud service

#define PORT 8080
