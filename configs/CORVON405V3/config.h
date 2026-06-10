/*
 * This file is part of Betaflight.
 * Target Configuration for CORVON405V3
 */

#pragma once

#define FC_TARGET_MCU   STM32F405

// --- Board & Manufacturer Info ---
#define BOARD_NAME      CORVON405V3
#define MANUFACTURER_ID CORV

// --- Accelerometer & Gyro ---
#define USE_ACC
#define USE_ACC_SPI_ICM42688P
#define USE_GYRO
#define USE_GYRO_SPI_ICM42688P
#define GYRO_1_CS_PIN           PC8
#define GYRO_1_SPI_INSTANCE     SPI2
#define GYRO_1_ALIGN            CW180_DEG

// GYRO CLOCK INPUT (External Clock)
// Currently DISABLED because PA8 is used for LED Blue.
// To enable later:
// #define USE_GYRO_CLKIN
// #define GYRO_1_CLKIN_PIN PA8
// #TIMER_PIN_MAP( 9, PA8, 1, -1 )

// --- Barometer ---
#define USE_BARO
#define USE_BARO_SPI_DPS310
#define BARO_CS_PIN             PA4
#define BARO_SPI_INSTANCE       SPI2

// --- Flash (Blackbox) ---
#define USE_FLASH
#define USE_FLASH_SPI
#define USE_FLASH_W25Q128FV
#define FLASH_CS_PIN            PC9
#define FLASH_SPI_INSTANCE      SPI3

// --- OSD ---
#define USE_OSD
#define USE_OSD_HD
#define USE_OSD_SD
#define USE_MAX7456
#define MAX7456_SPI_INSTANCE    SPI1
#define MAX7456_SPI_CS_PIN      PB12

// --- Other Features ---
#define USE_VTX
#define USE_NONCOMPLIANT_SMARTAUDIO
#define USE_LED_STRIP
#define USE_BEEPER
#define USE_ADC
#define USE_MAG
#define USE_MAG_I2C

// --- Motor Mapping (8 Motors) ---
// NOTE: M7 (PB8) / M8 (PB9) intentionally disabled on this target.
// DMA analysis: enabling M7 requires DMA1 Stream 7 Ch 2 (TIM4_CH3) which
// conflicts with M1 already holding Stream 7 Ch 5 (TIM3_CH3); TIM4_CH4
// (PB9) has no dedicated DMA request on F405, and its TIM4_UP fallback
// (DMA1 Stream 6 Ch 2) collides with M4 on Stream 6 Ch 3 (TIM2_CH2).
// Pads are present on the PCB but left unused in firmware.
#define MOTOR1_PIN PB0
#define MOTOR2_PIN PB1
#define MOTOR3_PIN PA15
#define MOTOR4_PIN PB3
#define MOTOR5_PIN PB4
#define MOTOR6_PIN PB5
// #define MOTOR7_PIN PB8
// #define MOTOR8_PIN PB9

// --- LED Strip ---
#define LED_STRIP_PIN PB14

// --- UART Mapping ---
#define UART1_TX_PIN PA9
#define UART1_RX_PIN PA10

#define UART2_TX_PIN PA2
#define UART2_RX_PIN PA3

#define UART3_TX_PIN PB10
#define UART3_RX_PIN PB11

#define UART4_TX_PIN PA0
#define UART4_RX_PIN PA1

#define UART5_RX_PIN PD2

#define UART6_TX_PIN PC6
#define UART6_RX_PIN PC7
#define INVERTER_PIN_UART6 PC15 // Hardware Inverter

// --- Serial Port Roles ---
#define MSP_UART             SERIAL_PORT_USART1
#define MSP_DISPLAYPORT_UART SERIAL_PORT_USART2
#define GPS_UART             SERIAL_PORT_USART3
#define ESC_SENSOR_UART      SERIAL_PORT_UART5
#define SERIALRX_UART        SERIAL_PORT_USART6

// --- SPI Mapping ---
#define SPI1_SCK_PIN PA5
#define SPI1_SDI_PIN PA6
#define SPI1_SDO_PIN PA7

#define SPI2_SCK_PIN PB13
#define SPI2_SDI_PIN PC2
#define SPI2_SDO_PIN PC3

#define SPI3_SCK_PIN PC10
#define SPI3_SDI_PIN PC11
#define SPI3_SDO_PIN PC12

// --- I2C Mapping ---
#define I2C1_SCL_PIN PB6
#define I2C1_SDA_PIN PB7
#define MAG_I2C_INSTANCE I2CDEV_1

// --- ADC Mapping ---
#define ADC_VBAT_PIN PC0
#define ADC_CURR_PIN PC1
#define ADC_INSTANCE ADC1
#define ADC1_DMA_OPT 1

// --- Status LEDs ---
// PA8 kept as LED Blue for current hardware revision.
#define LED0_PIN           PA8 // Blue
#define LED1_PIN           PC4 // Red
#define LED2_PIN           PC5 // Green

#define BEEPER_PIN         PB15
#define BEEPER_INVERTED

// --- Timer Mapping ---
// Indices 6/7 intentionally skipped (M7/M8 disabled above).
// Timer/channel resolution (verified via CLI dump):
//   PB0  occ=2 -> TIM3_CH3  (AF2)
//   PB1  occ=2 -> TIM3_CH4  (AF2)
//   PA15 occ=1 -> TIM2_CH1  (AF1)
//   PB3  occ=1 -> TIM2_CH2  (AF1)
//   PB4  occ=1 -> TIM3_CH1  (AF2)
//   PB5  occ=1 -> TIM3_CH2  (AF2)
//   PB14 occ=2 -> TIM8_CH2N (AF3)  [LED_STRIP]

#define TIMER_PIN_MAPPING \
    TIMER_PIN_MAP( 0, MOTOR1_PIN, 2,  0 ) \
    TIMER_PIN_MAP( 1, MOTOR2_PIN, 2,  0 ) \
    TIMER_PIN_MAP( 2, MOTOR3_PIN, 1,  0 ) \
    TIMER_PIN_MAP( 3, MOTOR4_PIN, 1,  0 ) \
    TIMER_PIN_MAP( 4, MOTOR5_PIN, 1,  0 ) \
    TIMER_PIN_MAP( 5, MOTOR6_PIN, 1,  0 ) \
    TIMER_PIN_MAP( 8, LED_STRIP_PIN, 2, 0 )

// --- Defaults ---
#define SYSTEM_HSE_MHZ 8
#define DEFAULT_DSHOT_BURST          DSHOT_DMAR_ON
#define DEFAULT_BLACKBOX_DEVICE      BLACKBOX_DEVICE_FLASH
#define DEFAULT_VOLTAGE_METER_SOURCE VOLTAGE_METER_ADC
#define DEFAULT_VOLTAGE_METER_SCALE  210
#define DEFAULT_CURRENT_METER_SOURCE CURRENT_METER_ADC
#define DEFAULT_CURRENT_METER_SCALE  402
