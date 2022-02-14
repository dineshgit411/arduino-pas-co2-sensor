#include <Arduino.h>
#include <pas-co2-serial-ino.hpp>

#define I2C_FREQ_HZ 400000  

/**
 * Create CO2 object. Unless otherwise specified,
 * using the Wire interface
 */
PASCO2SerialIno cotwo;

uint8_t prodId, revId;
Error_t err;

void setup()
{
  Serial.begin(9600);
  delay(500);
  Serial.println("serial initialized");

  /* Initialize the i2c serial interface used by the sensor */
  Wire.begin();
  Wire.setClock(I2C_FREQ_HZ);

  err = cotwo.begin();
  if(XENSIV_PASCO2_OK != err)
  {
    Serial.print("initialization error: ");
    Serial.println(err);
  }

  err = cotwo.getDeviceID(prodId, revId);
  if(XENSIV_PASCO2_OK != err)
  {
    Serial.print("error: ");
    Serial.println(err);
  }

  Serial.print("product id  : ");
  Serial.println(prodId);
  Serial.print("revision id : ");
  Serial.println(revId);
}

void loop()
{

}