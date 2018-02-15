// Changement de mode du Si4463

// == INCLUDES ==
#include <SPI.h>
#include "Si446x_defs.h"
#include "Si446x.h"
#include "radio_config_Si4463.h"                // A tester avec différentes config
// ==============


// == ETATS ==
#define RDY 0
#define RX 1
#define TX 2
#define en_RX '1'
#define en_TX '2'
#define en_RDY '3'
// =============
  char EtatPresent = 99;                                                       // Init
  
  
  void setup() {
  // == Configuration I/O pins ==
  pinMode(SI_SS, OUTPUT);                                                     // Config Slave Select
  pinMode(SI_SDN, OUTPUT);                                                    // Config Pin Shutdown
  pinMode(SI_nIRQ, INPUT);                                                    // Entrée lecture si il y a une interruption
  // ============================
  
  // == Initialisation des sorties ==
  digitalWrite(SI_SDN, LOW);                                                  // Initialisation du Shutdown à 0 =>
  // ================================
  
  // == Configuration du SPI ==
  SPI.begin();
  SPI.beginTransaction(SPISettings(SI_SCLK_FREQ_MAX, MSBFIRST, SPI_MODE0));   // SI_SCLK_FREQ_MAX dans le Si446x_defs.h
  Serial.begin(9600);
  // ==========================

  // == Variables local au setup ==
  uint8_t stateBuf[8] , state_chip = 0;
  
  // == Initialisation du CHIP == => doit se trouver en READY avant toute configurations
  while(state_chip != SI_READY) {
        //Serial.println(state_chip, DEC);
        cmd_SDN();
        delay(10);
        si_power_up(SI_NO_PATCH , SI_XTAL , 30000000);
        read_cts();
        lecture_state_info(stateBuf, &state_chip);
        delay(10);        
  }
  state_chip = 99;                         // Etat != pour relecture apres
  const uint8_t siConfigArray_433[] = RADIO_CONFIGURATION_DATA_ARRAY;
  si_load_cfg(siConfigArray_433);          // Chargement config general
  Serial.println("Fin du setup"); 
  Serial.println("");
  EtatPresent = RDY;
}

void loop() {
   char in_cmd = Serial.read();               // Pour recup la commande envoyé par le moniteur serie
   char EtatSuivant = EtatPresent;
   uint8_t stateBuf[8] , state_chip = 0;      // Pour le debug
   uint8_t statusModem[2]={0,0}; // Stores packet handler status/flags
        // == BLOC F ==
        switch(EtatPresent) {
            case RDY :  if(in_cmd == en_TX) { EtatSuivant = TX; }
                        else if(in_cmd == en_RX) { EtatSuivant = RX; }
                        break;
                        
            case TX :   if(in_cmd == en_RDY) { EtatSuivant = RDY; }
                        else if(in_cmd == en_RX) { EtatSuivant = RX; }
                        break;
                        
            case RX :   if(in_cmd == en_RDY) { 
                          EtatSuivant = RDY; 
                          si_state_change(SI_READY);          // Pour bien mettre la puce en mode RDY, sinon tjrs en mode RX
                         }
                        else if(in_cmd == en_TX) { EtatSuivant = TX; }
                        break;
        }
        // ============
        
        // == BLOC M ==
        EtatPresent = EtatSuivant;       
        // ============
        
        // == BLOC G ==
        if(EtatPresent == RX) {
            reception_datas();
        }
        else if(EtatPresent == TX) {
            transmission_datas();
        }
        else if(EtatPresent == RDY);
        // ============

        // == Test ETAT via cmd
        if(in_cmd == '5') {
          lecture_state_info(stateBuf, &state_chip);
          if(state_chip == 3) {
              Serial.println("En RDY");
          }
          else if(state_chip == 7) {
              Serial.println("En TX");
          }
          else if(state_chip == 8) {
              Serial.println("En RX");
          }
        }        
}   

// == FONCTIONS ==
void reception_datas(){
      // == Partie reception ==
      uint8_t numPackets = 64;                                                   // Nombre de paquets a recevoir 
      uint8_t fifoRX[64] = {1,2,3};                                             // Used for received packet data storage
      uint8_t statusModem[2]={0,0} , fifoInfoBuf[2] = {0,0};                                             // Stores packet handler status/flags
      // ======================

      delay(2);
      si_rx_cfg(0,0,0,0,0);                                                     // Chargement config RX
      delay(2);
      si_rx_start();                                                            // Init RX  => CHIP en état RX tant qu'on la pas modifié
                                                              
      
      si_status_ph(0, statusModem);    // Pour recuperer le flag du packet reçu
      si_fifo_info(fifoInfoBuf);
      /*Serial.println("Nb data dans fifo:");
      Serial.println(fifoInfoBuf[0] , DEC);
      Serial.println(fifoInfoBuf[1] , DEC);*/
     
      
      if( (statusModem[0] & 0x10) != 0) {
        Serial.println("Packet en Attente !!");
         si_fifo_read(numPackets, fifoRX);                                         // Read RX fifo buffer and store in byte array
           Serial.print("data[] = ");
          for(int i=0; i<numPackets; i++)
          {
            Serial.print(fifoRX[i], HEX);
            Serial.print(" ");
          }
          Serial.println("");
      }
      delay(20);
      if( (statusModem[1] & SI_PACKET_RX) != 0) {      // oU == SI_PACKET_RX // 0 => 1
           Serial.println(" Packet Recu !!");
           si_fifo_read(numPackets, fifoRX);                                         // Read RX fifo buffer and store in byte array
           Serial.print("data[] = ");
          for(int i=0; i<numPackets; i++)
          {
            Serial.print(fifoRX[i]);//, HEX);
            Serial.print(" ");
          }
          Serial.println("");
      }     
}

void transmission_datas() {
  uint8_t fifoTX[3] = {0xAA,0xAA, 0xAA};
  si_fifo_write(3, fifoTX);
  si_tx_cfg(0, 0, 1, 7, 0, 3) ;
  si_tx_start();
  delay(10);
  /*si_tx_cfg(1, 0, 1, 7, 0, 3) ;
  si_tx_start();
  delay(10);
  si_tx_cfg(2, 0, 1, 7, 0, 3) ;
  si_tx_start();
  delay(10);
  si_tx_cfg(3, 0, 1, 7, 0, 3) ;
  si_tx_start();
  delay(10);*/
}
