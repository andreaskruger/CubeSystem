#include <Arduino.h>
#include <wifi.h>
#include <esp_now.h>

uint8_t broadcastAdress[] = {0x94,0xB9,0x7E,0xE6,0x79,0x9C};

String mac_address;
int interupt_state1 = 0;
int interupt_state2 = 0;
int interupt_state3 = 0;

typedef struct struct_message{
    int state;
    int interupt_1;
    int interupt_2;
    int interupt_3;
    int interupt_4;
    int interupt_5;
    int interupt_6;
}struct_message;
 
struct_message msg_to_send;
struct_message msg_incoming;



// Callback when data is sent, triggas när något skickas
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
    if(msg_incoming.interupt_1 == 1){interupt_state1 = 1;}
    else if(msg_incoming.interupt_1 == 0){interupt_state1 = 0;}

    if(msg_incoming.interupt_2 == 1){interupt_state2 = 1;}
    else if(msg_incoming.interupt_2 == 0){interupt_state2 = 0;}

    if(msg_incoming.interupt_3 == 1){interupt_state3 = 1;}
    else if(msg_incoming.interupt_3 == 0){interupt_state3 = 0;}
}

// Callback when data is received, triggas när något mottas (används ej)
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
    memcpy(&msg_incoming, incomingData, sizeof(msg_incoming));
}

void getMACAdress(){
    Serial.println(mac_address);
}

void init_wifi (){
    WiFi.mode(WIFI_MODE_STA);
    WiFi.mode(WIFI_STA);
    mac_address = WiFi.macAddress();
    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
        return;
    }
    
    esp_now_register_send_cb(OnDataSent);
    
    esp_now_peer_info_t peerInfo;
    memcpy(peerInfo.peer_addr, broadcastAdress, 6);
    peerInfo.channel = 0;  
    peerInfo.encrypt = false;
    
    if (esp_now_add_peer(&peerInfo) != ESP_OK){
        Serial.println("Failed to add peer");
        return;
    }
    esp_now_register_recv_cb(OnDataRecv);
}

void send (int inter_1,int inter_2,int inter_3,int inter_4,int inter_5,int inter_6){
    esp_err_t result = esp_now_send(broadcastAdress, (uint8_t *) &msg_to_send, sizeof(msg_to_send));
}