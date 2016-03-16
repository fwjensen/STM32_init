#include "ION_CAN.h"
#include "ION_LED.h"

uint8_t data[8];
int x;
int main(void)
{
    LED_init();
    CAN_Initialise(CAN2);
    
    data[0] = 0x11;
    data[1] = 0x22;
    data[2] = 0x33;
    data[3] = 0x44;
    data[4] = 0x55;
    data[5] = 0x66;
    data[6] = 0x77;
    data[7] = 0x88;
    
    while(1)
    {
        LED_toggle(LED1);
        for(x = 0;x < 0xFFFFF;x++);
        CAN_Write(0x00, 8, data);
    }    
}
