#include <i8254.h>
#include <ioports.h>

// IO port
#define COUNTER_0 0x40 // Clock
#define COUNTER_1 0x41 // RAM Refresh Counter (usually in mode 2)
#define COUNTER_2 0x42 // Speaker function

#define CONTROL_REG  0x43 // Mode control register

// Control Word Register [SC1 SC0 RW1 RW0 M2 M1 M0 BCD]
// SC - Counter selection
// RW - Read/Write
// M - Mode
// BCD - Binary Counter
#define SELECT_COUNTER_0 0x0
#define NO_RW   0x0
#define RW_LOW  0x1
#define RW_HIGH 0x2
#define RW_ALL  0x3
#define MODE_0 0x0 // count down and interrupt on 0
#define MODE_1 0x1 
#define MODE_2 0x2
#define MODE_3 0x3
#define MODE_4 0x4
#define MODE_5 0x5
#define BINARY_COUNT  0x0
#define DECIMAL_COUNT 0x1

void i8254_init(uint16_t freq)
{
  uint8_t controlByte;
  uint16_t nb_tick = (I8254_MAX_FREQ / freq);

  controlByte = (SELECT_COUNTER_0 << 6) |
                (RW_ALL           << 4) |
                (MODE_0           << 1) |
                (BINARY_COUNT);
  outb(controlByte, CONTROL_REG);
  outb(nb_tick & 0xFF, COUNTER_0);
  outb((nb_tick >> 8) & 0xFF, COUNTER_0);
}

