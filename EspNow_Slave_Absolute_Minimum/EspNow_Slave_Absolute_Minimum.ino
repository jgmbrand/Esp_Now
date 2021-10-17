//Probably the absolute minimum code needed for an espnow slave 
//Expects a master to send some bytes to mac : 22:22:22:22:22:22

extern "C" {
  #include <user_interface.h>
  #include <espnow.h>
}

//the Master sends to mac : 22:22:22:22:22:22 
uint8_t newmac[6] = {0x22,0x22,0x22,0x22,0x22,0x22};

void recv_cb(uint8_t *mac, uint8_t *Data, uint8_t len) {
  int i;
  Serial.print("Received from mac : ");
  for (i=0;i<5;Serial.printf("%02x:",mac[i++]));Serial.printf("%02x > ",mac[i]);
  for (i=0;i<len;Serial.printf("%02x ",Data[i++]));Serial.printf("(%i bytes)\n",len);
}

void setup() {
  Serial.begin(115200); 
  Serial.printf("\nESP_Now Slave : %s\n",__FILE__);
  
  //change the macaddress(will be reset on poweron/reset)
  wifi_set_macaddr(0,newmac);
  
  if (esp_now_init() != 0) ESP.restart();
  
  //OK... now set role and register callback
  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(recv_cb);
}

void loop() {}
