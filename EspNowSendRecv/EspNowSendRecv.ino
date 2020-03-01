extern "C" {
  //location : C:\Users\<user>\AppData\Local\Arduino15\packages\esp8266\hardware\esp8266\2.6.3\tools\sdk\include
  #include <espnow.h>
}

//set the data to be send ( 0 is end-of-Cstring for printability) 
uint8_t data[] = {'H','e','l','l','o',' ','W','o','r','l','d','!',0};
 
//set initial remote mac-address (broadcast address)
//will be replaced by echoserver mac-address in receive-callback function recv_cb
uint8_t remoteMac[] = { 0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF };

//replace mac-address on first receive-callback only  
bool broadcast = true;

//----------------------------------------------------------------------------------
void send_cb(uint8_t* mac, uint8_t sendStatus) {
  Serial.printf("send_cb\r\n - send to MAC %0X:%0X:%0X:%0X:%0X:%0X  done, status = %s\r\n",mac[0],mac[1],mac[2],mac[3],mac[4],mac[5], sendStatus?"FAIL":"SUCCES");  
}

//----------------------------------------------------------------------------------
void recv_cb(uint8_t *mac, uint8_t *data, uint8_t len) {

  //show sender's mac-address, the received data and the number of bytes received
  Serial.printf("recv_cb\r\n - received from MAC %0X:%0X:%0X:%0X:%0X:%0X  : %s (%d bytes)\r\n\r\n",mac[0],mac[1],mac[2],mac[3],mac[4],mac[5],(char *)data,len); 

  if (broadcast){//only first time, not really necessary
    broadcast = false;
    //replace broadcast mac-address with echoserver mac-address
    memcpy(remoteMac,mac,6);
  } 
  
  //some direct visual feedback
  toggleLed();
}

//----------------------------------------------------------------------------------
void setup() {
  //init serial port and print some sketch info
  Serial.begin(74880);
  Serial.println("\n\n\n"+String(__FILE__)+"\n"+"Created : "+String(__DATE__)+" "+String(__TIME__)+"\n");

  //initialise esp_now 
  if (esp_now_init() != 0) {
    Serial.println("*** ESP_Now init failed");
    ESP.restart();
  }
  Serial.println("ESP_Now init succes\r\n");

  //set role (??? looks like any role will work ???)
  esp_now_set_self_role(ESP_NOW_ROLE_COMBO);     //CONTROLLER);//SLAVE);//COMBO);
  //register callbacks
  esp_now_register_recv_cb(recv_cb);
  esp_now_register_send_cb(send_cb);
}

//----------------------------------------------------------------------------------
void loop() {
  //send data periodically
  esp_now_send(remoteMac, data, sizeof(data));
  //for better visibility
  data[0] ^= 0x11;
  delay(2000);
}

//----------------------------------------------------------------------------------
void toggleLed(){
  pinMode(LED_BUILTIN,OUTPUT); 
  digitalWrite(LED_BUILTIN,!digitalRead(LED_BUILTIN));
}
