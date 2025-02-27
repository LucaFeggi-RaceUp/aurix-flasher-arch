/*
 * ********************************************************************************************************************
 *  Copyright 2022 Infineon Technologies AG
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *      http://www.apache.org/licenses/LICENSE-2.0
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 * ******************************************************************************************************************** */
#pragma once

#include <stdint.h>

// Definitions for addr_map 15 (TAS_AM15) and 14 (TAS_AM14)
// The TAS_AM15 addresses are compatible to the DAS address map 132 definitions

enum : uint8_t {
    TAS_AM0   = 0,    // Default for device access
    TAS_AM1   = 1,    // Auxiliary address map for device access. E.g. direct EEC access of AURIX EDs

    TAS_AM12  = 12,   // All address maps equal or higher than 12 are for special usage
    TAS_AM14  = 14,   // Exclusively used in the TasProxyServer inside of the device
    TAS_AM15  = 15,   // Exclusively used inside of the TasServer
    TAS_AM132 = 132,  // Converted to TAS_AM15 during TasClient packet request generation
};

// A PL1 packet may contain a mix of PL0 address maps if all are less than 12.
// Rules for address maps 12, 13, TAS_AM14 and TAS_AM15:
// 1. May only be used exclusively in a Pl1 packet.
// 2. A block transfer is never split to different Pl1 packets
// 3. Only 32 bit addresses allowed
// 4. Use uint32_t for the value read/written if not differently described

enum : uint16_t {
    TAS_AM_MASK_EXCLUSIVE = 0xF000,
    TAS_AM_MASK_SHARED    = 0x0FFF,
};

enum { TAS_AM15_JTAG_MAX_NUM_SCAN_BITS_PER_TRANSACTION = 1024*8 };

// If not otherwise noticed, the read or written values are 32 bit

enum tas_am15_addr_et : uint32_t {

    TAS_AM15_R_RESET_COUNT_GET = 0x000A1800,
    // Read tas_reset_count_st of TasServer for the connected device

    TAS_AM15_RW_USERPINS = 0x000A8000,
    // Read or write user pins with a bit vector.
    // Includes input and output pins.
    // read32 returns the value of input and output pins. Not existing pins are 0.
    // read64 returns tas_userpins_mask_st. mask shows all available user pins.
    // write32 updates all access HW output pins (tool to device t2d direction).
    // write64 updates only the t2d pins, where the mask bit is set.
    // The usage of write32 is discouraged to avoid race conditions for multi-tool setups.
    // Can use the tasutil_userpins_set_high()/tasutil_userpins_set_low() in simple cases.
    // If mask includes a pin which is not t2d, error TAS_ERR_RW_WRITE is returned.
    // However other t2d pins are updated properly in this case.

    TAS_AM15_RW_USERPINS_DIR = 0x000A8100,
    // Read or write the direction of the user pins with a bit vector.
    // The direction is encoded with 0 for tool to device t2d direction and 1 for d2t.
    // read32 returns the current direction of pins. Not existing pins are 0.
    // read64 returns tas_userpins_mask_st. mask shows the pins with direction control.
    // write32 updates the direction of all pins with direction control.
    // write64 updates only the pins, where the mask bit is set.
    // The usage of write32 is discouraged to avoid race conditions for multi-tool setups.
    // If mask includes a pin without direction control, error TAS_ERR_RW_WRITE is returned.
    // However other pins with direction control are updated properly in this case.

    TAS_AM15_RW_USERPINS_CNTRL = 0x000A8400,
    // Read or write the control settings tas_am15_userpins_cntrl_et

    TAS_AM15_RW_ACC_HW_FREQUENCY = 0x000C0100,
    // Read or write the frequency [Hz] of the device access HW clock (JTAG, DAP, SWD, etc.).
    // When the value is written the TasServer chooses the closest possible lower value it can operate. 
    // If too low the lowest supported clock frequency is set.

    TAS_AM15_RW_JTAG_SCAN_MODE_ENABLE = 0x000C1100,
    // Enable native JTAG scan mode
    // The uint32_t value written is reserved for future use
    // The LSB of the read uint32_t value indicates that JTAG scan mode is enabled
    // Note that during native JTAG scan mode regular R/W access to the device is not possible.

    TAS_AM15_W_JTAG_SCAN_MODE_DISABLE = 0x000C1200,
    // Disable native JTAG scan mode
    // The uint32_t value written is reserved for future use

    TAS_AM15_W_JTAG_SET_IR  = 0x000C1300,
    // Select the scan chain with the JTAG instruction register
    // by writing tas_jtag_set_ir_st

    TAS_AM15_W_JTAG_CAPTURE = 0x000C1400,
    // Capture selected JTAG scan chain
    // The uint32_t num_scan_bits value written is the number of scan chain bits shifted 
    // with one or several following DAE_ARW_JTAG_SCAN_MODE_DATA_SHIFT transactions

