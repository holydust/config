/*
 * This file is part of Betaflight.
 *
 * Betaflight is free software. You can redistribute this software
 * and/or modify this software under the terms of the GNU General
 * Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any later
 * version.
 *
 * Betaflight is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this software.
 *
 * If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#define FC_TARGET_MCU   STM32H743

#define BOARD_NAME      CORVON743V2
#define MANUFACTURER_ID CORV

// V2 needs 4 MSP-capable serial ports concurrently: VCP (USB), USART1 (MSP_UART),
// USART2 (MSP_DISPLAYPORT_UART forces FUNCTION_VTX_MSP|FUNCTION_MSP for DJI O4),
// and UART8 (USE_MSP_UART for onboard Bluetooth). BF's default cap is 3, which
// causes isSerialConfigValid() to reject any user save attempt silently — every
// CLI/Configurator change reverts after reboot. Bump to 4. Cost: one extra
// mspPort_t (~100 B) in static storage.
#define MAX_MSP_PORT_COUNT 4

// --- Sensor drivers ---
#define USE_ACC
#define USE_GYRO
#define USE_ACC_SPI_ICM42688P
#define USE_GYRO_SPI_ICM42688P
#define USE_BARO
#define USE_BARO_BMP581       // BMP581 silicon, driver from #14925 (backported on parent branch)
#define DEFAULT_BARO_BMP581   // makes pgReset_barometer take the I2C branch; without this baro_hardware defaults to BARO_NONE
#define USE_SDCARD

#ifndef USE_MAG
#define USE_MAG
#define USE_MAG_IST8310
#endif

// --- Motor pins (10 DShot bidir + 2 PWM servos) ---
#define MOTOR1_PIN  PE9     // TIM1_CH1
#define MOTOR2_PIN  PE11    // TIM1_CH2
#define MOTOR3_PIN  PE13    // TIM1_CH3
#define MOTOR4_PIN  PE14    // TIM1_CH4
#define MOTOR5_PIN  PB0     // TIM3_CH3
#define MOTOR6_PIN  PB1     // TIM3_CH4
#define MOTOR7_PIN  PD12    // TIM4_CH1
#define MOTOR8_PIN  PD13    // TIM4_CH2
#define MOTOR9_PIN  PD14    // TIM4_CH3
#define MOTOR10_PIN PD15    // TIM4_CH4
#define SERVO1_PIN  PB14    // TIM12_CH1, PWM-only
#define SERVO2_PIN  PB15    // TIM12_CH2, PWM-only

// --- UART pins (8 UARTs) ---
#define UART1_TX_PIN PA9
#define UART1_RX_PIN PA10
#define UART2_TX_PIN PA2
#define UART2_RX_PIN PA3
#define UART3_TX_PIN PD8
#define UART3_RX_PIN PD9
#define UART4_TX_PIN PA0
#define UART4_RX_PIN PA1
#define UART5_TX_PIN PB13
#define UART5_RX_PIN PB12
#define UART6_TX_PIN PC6
#define UART6_RX_PIN PC7
#define UART7_TX_PIN PE8
#define UART7_RX_PIN PE7
#define UART8_TX_PIN PE1
#define UART8_RX_PIN PE0

// --- I2C pins ---
#define I2C1_SCL_PIN PB6     // external (GPS+compass / airspeed)
#define I2C1_SDA_PIN PB7
#define I2C2_SCL_PIN PB10    // internal (BMP581 baro + IST8310 mag)
#define I2C2_SDA_PIN PB11

// --- SPI3 (IMU bus) ---
#define SPI3_SCK_PIN PB3
#define SPI3_SDI_PIN PB4     // MISO
#define SPI3_SDO_PIN PB5     // MOSI (AF7 — see resource doc §11.4)

// --- SDIO (SDMMC1, 4-bit) ---
#define SDIO_CK_PIN  PC12
#define SDIO_CMD_PIN PD2
#define SDIO_D0_PIN  PC8
#define SDIO_D1_PIN  PC9
#define SDIO_D2_PIN  PC10
#define SDIO_D3_PIN  PC11

// --- ADC (primary battery only) ---
#define ADC_VBAT_PIN PC0
#define ADC_CURR_PIN PC1
// PC4 / PC5: secondary battery pads (no Betaflight BAT2 firmware support).
// PB8 / PB9: FDCAN1 (unused by Betaflight).
// PD4 / PD5 / PD6 / PD11: BMI088 split-CS / DRDY pads (no BF driver yet).

// --- Status LEDs (V2 silkscreen: PE4=blue, PE5=red, PE6=green) ---
#define LED0_PIN PE4
#define LED1_PIN PE5
#define LED2_PIN PE6

// --- Beeper + WS2812 ---
#define BEEPER_PIN    PA7    // TIM14_CH1
#define LED_STRIP_PIN PA5    // TIM2_CH1

// --- IMU 1: ICM-42688P on SPI3 ---
#define GYRO_1_SPI_INSTANCE SPI3
#define GYRO_1_CS_PIN       PA15
#define GYRO_1_EXTI_PIN     PD10
#define GYRO_1_ALIGN        CW90_DEG

// --- Baro: BMP581 on I2C2 @ 0x46 (SDO = GND) ---
#define BARO_I2C_INSTANCE        I2CDEV_2
#define DEFAULT_BARO_I2C_ADDRESS 0x46     // SDO=GND on V2; BF's macro name is DEFAULT_BARO_I2C_ADDRESS, not BARO_I2C_ADDRESS

// --- Mag: IST8310 on I2C2 @ 0x0E (this batch — datasheet default 0x0C) ---
#define MAG_I2C_INSTANCE I2CDEV_2
#define MAG_I2C_ADDRESS  14          // 0x0E
#define MAG_ALIGN        CW90_DEG
#define MAG_ALIGN_YAW    900

// --- Timer pin mapping ---
//
// Timer occurrence indices verified against
// src/platform/STM32/timer_stm32h7xx.c:56-138 :
//   PB0/PB1 use occ 2 (TIM3 channels)
//   PB14/PB15 use occ 2 (TIM12 channels)
//   PA5 uses occ 1 (TIM2_CH1)
//   PA7 uses occ 4 (TIM14_CH1)
//
#define TIMER_PIN_MAPPING \
    TIMER_PIN_MAP( 0, MOTOR1_PIN,    1,  0 ) /* PE9  TIM1_CH1  */ \
    TIMER_PIN_MAP( 1, MOTOR2_PIN,    1,  1 ) /* PE11 TIM1_CH2  */ \
    TIMER_PIN_MAP( 2, MOTOR3_PIN,    1,  2 ) /* PE13 TIM1_CH3  */ \
    TIMER_PIN_MAP( 3, MOTOR4_PIN,    1,  3 ) /* PE14 TIM1_CH4  */ \
    TIMER_PIN_MAP( 4, MOTOR5_PIN,    2,  4 ) /* PB0  TIM3_CH3  */ \
    TIMER_PIN_MAP( 5, MOTOR6_PIN,    2,  5 ) /* PB1  TIM3_CH4  */ \
    TIMER_PIN_MAP( 6, MOTOR7_PIN,    1,  6 ) /* PD12 TIM4_CH1  */ \
    TIMER_PIN_MAP( 7, MOTOR8_PIN,    1,  7 ) /* PD13 TIM4_CH2  */ \
    TIMER_PIN_MAP( 8, MOTOR9_PIN,    1,  8 ) /* PD14 TIM4_CH3  */ \
    TIMER_PIN_MAP( 9, MOTOR10_PIN,   1,  9 ) /* PD15 TIM4_CH4  */ \
    TIMER_PIN_MAP(10, SERVO1_PIN,    2, -1 ) /* PB14 TIM12_CH1, PWM-only */ \
    TIMER_PIN_MAP(11, SERVO2_PIN,    2, -1 ) /* PB15 TIM12_CH2, PWM-only */ \
    TIMER_PIN_MAP(12, LED_STRIP_PIN, 1, 10 ) /* PA5  TIM2_CH1  */ \
    TIMER_PIN_MAP(13, BEEPER_PIN,    4, -1 ) /* PA7  TIM14_CH1 */

