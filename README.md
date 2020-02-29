# Esp_Now
# Some exercises with the Espressif Esp_Now  library
Have been playing around with some Espressif ESP8266's and Esp-Now.  
Created some very basic examples.  
No need for knowledge of mac-addresses. 

EspNowSendRecv.ino    : Send-Master.  
EspNowEchoServer.ino  : Echo-Slave.
Send-Master : broadcasts (MAC:0xFFFFFFFFFFFF) some simple data.  
Echo-Slave  : receives this data and prints it.  
Echo-Slave  : sends the data back to the Send-Master.  
Send-Master : receives this response data and prints it.  
Send-Master : copies the mac-address of the responding Echo-Slave.  
Send-Master : continues sending data to the Echo-Slave's mac-address.  
Echo-Slave  : continues responding to the Send-Master's data  
