/*
  wifi.cpp - Handles connection to wifi and makes web, websockets and telnet
  connections available
*/

#ifndef esp8266_cpu_map_h
#define esp8266_cpu_map_h

volatile static union
{
  uint32_t data;
  struct
  {
    uint8_t STEP_PORT_OFFSET : 8;      // All outputs
    uint8_t DIRECTION_PORT_OFFSET : 8; // All outputs
    uint8_t MISC_PORT_OFFSET : 8;      // Inputs and outputs
    uint8_t LIMIT_PORT_OFFSET : 8;     // All inputs
  };
} regs;

// Used to modify SPI registers without altering Grbl's registers
decltype(regs) regs_tmp;


// Define serial port pins and interrupt vectors.
#define SERIAL_RX USART_RX_vect
#define SERIAL_UDRE USART_UDRE_vect


#define ENABLE_WIFI             // Enables wifi needed for websocket, telnet, etc
#define ENABLE_WEBSOCKET    // Enables socket serial communication
#define ENABLE_TELNET           // Enables telnet communication
//#define ENABLE_mDNS           // Enables ESP8266 mDNS
//#define ENABLE_OTA            // Enables ESP8266 OTA


#if defined(ENABLE_mDNS) && defined(ENABLE_OTA)
#error "ENABLE_mDNS AND ENABLE_OTA Not use at the same time , ENABLE_OTA include ENABLE_mDNS"
#endif

#ifdef ENABLE_WIFI
  #define WIFI_SSID "baoli301"
  #define WIFI_PASSWORD "wwwhhh123"
  #define WIFI_HOSTNAME "grblesp"  // 设置对应的域名,不用加<.local>
  #define OTA_HOSTNAME WIFI_HOSTNAME
  #define OTA_PASSWORD WIFI_HOSTNAME
#endif
// Define step pulse output pins. NOTE: All step bit pins must be on the same port.
#define STEP_PORT regs.STEP_PORT_OFFSET
#define X_STEP_BIT 0
#define Y_STEP_BIT 1
#define Z_STEP_BIT 2
#define A_STEP_BIT 3
#define B_STEP_BIT 4
#define C_STEP_BIT 5
#define D_STEP_BIT 6
#define E_STEP_BIT 7
#define STEP_MASK ((1 << X_STEP_BIT) | (1 << Y_STEP_BIT) | (1 << Z_STEP_BIT) | (1 << A_STEP_BIT) | (1 << B_STEP_BIT) | (1 << C_STEP_BIT) | (1 << D_STEP_BIT) | (1 << E_STEP_BIT)) // All step bits

// Define step direction output pins. NOTE: All direction pins must be on the same port.
#define DIRECTION_PORT regs.DIRECTION_PORT_OFFSET
#define X_DIRECTION_BIT 0
#define Y_DIRECTION_BIT 1
#define Z_DIRECTION_BIT 2
#define A_DIRECTION_BIT 3
#define B_DIRECTION_BIT 4
#define C_DIRECTION_BIT 5
#define D_DIRECTION_BIT 6
#define E_DIRECTION_BIT 7
#define DIRECTION_MASK ((1 << X_DIRECTION_BIT) | (1 << Y_DIRECTION_BIT) | (1 << Z_DIRECTION_BIT) | (1 << A_DIRECTION_BIT) | (1 << B_DIRECTION_BIT) | (1 << C_DIRECTION_BIT) | (1 << D_DIRECTION_BIT) | (1 << E_DIRECTION_BIT)) // All direction bits

// Define stepper driver enable/disable output pin.
#define STEPPERS_DISABLE_PORT regs.MISC_PORT_OFFSET
#define STEPPERS_DISABLE_BIT 7
#define STEPPERS_DISABLE_MASK (1 << STEPPERS_DISABLE_BIT)

// Define homing/hard limit switch input pins and limit interrupt vectors.
// NOTE: All limit bit pins must be on the same port, but not on a port with other input pins (CONTROL).
#define LIMIT_PORT_INPUTS regs_tmp.LIMIT_PORT_OFFSET
#define LIMIT_PORT regs.LIMIT_PORT_OFFSET
#define X_LIMIT_BIT 0
#define Y_LIMIT_BIT 1
#define Z_LIMIT_BIT 2
#define A_LIMIT_BIT 3
#define B_LIMIT_BIT 4
#define C_LIMIT_BIT 5
#define D_LIMIT_BIT 6
#define E_LIMIT_BIT 7
#define LIMIT_MASK ((1 << X_LIMIT_BIT) | (1 << Y_LIMIT_BIT) | (1 << Z_LIMIT_BIT) | (1 << A_LIMIT_BIT) | (1 << B_LIMIT_BIT) | (1 << C_LIMIT_BIT) | (1 << D_LIMIT_BIT) | (1 << E_LIMIT_BIT)) // All limit bits

/*
  // Define spindle enable and spindle direction output pins.
  #define SPINDLE_ENABLE_PORT  regs.MISC_PORT_OFFSET
  // Z Limit pin and spindle PWM/enable pin swapped to access hardware PWM on Pin 11.
  #ifdef VARIABLE_SPINDLE
    #ifdef USE_SPINDLE_DIR_AS_ENABLE_PIN
      // If enabled, spindle direction pin now used as spindle enable, while PWM remains on D11.
      #define SPINDLE_ENABLE_BIT    7
    #else
      #define SPINDLE_ENABLE_BIT    7
    #endif
  #else
    #define SPINDLE_ENABLE_BIT    7
  #endif
  #ifndef USE_SPINDLE_DIR_AS_ENABLE_PIN
    #define SPINDLE_DIRECTION_BIT   7
  #endif
*/

