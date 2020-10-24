#define SWITCH_PORT 4

boolean switchValueBefore = false;

void setup() {
  Serial.begin(115200);
  // put your setup code here, to run once:
  pinMode(SWITCH_PORT, INPUT );
}

void loop() {
  delay(10);
  // put your main code here, to run repeatedly:
  boolean switchValue = digitalRead(SWITCH_PORT);
  if (switchValue != switchValueBefore)
  {
    if (switchValue)
      Serial.println("LED turns on");
    else
      Serial.println("LED turns off");
  }
  switchValueBefore = switchValue;
}