    TAS_AM15_RW_JTAG_DATA_SHIFT = 0x000C1500,
    // The access HW will shift data in and out of the captured JTAG scan chain
    // The access HW will automatically call Update of the JTAG state machine, when
    // num_scan_bits set with DAE_AW_JTAG_SCAN_MODE_CAPTURE is reached.
    // The data has to be a multiple of 8 (num_scan_bits sets the effective bits).
    // Excess bits are ignored for write and set to 0 for read.
    // Writing TAS_AM15_RW_JTAG_DATA_SHIFT will start the shift operation.
    // Reading, to get the shifted out data is optional.
    // The read, following the write has to use the same data size.

    TAS_AM15_W_JTAG_GENERATE_CLOCK_CYCLES = 0x000C1700,
    // Generate additional clock cycles in RUN TEST IDLE state
    // The uint32_t value written is num_clock_cycles 

    TAS_AM15_W_JTAG_RESET = 0x000C1800,
    // Execute a JTAG reset with the JTAG TAP controller (not the JTAG reset pin)
    // The uint32_t value written is reserved for future use

    TAS_AM15_R_DEVICE_TYPE_ACC_HW = 0x00DD1000,
    // Get the device_type (JTAG ID) which was read by the access HW

    TAS_AM15_RW_DEVICE_TYPE_SET = 0x00DD1080,
    // Set the device_type in the TasServer
    // If not 0:
    // - The TasServer will operate the device according to the given device_type
    // - Output drivers of the access HW will always stay enabled even if no device is present. 
    // If 0, the device_type, which is automatically read by the access HW, is used.

    TAS_AM15_R_TIME_SERVER_START_US = 0x50000080,
    // Time of the TasServer start in micro seconds elapsed since midnight, January 1, 1970
    // Has to be read as a 64 bit value

    TAS_AM15_R_TIME_SINCE_SERVER_START_US = 0x50000090,
    // Time in micro seconds elapsed since TasServer start
    // Has to be read as a 64 bit value
};

enum tas_am15_userpins_cntrl_et : uint32_t {

    TAS_UPC_USERPINS      = 0,  // TAS_UP_ALL_UP (default)

    // Additional control of special function pins (only t2d direction)

    // Control of reset pins
    TAS_UPC_ADD_SFP_RESET = 1,  // TAS_UP_ALL_UP, TAS_UP_SFP_RESET, TAS_UP_SFP_TRSTN

    // Additional control of tool interface pins (TIP)
    TAS_UPC_ADD_SFP_TIP   = 2,  // TAS_UP_ALL_UP, TAS_UP_SFP_RESET, TAS_UP_SFP_JTAG or TAS_UP_SFP_DAP 
};


enum tas_am15_userpins_et : uint32_t {

    TAS_UP_ALL_UP       = 0x0000FFFF,  // All potential userpins of an access HW

    TAS_UP_USR0         = 0x00000001,  // DAP connector: USR0 bidi; OCDS L1 connector: OCDSE t2d
    TAS_UP_USR1         = 0x00000002,  // DAP connector: USR1 bidi
    TAS_UP_USR8         = 0x00000100,  // On-board, FTDI access HW USR8 t2d

    TAS_UP_BRKIN        = 0x00001000,  // OCDS L1 connector: BRKIN  t2d 
    TAS_UP_BRKOUT       = 0x00002000,  // OCDS L1 connector: BRKOUT d2t

    TAS_UP_RUNLED       = 0x00008000,  // Target is running LED on miniWiggler and on-board. Low active.


    TAS_UP_ALL_SFP      = 0xFFFF0000,  // All potential special function pins of an access HW

    // Special function pins added if TAS_UPC_ADD_SFP_RESET
    TAS_UP_SFP_RESET    = 0x00010000,  // Low active reset pin t2d
    TAS_UP_SFP_TRST     = 0x10000000,  // Low active JTAG TRST pin t2d

    // For the following special function pins these rules apply:
    // 1. All are t2d or bidi used in as t2d (automatically switched)
    // 2. The value read back is 0
    // 3. The output drivers of the access HW are automatically enabled if switched off

    // Additional special function pins if TAS_UPC_ADD_SFP_TIP and TAS_DEV_CON_PHYS_JTAG
    TAS_UP_SFP_ALL_JTAG = 0xF0000000,  // All controllable JTAG pins (TRST, TDI, TMS, TCK) t2d
    TAS_UP_SFP_TDI      = 0x20000000,
    TAS_UP_SFP_TMS      = 0x40000000,
    TAS_UP_SFP_TCK      = 0x80000000,

    // Additional special function pins if TAS_UPC_ADD_SFP_TIP and (TAS_DEV_CON_PHYS_DAP or TAS_DEV_CON_PHYS_SWD)
    TAS_UP_SFP_ALL_DAP  = 0x03000000,  // All controllable DAP pins (DAP0, DAP1) t2d
    TAS_UP_SFP_DAP0     = 0x01000000,  // DAP0 or SWDCLK
    TAS_UP_SFP_DAP1     = 0x02000000,  // DAP1 or SWDIO
};


struct tas_userpins_mask_st {
    uint32_t  value;
    uint32_t  mask;
};  // Optional bit mask for TAS_AM15_RW_USERPINS and TAS_AM15_RW_USERPINS_DIR


///////////////////////////////////////////////////////////////////////////////
// JTAG scan mode support

struct tas_jtag_set_ir_st {
    uint32_t  width;
    uint32_t  value;
};  // TAS_AM15_W_JTAG_SET_IR control data