// Define flood and mist coolant enable output pins.
#define COOLANT_FLOOD_PORT regs.MISC_PORT_OFFSET
#define COOLANT_FLOOD_BIT 5
#define COOLANT_MIST_PORT regs.MISC_PORT_OFFSET
#define COOLANT_MIST_BIT 6

// Define user-control controls (cycle start, reset, feed hold) input pins.
// NOTE: All CONTROLs pins must be on the same port and not on a port with other input pins (limits).
#define CONTROL_PORT_INPUTS regs_tmp.MISC_PORT_OFFSET
#define CONTROL_PORT regs.MISC_PORT_OFFSET
#define CONTROL_RESET_BIT 0
#define CONTROL_FEED_HOLD_BIT 1
#define CONTROL_CYCLE_START_BIT 2
#define CONTROL_SAFETY_DOOR_BIT 3

//#define CONTROL_INT       PCIE1  // Pin change interrupt enable pin
//#define CONTROL_INT_vect  PCINT1_vect
//#define CONTROL_PCMSK     PCMSK1 // Pin change interrupt register
#define CONTROL_MASK ((1 << CONTROL_RESET_BIT) | (1 << CONTROL_FEED_HOLD_BIT) | (1 << CONTROL_CYCLE_START_BIT) | (1 << CONTROL_SAFETY_DOOR_BIT))
#define CONTROL_INVERT_MASK CONTROL_MASK // May be re-defined to only invert certain control pins.

// Define probe switch input pin.
#define PROBE_PORT regs.MISC_PORT_OFFSET
#define PROBE_BIT 4
#define PROBE_MASK (1 << PROBE_BIT)

// Variable spindle configuration below. Do not change unless you know what you are doing.
// NOTE: Only used when variable spindle is enabled.
#define SPINDLE_PWM_MAX_VALUE 255 // Don't change. 328p fast PWM mode fixes top value as 255.
#ifndef SPINDLE_PWM_MIN_VALUE
#define SPINDLE_PWM_MIN_VALUE 1 // Must be greater than zero.
#endif
#define SPINDLE_PWM_OFF_VALUE 0
#define SPINDLE_PWM_RANGE (SPINDLE_PWM_MAX_VALUE - SPINDLE_PWM_MIN_VALUE)
//#define SPINDLE_TCCRA_REGISTER	  TCCR2A
//#define SPINDLE_TCCRB_REGISTER	  TCCR2B
//#define SPINDLE_OCR_REGISTER      OCR2A
//#define SPINDLE_COMB_BIT	        COM2A1

// Prescaled, 8-bit Fast PWM mode.
#define SPINDLE_TCCRA_INIT_MASK ((1 << WGM20) | (1 << WGM21)) // Configures fast PWM mode.
// #define SPINDLE_TCCRB_INIT_MASK   (1<<CS20)               // Disable prescaler -> 62.5kHz
// #define SPINDLE_TCCRB_INIT_MASK   (1<<CS21)               // 1/8 prescaler -> 7.8kHz (Used in v0.9)
// #define SPINDLE_TCCRB_INIT_MASK   ((1<<CS21) | (1<<CS20)) // 1/32 prescaler -> 1.96kHz
#define SPINDLE_TCCRB_INIT_MASK (1 << CS22) // 1/64 prescaler -> 0.98kHz (J-tech laser)

// NOTE: On the 328p, these must be the same as the SPINDLE_ENABLE settings.
#define SPINDLE_PWM_DDR DDRB
#define SPINDLE_PWM_PORT PORTB
#define SPINDLE_PWM_BIT 3 // Uno Digital Pin 11

#define CONTROL_INPUT_GPIO_PIN D3 // GPIO_0 = D3

#define LIMIT_INPUT_GPIO_PIN D4 // GPIO_2 = D4

#define F_STEPPER_TIMER 80000000 / 2 // frequency in Hz of step pulse timer (SPI)

#define DISABLE_74HC595 // not use spi control steeper 74HC595 芯片扩充GPIO
//#define USE_ENABLE_STEPPERS  //使用gpio15引腳控制电机使能引腳,连接到3个步进电机EN脚
#define USE_ENABLE_SPINDLE //使用gpio15引腳作为pwm引脚,范围0-1000 M3S500 ,舵机占空比为 500/1000 = 0.5
#define Servo // 把pwm引脚作为舵机引脚,把pwm改为50hz.输入的值为舵机角度,范围0-210度 M3S30 舵机转过30度,



#ifdef DISABLE_74HC595
#define X_STEP_PORT 5
#define Y_STEP_PORT 13
#define Z_STEP_PORT 14

#define X_DIRECTION_PORT 4
#define Y_DIRECTION_PORT 12
#define Z_DIRECTION_PORT 16
#endif //DISABLE_74HC595

#ifdef USE_ENABLE_STEPPERS //步进电机使能
#define C_STEPPERS_DISABLE_PORT 15
#endif // USE_ENABLE_STEPPERS

#ifdef USE_ENABLE_SPINDLE  //pwm 使能
#define C_SPINDLE_PORT 15
#endif //USE_ENABLE_SPINDLE

#if defined(USE_ENABLE_STEPPERS) && defined(USE_ENABLE_SPINDLE)
#error "USE_SPINDLE AND USE_ENABLE_STEPPERS Not use at the same time"
#endif

#endif //esp8266_cpu_map_h