/**
 * Pin definitions
 */
#define SI_SS 10  // Pin NSEL of transceiver
#define SI_SDN A5 // Pin SDN of transceiver control SHUTDOWN state       // Changement, on prend la pin A5
#define SI_nIRQ 2 // Pin nIRQ pour la lecture des interruptions
#define SI_SCLK_FREQ_MAX 1000000 // SCLK max 1MHZ

/**
 * Main commands
 */
// BOOT_COMMANDS
#define SI_POWER_UP 0x02
// COMMON_COMMANDS
#define SI_READ_CMD_BUFF 0x44 // Command read CTS
#define SI_CTS 0xFF
#define SI_PART_INFO 0x01
#define SI_FUNC_INFO 0x10
#define SI_FIFO_INFO 0x15
#define SI_REQUEST_DEVICE_STATE 0x33
#define SI_CHANGE_STATE 0x34
#define SI_GET_CHIP_STATUS 0x23
#define SI_GET_MODEM_STATUS 0x22
#define SI_GET_PH_STATUS 0x21
#define SI_GET_INT_STATUS 0x20
#define SI_SET_PROPERTY 0x11
#define SI_GET_PROPERTY 0x12
#define SI_GPIO_PIN_CFG 0x13
#define SI_GET_ADC_READING 0x14
#define SI_IRCAL 0x17
#define SI_PROTOCOL_CFG 0x18
// TX_COMMANDS
#define SI_START_TX 0x31
#define SI_WRITE_TX_FIFO 0x66
// RX_COMMANDS
#define SI_START_RX 0x32
#define SI_PACKET_INFO 0x16
#define SI_READ_RX_FIFO 0x77

// Send to si_fifo_info to reset rx/tx fifo's
#define SI_RESET_FIFO_RX 2
#define SI_RESET_FIFO_TX 1

#define SI_FRR_A 0x50
#define SI_FRR_B 0x51
#define SI_FRR_C 0x53
#define SI_FRR_D 0x57
#define SI_FRR_ALL 0xFF

// Group Interrupts
#define SI_CHIP_INT_STATUS 4
#define SI_MODEM_INT_STATUS 2
#define SI_PH_INT_STATUS 1

// Chip Interrupts
#define SI_WUT 1
#define SI_LOW_BATT 2
#define SI_CHIP_READY 4
#define SI_CMD_ERROR 8
#define SI_STATE_CHANGE 0x10
#define SI_FIFO_UNDERFLOW_OVERFLOW_ERROR 0x20 
#define SI_CAL 0x40

// Modem Interrupts
#define SI_INVALID_SYNC 0x20
#define SI_RSSI_JUMP 0x10 
#define SI_RSSI 0x08 
#define SI_INVALID_PREAMBLE 0x04 
#define SI_PREAMBLE_DETECT 0x02 
#define SI_SYNC_DETECT 0x01

// Packet handler Interrupts
#define SI_FILTER_MATCH 0x80
#define SI_FILTER_MISS 0x40
#define SI_PACKET_SENT 0x20
#define SI_PACKET_RX 0x10
#define SI_CRC_ERROR 0x08
#define SI_TX_FIFO_ALMOST_EMPTY 0x02
#define SI_RX_FIFO_ALMOST_FULL 0x01

/**
 * Transceiver Operating States
 */
#define SI_NOCHANGE 0 	// Do not change from previously sent TXCOMPLETE_STATE. (No Change does not have the effect of remaining in TX mode.)
#define SI_SLEEP 1 	// SLEEP or STANDBY state, according to the mode of operotion of the 32K R-C Osc selected by GLOBAL_CLK_CFG:CLK_32K_SEL.
#define SI_SPI_ACTIVE 2 // SPI ACTIVE state.
#define SI_READY 3 	// READY state.
#define SI_READY2 4 	// Another enumeration for READY state.
#define SI_TX_TUNE 5 	// TX_TUNE state.
#define SI_RX_TUNE 6 	// RX_TUNE state.
#define SI_TX 7 		// TX state.
#define SI_RX 8 		// RX state.

