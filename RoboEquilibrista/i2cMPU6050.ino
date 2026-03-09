/* Copyright (C) 2012 Kristian Lauszus, TKJ Electronics. All rights reserved.

 This software may be distributed and modified under the terms of the GNU
 General Public License version 2 (GPL2) as published by the Free Software
 Foundation and appearing in the file GPL2.TXT included in the packaging of
 this file. Please note that GPL2 Section 2[b] requires that all works based
 on this software must also be made publicly available under the terms of
 the GPL2 ("Copyleft").

 Contact information
 -------------------

 Kristian Lauszus, TKJ Electronics
 Web      :  http://www.tkjelectronics.com
 e-mail   :  kristianl@tkjelectronics.com
 */

const uint8_t IMUAddress = 0x68; // Endereço padrão da MPU6050
const uint16_t I2C_TIMEOUT =
    1000; // Used to check for errors in I2C communication

uint8_t i2cWrite(uint8_t registerAddress, uint8_t data, bool sendStop) {
  return i2cWrite(registerAddress, &data, 1, sendStop); // Returns 0 on success
}

uint8_t i2cWrite(uint8_t registerAddress, uint8_t *data, uint8_t length,
                 bool sendStop) {
  Wire.beginTransmission(IMUAddress);
  Wire.write(registerAddress);
  Wire.write(data, length);
  uint8_t rcode = Wire.endTransmission(sendStop); // Returns 0 on success
  if (rcode) {
    Serial.print(F("i2cWrite failed: "));
    Serial.println(rcode);
  }
  return rcode;
}

uint8_t i2cRead(uint8_t registerAddress, uint8_t *data, uint8_t nbytes) {
  uint32_t timeOutTimer;
  Wire.beginTransmission(IMUAddress);
  Wire.write(registerAddress);
  uint8_t rcode = Wire.endTransmission(false); // Don't release the bus
  if (rcode) {
    Serial.print(F("i2cRead failed: "));
    Serial.println(rcode);
    return rcode;
  }

  // Request data from MPU
  uint8_t bytesReceived = Wire.requestFrom(IMUAddress, nbytes, (uint8_t)true);

  if (bytesReceived < nbytes) {
    // Wait slightly if data is slow
    timeOutTimer = micros();
    while (((micros() - timeOutTimer) < I2C_TIMEOUT) &&
           (Wire.available() < nbytes))
      ;
  }

  if (Wire.available() >= nbytes) {
    for (uint8_t i = 0; i < nbytes; i++) {
      data[i] = Wire.read();
    }
    return 0; // Success
  } else {
    Serial.println(F("i2cRead timeout or insufficient data"));
    return 5; // Error
  }
}
