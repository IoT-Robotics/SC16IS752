# I2C_RECEIVE_TIMEOUT
Input is completed with the timeout.   
Timeout is 500 mill sec.   
Connect RX of ChannelA and other Arduno TX at 9600 bps.   
Connect RX of ChannelB and other Arduno TX at 115200 bps.   
Connect Gnd and other Arduno Gnd.   

__Connections should be as short as possible__

![atmega-i2c-receive-timeout](https://user-images.githubusercontent.com/6020549/147806101-1faa907f-0941-4a0b-91f9-32cef46b53a2.jpg)

# Channel baudrate
You can specify different baudrates for channel A and channel B

# Sketch of the other side
```
#define baudrate 9600L

void setup() {
  Serial.begin(baudrate);
}

void loop() {
  char buf[64];
  sprintf(buf,"Hello Wold, Baudrate is %ld", baudrate);
  Serial.print(buf);
  delay(1000);
}
```

