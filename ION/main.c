#include "ION_CAN.h"
#include "ION_10-DOF_IUM.h"
#include "ION_LED.h"
#include "ION_GPS.h"

uint8_t data[8];
int x;
l3gd20hAxis L3GAxis;
lsm303AccelAxis LSMAccelAxis;
lsm303MagAxis LSMMagAxis;
uint16_t chip[12];
uint8_t chip_MSB;
uint8_t chip_LSB;
int main(void)
{
    LED_init();
    TEN_DOF_IUM_Initialise(I2C2);
    CAN_Initialise(CAN2);
    GPS_Initialise();
    
    data[0] = 'I';
    data[1] = 'O';
    data[2] = 'N';
    data[3] = ' ';
    data[4] = 'U';
    data[5] = 'I';
    data[6] = 'S';
    data[7] = '!';
    while(1)
    {
        for(x = 0;x < 0xFFFFF;x++);
        LED_on(LED1);
        
        L3GAxis = L3GD20H_XYZ(); //Axis
        chip[0] = L3GAxis.X;
        chip[1] = L3GAxis.Y;
        chip[2] = L3GAxis.Z;
        
        for(x = 0;x < 0xFFFFF;x++);
        LED_on(LED2);
        
        LSMAccelAxis = LSM303_ACCEL_XYZ(); //Acceleration
        chip[3] = LSMAccelAxis.X;
        chip[4] = LSMAccelAxis.Y;
        chip[5] = LSMAccelAxis.Z;
        
        for(x = 0;x < 0xFFFFF;x++);
        LED_on(LED3);
        
        LSMMagAxis = LSM303_MAG_XYZ(); //Magnetometer
        chip[6] = LSMMagAxis.X;
        chip[7] = LSMMagAxis.Y;
        chip[8] = LSMMagAxis.Z;
        
        for(x = 0;x < 0xFFFFF;x++);
        LED_on(LED4);
        
        chip[9] = BMP180_Temperature(BMP180_OSS_SINGLE); //Temperature
        
        for(x = 0;x < 0xFFFFF;x++);
        LED_off(LED1);
        
        chip[10] = BMP180_Pressure(BMP180_OSS_SINGLE); //Pressure
        
        for(x = 0;x < 0xFFFFF;x++);
        LED_off(LED2);
        
        chip[11] = USARTData[0]; //get gps cords; this is for testing only.
        
        for(x = 0;x < 0xFFFFF;x++);
        LED_off(LED3);
        
        for (x = 0;x < 12;x++) //send data to CAN.
        {
            chip_LSB = (uint8_t)(chip[x]);
            chip_MSB = (uint8_t)(chip[x]>>8);
            CAN_Write(CAN2, 0x01, 1, &chip_LSB); //LSB-CAN
            CAN_Write(CAN2, 0x02, 1, &chip_MSB); //MSB-CAN
        }
        
        for(x = 0;x < 0xFFFFF;x++);
        LED_off(LED4);
        
        for (x = 0;x < 12;x++) //send data to USART.
        {
            USART_Write(USART2, chip[x]); //USART.
        }
    }    
}
