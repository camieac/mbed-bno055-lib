/**
* @file main.cpp
* @author Cameron A. Craig
* @date 14 Oct 2017
* @copyright 2017 Cameron A. Craig
* @brief Drives ESCs for Triforce fighting robot based on PWM signals from receiver.
*/

/* Includes */
#include "mbed.h"
#include "rtos.h"

#include "i2c_device.h"
#include "drv_bno055.h"
#include "return_codes.h"

#define BNO055_SDA_PIN p9
#define BNO055_SCL_PIN p9

Serial *serial = new Serial(USBTX, USBRX);

int bno055_wait_until_ready(i2c_device_t *bno055, I2C *i2c) {
  unsigned bno055_init_attempts = 0;
  while (bno055_init(bno055, i2c, BNO055_SDA_PIN, BNO055_SCL_PIN) != RET_OK) {
    bno055_init_attempts++;
    if(bno055_init_attempts > 5) {
      return RET_ERROR;
    }
  }
  return RET_OK;
}

/** Main
 *
 * Main Loop
 */
int main() {
  // Configure serial connection to a PC (for debug)
  serial->baud(115200);


  // Print initial messsage inidicating start of new process
  serial->puts("BNO055 Test\r\n");
  i2c_device_t *bno055;
  I2C i2c(p9, p10);

  serial->printf("init(): BNO055\r\n");
  if (!bno055_wait_until_ready(bno055, &i2c)){
    serial->printf("\tBNO055 not in use.\r\n");
  };


  delete(serial);

}
