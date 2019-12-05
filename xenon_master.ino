
char deviceID[] = "badge22341";
char normalTopic[] = "BadgeConnTopic";
char emerTopic[] = "emergencyTopic";
int emgButton = D2;
volatile int topic = 0;


void setup() {
    pinMode(emgButton,INPUT_PULLUP);
    attachInterrupt(emgButton, EmgHandler,CHANGE,12);
}




void loop() {
    if(Mesh.ready())
    {
        if(topic >= 6)
        {
            Mesh.publish(emerTopic,deviceID);
            topic = 0;
        }
        else
        {
            Mesh.publish(normalTopic,deviceID);
            delay(1200);
        }
    }
    
}
void EmgHandler()
{
    topic++;
}