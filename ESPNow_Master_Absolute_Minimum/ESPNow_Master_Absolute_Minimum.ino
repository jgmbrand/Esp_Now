/* Espressif SDK is written in C, not C++ */
extern "C" {
  #include <espnow.h>
}

#define WIFI_CHANNEL 1
#define SECONDS 1000000L
#define SLEEP_TIME 10      // seconds

//MAC Address remote ESP_Now server (slave) and data to be send
static uint8_t peerMac[]  = {0x22, 0x22, 0x22, 0x22, 0x22, 0x22};
static uint8_t peerData[] = {0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55};
static int i;

//callback after send
static void send_cb(uint8_t* mac, uint8_t sendStatus) {
  Serial.print(sendStatus?" -> FAILED\n":" -> SUCCES\n");
}

void setup() {
  Serial.begin(115200);
  Serial.printf("\nESP_Now Master : %s\n",__FILE__);

  if (esp_now_init() != 0) ESP.restart();

  //OK... now set role, add peers and register callback
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_add_peer(peerMac, ESP_NOW_ROLE_SLAVE, WIFI_CHANNEL, NULL, 0);
  esp_now_register_send_cb(send_cb);
  
  //and send some data
  Serial.printf("sending : ");for(i=0;i<sizeof(peerData);Serial.printf("%02X ",peerData[i++]));
  esp_now_send(NULL, peerData, sizeof(peerData)); // NULL means send to all peers

  //just sleep a bit
  delay(5); //allow some time for the callback function
  ESP.deepSleep(SLEEP_TIME * SECONDS);
}

void loop() {}
