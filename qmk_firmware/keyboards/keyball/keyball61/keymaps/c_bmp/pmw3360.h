#pragma once

#include QMK_KEYBOARD_H

#include <stdint.h>
#include <stdbool.h>
    
#define constrain_hid(amt) ((amt) < -127 ? -127 : ((amt) > 127 ? 127 : (amt)))

//////////////////////////////////////////////////////////////////////////////
// Configurations

#define PMW3360_SPI_MODE 3
#define PMW3360_SPI_DIVISOR (F_CPU / PMW3360_CLOCKS)
#define PMW3360_CLOCKS 2000000

#ifndef PMW3360_NCS_PIN
#    define PMW3360_NCS_PIN 13
#endif

#ifndef PMW3360_MOSI
#    define PMW3360_MOSI 14
#endif

#ifndef PMW3360_MISO
#    define PMW3360_MISO 15
#endif

#ifndef PMW3360_SCLK
#    define PMW3360_SCLK 16
#endif

#define PMW3360_CPI 500U
#define PMW3360_CPI_STEP 100
#define PMW3360_CPI_MIN 100
#define PMW3360_CPI_MAX 12000

enum {
    pmw3360_MAXCPI = 0x77, // = 119: 12000 CPI
};


// PMW3360 register addresses
// clang-format off
#define REG_Product_ID                   0x00
#define REG_Revision_ID                  0x01
#define REG_Motion                       0x02
#define REG_Delta_X_L                    0x03
#define REG_Delta_X_H                    0x04
#define REG_Delta_Y_L                    0x05
#define REG_Delta_Y_H                    0x06
#define REG_SQUAL                        0x07
#define REG_Raw_Data_Sum                 0x08
#define REG_Maximum_Raw_data             0x09
#define REG_Minimum_Raw_data             0x0a
#define REG_Shutter_Lower                0x0b
#define REG_Shutter_Upper                0x0c
#define REG_Control                      0x0d
#define REG_Config1                      0x0f
#define REG_Config2                      0x10
#define REG_Angle_Tune                   0x11
#define REG_Frame_Capture                0x12
#define REG_SROM_Enable                  0x13
#define REG_Run_Downshift                0x14
#define REG_Rest1_Rate_Lower             0x15
#define REG_Rest1_Rate_Upper             0x16
#define REG_Rest1_Downshift              0x17
#define REG_Rest2_Rate_Lower             0x18
#define REG_Rest2_Rate_Upper             0x19
#define REG_Rest2_Downshift              0x1a
#define REG_Rest3_Rate_Lower             0x1b
#define REG_Rest3_Rate_Upper             0x1c
#define REG_Observation                  0x24
#define REG_Data_Out_Lower               0x25
#define REG_Data_Out_Upper               0x26
#define REG_Raw_Data_Dump                0x29
#define REG_SROM_ID                      0x2a
#define REG_Min_SQ_Run                   0x2b
#define REG_Raw_Data_Threshold           0x2c
#define REG_Config5                      0x2f
#define REG_Power_Up_Reset               0x3a
#define REG_Shutdown                     0x3b
#define REG_Inverse_Product_ID           0x3f
#define REG_LiftCutoff_Tune3             0x41
#define REG_Angle_Snap                   0x42
#define REG_LiftCutoff_Tune1             0x4a
#define REG_Motion_Burst                 0x50
#define REG_LiftCutoff_Tune_Timeout      0x58
#define REG_LiftCutoff_Tune_Min_Length   0x5a
#define REG_SROM_Load_Burst              0x62
#define REG_Lift_Config                  0x63
#define REG_Raw_Data_Burst               0x64
#define REG_LiftCutoff_Tune2             0x65
// clang-format on

typedef struct {
    int16_t x;
    int16_t y;
} pmw3360_motion_t;

//////////////////////////////////////////////////////////////////////////////

/// pmw3360_init initializes PMW3360DM-T2QU module.
/// It will return true when succeeded, otherwise false.
bool pmw3360_init(void);

uint8_t pmw3360_cpi_get(void);

void pmw3360_cpi_set(uint8_t cpi);

/// pmw3360_motion_read gets a motion data by Motion register.
/// This requires to write a dummy data to pmw3360_Motion register
/// just before.
bool pmw3360_motion_read(pmw3360_motion_t *d);

/// pmw3360_motion_burst gets a motion data by Motion_Burst command.
/// This requires to write a dummy data to pmw3360_Motion_Burst register
/// just before.
bool pmw3360_motion_burst(pmw3360_motion_t *d);

//////////////////////////////////////////////////////////////////////////////
// Register operations

/// pmw3360_reg_read reads a value from a register.
uint8_t pmw3360_reg_read(uint8_t addr);

/// pmw3360_reg_write writes a value to a register.
void pmw3360_reg_write(uint8_t addr, uint8_t data);

//////////////////////////////////////////////////////////////////////////////

void spi_start();

void spi_stop();
