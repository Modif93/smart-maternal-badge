

char normalTopic[] = "BadgeConnTopic";
char emegencyTopic[] = "emergencyTopic";
void setup() {
    
    pinMode(led1, OUTPUT);
    pinMode(led2, OUTPUT);
    
}


void subHandler(const char *event, const char *data)
{
  Serial.println("event=%s data=%s", event, data ? data : "NULL");
}

void loop() {
    
    if(Mesh.ready())
    {
        snprintf(msg, 75, "hello world #%ld", value);
        Mesh.publish(Location,Data);
       
    }
    delay(1000);
}