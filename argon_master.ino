
    char uuid[17];
    
    
    
    memcpy(uuid, &data[0], 17);
    memcpy(buffer, &data[17], 17);
    
    Log.info("%s %s\n", uuid, buffer);
    
    int i = 0;
    
    if(strcmp(buffer, "pregEmerg") == 0){
        client.publish("pregEmerg", uuid);
    }else if (strcmp(buffer, "pregNom") == 0){
        client.publish("pregNom", uuid);
    }else{
        client.publish("undef", uuid);
    }
}
void setup() {
    
    
    BleCharacteristic myData;
    myData.onDataReceived(onDataReceived, NULL);
    //Serial.begin();
    
    
}
void loop() {
    resultLen = BLE.scan(result, 100);
    
    for(int i = 0; i < resultLen; i++){
        uint8_t uuid[BLE_MAX_ADV_DATA_LEN];
        uint8_t data[BLE_MAX_ADV_DATA_LEN];
        size_t len;
        len = result[i].advertisingData.get(BleAdvertisingDataType::SERVICE_UUID_128BIT_COMPLETE, uuid, BLE_MAX_ADV_DATA_LEN);
        len = result[i].advertisingData.get(BleAdvertisingDataType::SERVICE_DATA, data, BLE_MAX_ADV_DATA_LEN);
        
            if(strcmp(reinterpret_cast<char *>(data), "pregEmerg") == 0){
                client.publish("pregEmerg", reinterpret_cast<char *>(uuid));
            }else if (strcmp(reinterpret_cast<char *>(data), "pregNom") == 0){
                client.publish("pregNom", reinterpret_cast<char *>(uuid));
            }else{
                client.publish("undef", reinterpret_cast<char *>(uuid));
            }
        
    }
    
    if(!client.isConnected()){
        client = MQTT("172.30.1.59", 1883, nullptr);
    }
}