#define SI_IMMEDIATE 0 // Start TX immediately.
#define SI_WUT 1		// Start TX upon expiration of the Wake-Up Timer.

/**
 * TX Defines
 */
#define SI_TX_ENUM_0 0 // Send data that has been written to the TX FIFO. If the TX FIFO is empty, a FIFO underflow interrupt will occur.
#define SI_TX_ENUM_1 1 // Send last packet again.

/**
 * Selects the data field whose length will be modified per the LEN[15:0] and LEN_DIFF[15:0] parameters.
 */
#define SI_RX_ENUM_0 0 // Do not override the length of any data fields.
#define SI_RX_ENUM_1 1 // Override the programmed value of PKT_FIELD_1_LENGTH, or the value of RX_LEN in the START_RX command.
#define SI_RX_ENUM_2 2 // Override the programmed value of PKT_FIELD_2_LENGTH. 
#define SI_RX_ENUM_3 4 // Override the programmed value of PKT_FIELD_3_LENGTH. 
#define SI_RX_ENUM_4 8 // Override the programmed value of PKT_FIELD_4_LENGTH. 
#define SI_RX_ENUM_5 16 // Override the programmed value of PKT_FIELD_5_LENGTH. 


/**
 * Boot-time params
 */
#define SI_PATCH 1
#define SI_NO_PATCH 0
#define SI_PRO 1
#define SI_XTAL 0
#define SI_TCXO 1

/**
 * GPIO Config:
 * 
 */
#define SI_GPIO_PULL_SET 0x40

#define SI_GPIO_STATE 0x80

#define SI_GPIO_DONOTHING 0
#define SI_GPIO_TRISTATE 1
#define SI_GPIO_DRIVE0 2
#define SI_GPIO_DRIVE1 3
#define SI_GPIO_INPUT  4
#define SI_GPIO_32K_CLK 5
#define SI_GPIO_BOOT_CLK 6
#define SI_GPIO_DIV_CLK 7
#define SI_GPIO_CTS 8
#define SI_GPIO_INV_CTS 9
#define SI_GPIO_CMD_OVERLAP 10
#define SI_GPIO_SDO 11
#define SI_GPIO_POR 12
#define SI_GPIO_CAL_WUT 13
#define SI_GPIO_WUT 14
#define SI_GPIO_EN_PA 15
#define SI_GPIO_TX_DATA_CLK 16
#define SI_GPIO_RX_DATA_CLK 17
#define SI_GPIO_EN_LNA 18
#define SI_GPIO_TX_DATA 19
#define SI_GPIO_RX_DATA 20
#define SI_GPIO_RX_RAW_DATA 21
#define SI_GPIO_ANTENNA_1_SW 22
#define SI_GPIO_ANTENNA_2_SW 23
#define SI_GPIO_VALID_PREAMBLE 24
#define SI_GPIO_INVALID_PREABLE 25
#define SI_GPIO_SYNC_WORD_DETECT 26
#define SI_GPIO_CCA 27
#define SI_GPIO_IN_SLEEP 28
#define SI_GPIO_TX_STATE 32
#define SI_GPIO_RX_STATE 33
#define SI_GPIO_RX_FIFO_FULL 34
#define SI_GPIO_TX_FIFO_EMPTY 35
#define SI_GPIO_LOW_BATT 36
#define SI_GPIO_CCA_LATCH 37
#define SI_GPIO_HOPPED 38
#define SI_GPIO_HOP_TABLE_WRAP 39
#define SI_GPIO_NIRQ 39

#define SI_GPIO_DRV_HIGH 0
#define SI_GPIO_DRV_MED_HIGH 0x20
#define SI_GPIO_DRV_MED_LOW 0x40
#define SI_GPIO_DRV_LOW 0x60

// ADC channels
#define SI_ADC_TEMPERATURE 0x10
#define SI_ADC_BATTERY_VOLTAGE 0x08
#define SI_ADC_GPIO 0x04
