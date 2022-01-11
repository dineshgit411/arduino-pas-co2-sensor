#include <Arduino.h>
#include <pas-co2-serial-ino.hpp>

/**
 * Select the serial interface:
 * - I2C (TwoWire)
 * - UART (HardwareSerial)
 * By default the I2C interfaces is selected. 
 * Compile with -DINO_HW_SERIAL to select the UART interface.
 */
#ifdef INO_HW_SERIAL
HardwareSerial * bus = (HardwareSerial*) PASCO2_INO_UART;
#else
TwoWire * bus = (TwoWire*) PASCO2_INO_I2C;
#endif

PASCO2SerialIno cotwo(bus);

ABOC_t   aboc     = XENSIV_PASCO2_BOC_CFG_AUTOMATIC;
int16_t  abocRef  = 100;
uint16_t pressRef = 700;
Error_t  err;

void setup()
{
  Serial.begin(9600);
  delay(500);
  Serial.println("pas co2 serial initialized");

  err = cotwo.begin();
  if(XENSIV_PASCO2_OK != err)
  {
    Serial.print("initialization error: ");
    Serial.println(err);
  }

  /* Set automatic base line compensation */
  err = cotwo.setABOC(aboc, abocRef);
  if(XENSIV_PASCO2_OK != err)
  {
    Serial.print("error: ");
    Serial.println(err);
  }

  /* Set pressure reference */
  Error_t err = cotwo.setPressRef(pressRef);
  if(XENSIV_PASCO2_OK != err)
  {
    Serial.print("error: ");
    Serial.println(err);
  }

  Serial.println("sensor calibration completed");
}

void loop()
{

}