#include <Wire.h>

int ret;
void i2cWrite(byte addr, byte reg, byte volt, byte ctrl) {
  byte val = (volt << 2) | ctrl;
  Wire.beginTransmission(addr);
  Wire.write(reg);
  Wire.write(val);  
  Wire.endTransmission(true);  

  Serial.print("addr[");
  Serial.print(addr, HEX);
  Serial.print("] = ");
  Serial.print(val, HEX);
  Serial.println("");
}

byte i2cRead(byte addr, byte reg) {
  Wire.beginTransmission(addr);
  Wire.write(reg);
  ret = Wire.endTransmission(true);  

  Wire.requestFrom((unsigned int)addr, 1);
  while (0 < Wire.available()) {
    ret = Wire.read();
  }

  Serial.print(ret, DEC);  
  Serial.print(" = addr[");
  Serial.print(addr, HEX);
  Serial.print("]");
  Serial.println("");

  return ret;
}

#define ADDR_MOTOR1   (0x60)
#define REG_CONTROL   (0x00)
#define REG_ERROR     (0x01)

#define MOTOR_CONTROL_STOP  (0)
#define MOTOR_CONTROL_CW    (1)
#define MOTOR_CONTROL_CCW   (2)
#define MOTOR_CONTROL_BRAKE (3)

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Wire.begin();
  i2cWrite(ADDR_MOTOR1, REG_ERROR, 0x20, 0);
  i2cWrite(ADDR_MOTOR1, REG_CONTROL, 0x26, MOTOR_CONTROL_CW);
}

void loop() {
  delay(1000);
  i2cWrite(ADDR_MOTOR1, REG_ERROR, 0x20, 0);
  i2cWrite(ADDR_MOTOR1, REG_CONTROL, 0x26, MOTOR_CONTROL_CW);
  //i2cRead(0x60, REG_CONTROL);
  //i2cRead(0x60, REG_ERROR);
}

