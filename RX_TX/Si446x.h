#include "Si446x_defs.h"
#include <SPI.h>

// Pre-built config file transfer
void si_apply_patch(uint8_t patchArray[][8]) ;
uint8_t si_load_cfg(uint8_t* cmdArray);

// Power-up and calibration
uint8_t si_power_up(char patch_to_apply, char ext_xtal, unsigned long int xo_freq);
uint8_t si_ir_cal(uint8_t stepSize, uint8_t rssiAvg, uint8_t rxSet1, uint8_t rxSet2) ;

// Manual property read/override, and gpio config
uint8_t si_property_set(uint8_t propGroup, uint8_t numProps, uint8_t startProp, uint8_t* propData);
uint8_t si_property_get(uint8_t propGroup, uint8_t numProps, uint8_t startProp, uint8_t* propData) ;
uint8_t si_gpio_cfg(uint8_t* gpioSet, uint8_t nIrq, uint8_t sdo, uint8_t driveStrength, uint8_t* gpioData);

// Chip info: model, mask, rom, revision and patch applied
uint8_t si_get_info(uint8_t* infobuf) ;
uint8_t si_get_func(uint8_t* funcbuf);

// TX and RX start/cfg
uint8_t si_tx_start(void) ;
uint8_t si_tx_cfg(uint8_t channel, uint8_t nextState, uint8_t retransmit, uint16_t length, uint8_t pktDelay, uint8_t pktRepeat) ;

uint8_t si_rx_start(void) ;
uint8_t si_rx_cfg(uint8_t channel, uint16_t length, uint8_t timeoutState, uint8_t validState, uint8_t invalidState);

// FIFO and packet handling
uint8_t si_fifo_info(uint8_t* fifoInfoBuf);
void si_fifo_write(uint8_t size, uint8_t* fifobytes) ;
void si_fifo_read(uint8_t size, uint8_t* fifobytes) ;
uint8_t si_packet_info(uint8_t* packetLen);

// Chip operating state info/override
uint8_t si_state_info(uint8_t* stateBuf);
uint8_t si_state_change(uint8_t nextState);

// Chip/Modem/Packet Interrupts
uint8_t si_status_chip(uint8_t clearId, uint8_t* chipInterrupts) ;
uint8_t si_status_modem(uint8_t clearId, uint8_t* modemStatus);
uint8_t si_status_ph(uint8_t clearId, uint8_t* phStatus) ;
uint8_t si_status(uint8_t* clearIds, uint8_t* intStatus);

// Misc functions
uint8_t si_adc_read(uint8_t sources, uint8_t* adcData);
void si_read_frr(uint8_t frrId, uint8_t* frrBytes);
uint8_t si_get_cmd(uint8_t buffer_size, uint8_t* cmdbuf) ;

// Fonctions ajoutées
void reset_fifo(uint8_t* fifoInfoBuf , uint8_t SI_RESET_FIFO_XX);
void cmd_SDN();
uint8_t read_cts();
void lecture_state_info(uint8_t *stateBuf,  char *state_chip);
