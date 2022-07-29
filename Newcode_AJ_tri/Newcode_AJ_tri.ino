
#include<Wire.h>

const int MPU_addr = 0x68;
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;

int minVal = 265;
int maxVal = 402;

double x, y, z;

void setup() {
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0);
  
  Wire.endTransmission(true);
  Serial.begin(9600);
}
void loop() {
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr, 14, true);
  AcX = Wire.read() << 8 | Wire.read();
  AcY = Wire.read() << 8 | Wire.read();
  AcZ = Wire.read() << 8 | Wire.read();
  int xAng = map(AcX, minVal, maxVal, -90, 90);
  int yAng = map(AcY, minVal, maxVal, -90, 90);
  int zAng = map(AcZ, minVal, maxVal, -90, 90);

  x = RAD_TO_DEG * (atan2(-yAng, -zAng) + PI);
  y = RAD_TO_DEG * (atan2(-xAng, -zAng) + PI);
  z = RAD_TO_DEG * (atan2(-yAng, -xAng) + PI);

  /*
  Serial.print("Angle Z: "); Serial.println(z);
  Serial.print("Angle X: "); Serial.println(x);
  Serial.print("Angle Y: "); Serial.println(y);
  Serial.println("<=========================================================>");
  */

  int lower_angle = 300;
  int highier_angle = 50 ;
  Serial.println(x);
  if ( x > lower_angle){
    Serial.println("Wrong, Too Low");
  }
  else if ( x < highier_angle){
        Serial.println("Wrong, Too high");
  }

  else{
    Serial.println(" perfect ");
  }
 
}