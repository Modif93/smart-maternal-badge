
char deviceID[] = "badge23243";
char normalTopic[] = "BadgeConnTopic";
char emegencyTopic[] = "emergencyTopic";
int emgButton = D2;
volatile int topic = 0;


void setup() {
    pinMode(emgButton,INPUT_PULLUP);
    attachInterrupt(emgButton, EmgHandler, CHANGE);
}




void loop() {
    
    if(Mesh.ready())
    {
        if(topic >= 6)
        {
            Mesh.publish(emegencyTopic,deviceID);
            topic = 0;
        }
        else if(topic == 0)
        {
            Mesh.publish(normalTopic,deviceID);
            delay(2500);
        }
    }
    
}
void EmgHandler(const char *event, const char *data)
{
    topic++;
}