#define ADC1_DMA_OPT   8
#define ADC3_DMA_OPT   9
#define TIMUP1_DMA_OPT 0
#define TIMUP3_DMA_OPT 0
#define TIMUP4_DMA_OPT 0
#define TIMUP8_DMA_OPT 0

#define SDIO_USE_4BIT 1
#define SDIO_DEVICE   SDIODEV_1

#define BEEPER_INVERTED
#define BEEPER_PWM_HZ 2500

#define DEFAULT_BLACKBOX_DEVICE      BLACKBOX_DEVICE_SDCARD
#define DEFAULT_CURRENT_METER_SOURCE CURRENT_METER_ADC
#define DEFAULT_VOLTAGE_METER_SOURCE VOLTAGE_METER_ADC
#define DEFAULT_CURRENT_METER_SCALE  402     // V1 carryover; bench-cal recommended
#define DEFAULT_VOLTAGE_METER_SCALE  210     // 21:1 divider per resource doc

// --- UART role bindings ---
#define MSP_UART             SERIAL_PORT_USART1   // TELEM1 — primary MSP (next to USB VCP)
#define MSP_DISPLAYPORT_UART SERIAL_PORT_USART2   // DJI O4
#define GPS_UART             SERIAL_PORT_USART3
#define SERIALRX_UART        SERIAL_PORT_USART6   // SBUS / CRSF
#define ESC_SENSOR_UART      SERIAL_PORT_UART7
#define USE_MSP_UART         SERIAL_PORT_UART8    // secondary MSP for onboard Bluetooth @ 115200 (see resource doc §11.15)
// UART4 (TELEM2) and UART5 (aux) left unbound — user assigns via Configurator.
