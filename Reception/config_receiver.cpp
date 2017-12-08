

void lecture_infos() {
   char i;
   uint8_t buffer_info[8] = {0};
   si_get_info(buffer_info);        // reponse sur 8 octects == PART info API
   Serial.println("Data get_info");
   Serial.println("CHIPREV PART2 PART1 PBUILD ID2 ID1 CUSTOMER ROM");
   for(i=0; i<8; i++){     
     Serial.print(buffer_info[i], HEX);
     Serial.print("  ");
    }
    Serial.println(" ");
    Serial.println(" ");
}