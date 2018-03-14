int State = LOW;
int buttonState;
int lastButtonState = LOW;
unsigned long lastDebounceTime = 0;  
unsigned long debounceDelay = 50;
int rate;
float freq = 1; // hz
int pState = "off";
float sensorMin = 1023;
float sensorMax = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(9, OUTPUT);
  pinMode(10, INPUT);
  Serial.begin(9600);
  calibrate();
}

void loop() {
  // put your main code here, to run repeatedly:
  buttonCheck(); 
  if (State == HIGH){ 
  float x = millis();
  int sensorValue = analogRead(A0);
  Serial.println(sensorValue);
  freq = map(sensorValue,sensorMin,sensorMax,10,.001);
  rate = (127 + 127 * sin(freq * 2*PI*x / 1000));
  analogWrite(9, rate);// turn the LED on (HIGH is the voltage level)
  }
  else{
    analogWrite(9, 0);
  }
}
void buttonCheck(){
int reading = digitalRead(10);
  if (reading != lastButtonState) {
    lastDebounceTime = millis();  // reset the debouncing timer
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == HIGH) {
        State = !State;
      }
    }
  }
  lastButtonState = reading;
 }
 
 void calibrate(){
   while (millis() < 10000){
   int sensor = analogRead(A0);
   sensorMin= min(sensorMin,sensor);
   sensorMax= max(sensorMax,sensor);
   Serial.println(sensorMin);
   }
 }
 
