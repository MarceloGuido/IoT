#include <TM1637Display.h>

#define CLK 4  // D2 (GPIO4)
#define DIO 0  // D3 (GPIO0)

TM1637Display display(CLK, DIO);

void setup() {
    display.setBrightness(7);

    // Exibe "OI" no display
    uint8_t oi[] = {0x3F, 0x06, 0x00, 0x00};
    display.setSegments(oi);
}

void loop() {
   
}
