// This #include statement was automatically added by the Particle IDE.
#include <MQTT.h>

//#define stationType //0 as metro, 1 as bus 



#define trasportType 0 //0 as metro, 1 as bus 
#define carNumber 5545
//#define stationNumber 22523



long lastMsg = 0;
char status[50];
char recvBadge[60];
char sendBadge[30];
char deviceInfo[50];
int value = 0;
int seatNum = 0;
void callback(char* topic, byte* payload, unsigned int length);
bool emergency;

char deviceID[] = "gatway1151231";
/**
 * if want to use IP address,
 * byte server[] = { XXX,XXX,XXX,XXX };
 * MQTT client(server, 1883, callback);
 * want to use domain name,
 * exp) iot.eclipse.org is Eclipse Open MQTT Broker: https://iot.eclipse.org/getting-started
 * MQTT client("iot.eclipse.org", 1883, callback);
 **/
MQTT client("172.30.1.59", 1883, callback);

// for QoS2 MQTTPUBREL message.
// this messageid maybe have store list or array structure.
uint16_t qos2messageid = 0;

//

// receive message ==> for debugging

void setup() {
    Serial.begin(); //via usb serial
    Serial.println("starting Serial");
    RGB.control(true);
    emergency =false;
    // connect to the server
    client.connect(deviceID); //connect as argonGateway id


    // publish/subscribe
    Mesh.subscribe("BadgeConnTopic", BadgeHandler);
    Mesh.subscribe("emergencyTopic",BadgeHandler);
    if (client.isConnected()) {
        if(trasportType)
            snprintf(deviceInfo,50,"metro%04d",carNumber);
        else
            snprintf(deviceInfo,50,"bus%04d",carNumber);




        client.publish("onConnTopic", deviceInfo);
        client.subscribe("recvTranportInfo");
    }
    else
    {
        Serial.println("not Connected");
    }
        
}

void callback(char* topic, byte* payload, unsigned int length) {
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
    for (int i = 0; i < length; i++) {
        Serial.print((char)payload[i]);
    }
    Serial.println();


}

void BadgeHandler(const char *event, const char *data)
{
    if(event=="emergencyTopic")
    {
        Serial.printlnf("emergency on badge %s",data);
        
        if(client.isConnected())
        {
            client.publish("pregEmerg",data);
        }
        Serial.printlnf(".. send to broker");
        emergency = true;
    }
    else{
        Serial.printlnf("event : %s  badge ID : %s",event,data);
    }
}



void reconnect() {
  // Loop until we're reconnected
    while (!client.isConnected()) {
        Serial.print("Attempting MQTT connection...");
        // Attempt to connect
        if (client.connect(deviceID)) {
        Serial.println("connected");
        // Once connected, republish an announcement...
        client.publish("onConnTopic", deviceInfo);
        // ... and resubscribe
        client.subscribe("recvTranportInfo");

        } else {
            Serial.print("failed, rc=");
            Serial.print(client.isConnected());
            Serial.println("... try again in 5 seconds");
            // Wait 5 seconds before retrying
            delay(5000);
        }
    }
}




void loop() {
    if (!client.isConnected())
        reconnect();
    client.loop();
    delay(1000);
    snprintf (status, 75, "%d/%d/%s",carNumber,seatNum,deviceID); //if seatNumber == 0 => not sitting
    
    
    if(!emergency){
        Serial.print("Publish message: ");
        Serial.println(status);
        client.publish("pregNom", status);
    }
  
}

