int ledPin = 13;

int pinA = 2;
int pinB = 3;
int pinC = 4;
int pinD = 5;
int pinE = 6;
int pinF = 7;
int pinG = 8;
int C1 = 9;
int C2 = 10;
int C3 = 11;
int C4 = 12;
int LDR_pin = A2; //Declare pin

int isMotionDetected = 0;
byte isMotionExited = 0;

unsigned long last_display_on_time = 0, period_display_on_time = 2000;

unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;
int lastButtonState = LOW;
int buttonState; 

void dispalyDigit(int digit) {
  switch (digit) {
    case 0:
      digitalWrite(pinA, HIGH);
      digitalWrite(pinB, HIGH);
      digitalWrite(pinC, HIGH);
      digitalWrite(pinD, HIGH);
      digitalWrite(pinE, HIGH);
      digitalWrite(pinF, HIGH);
      digitalWrite(pinG, LOW);
      break;
    case 1:
      digitalWrite(pinA, LOW);
      digitalWrite(pinB, HIGH);
      digitalWrite(pinC, HIGH);
      digitalWrite(pinD, LOW);
      digitalWrite(pinE, LOW);
      digitalWrite(pinF, LOW);
      digitalWrite(pinG, LOW);
      break;
    case 2:
      digitalWrite(pinA, HIGH);
      digitalWrite(pinB, HIGH);
      digitalWrite(pinC, LOW);
      digitalWrite(pinD, HIGH);
      digitalWrite(pinE, HIGH);
      digitalWrite(pinF, LOW);
      digitalWrite(pinG, HIGH);
      break;
    case 3:
      digitalWrite(pinA, HIGH);
      digitalWrite(pinB, HIGH);
      digitalWrite(pinC, HIGH);
      digitalWrite(pinD, HIGH);
      digitalWrite(pinE, LOW);
      digitalWrite(pinF, LOW);
      digitalWrite(pinG, HIGH);
      break;
    case 4:
      digitalWrite(pinA, LOW);
      digitalWrite(pinB, LOW);
      digitalWrite(pinC, HIGH);
      digitalWrite(pinD, LOW);
      digitalWrite(pinE, LOW);
      digitalWrite(pinF, HIGH);
      digitalWrite(pinG, HIGH);
      break;
    case 5:
      digitalWrite(pinA, LOW);
      digitalWrite(pinB, LOW);
      digitalWrite(pinC, HIGH);
      digitalWrite(pinD, HIGH);
      digitalWrite(pinE, LOW);
      digitalWrite(pinF, HIGH);
      digitalWrite(pinG, HIGH);
      break;
    case 6:
      digitalWrite(pinA, HIGH);
      digitalWrite(pinB, LOW);
      digitalWrite(pinC, HIGH);
      digitalWrite(pinD, HIGH);
      digitalWrite(pinE, HIGH);
      digitalWrite(pinF, HIGH);
      digitalWrite(pinG, HIGH);
      break;
    case 7:
      digitalWrite(pinA, HIGH);
      digitalWrite(pinB, HIGH);
      digitalWrite(pinC, HIGH);
      digitalWrite(pinD, LOW);
      digitalWrite(pinE, LOW);
      digitalWrite(pinF, LOW);
      digitalWrite(pinG, LOW);
      break;
    case 8:
      digitalWrite(pinA, HIGH);
      digitalWrite(pinB, HIGH);
      digitalWrite(pinC, HIGH);
      digitalWrite(pinD, HIGH);
      digitalWrite(pinE, HIGH);
      digitalWrite(pinF, HIGH);
      digitalWrite(pinG, HIGH);
      break;
    case 9:
      digitalWrite(pinA, HIGH);
      digitalWrite(pinB, HIGH);
      digitalWrite(pinC, HIGH);
      digitalWrite(pinD, LOW);
      digitalWrite(pinE, LOW);
      digitalWrite(pinF, HIGH);
      digitalWrite(pinG, HIGH);
      break;
  }
}
void operateDigitalDisplay(int number) {
  int digit2 = number % 10;
  int digit1 = (number / 10) % 10;
  int digit3 = 0;
  int digit4 = 0;
  if (number < 100 ) {
    digitalWrite(C1, LOW);
    digitalWrite(C2, HIGH);
    digitalWrite(C3, HIGH);
    digitalWrite(C4, HIGH);
    //0
    dispalyDigit(digit1);
    delay(1);               // wait for a second
  }
  //1
  if (number < 100 ) {
    digitalWrite(C1, HIGH);
    digitalWrite(C2, LOW);
    digitalWrite(C3, HIGH);
    digitalWrite(C4, HIGH);
    dispalyDigit(digit2);
    delay(1);               // wait for a second
  }
  if (number > 100 && number < 1000) {
    digitalWrite(C1, HIGH);
    digitalWrite(C2, HIGH);
    digitalWrite(C3, LOW);
    digitalWrite(C4, HIGH);
    dispalyDigit(digit3);
    delay(1);               // wait for a second
  }
  if (number > 1000) {
    digitalWrite(C1, HIGH);
    digitalWrite(C2, HIGH);
    digitalWrite(C3, HIGH);
    digitalWrite(C4, LOW);
    dispalyDigit(digit4);
    delay(1);               // wait for a second
  }
}



float operateLMSensor() {
  const float lmSensorVoltage = analogRead(A0);
  const float temperature = lmSensorVoltage * 0.48828;
  return temperature;
}

void setup() {
  Serial.begin(9600);

  pinMode(ledPin, OUTPUT);

  pinMode(pinA, OUTPUT);
  pinMode(pinB, OUTPUT);
  pinMode(pinC, OUTPUT);
  pinMode(pinD, OUTPUT);
  pinMode(pinE, OUTPUT);
  pinMode(pinF, OUTPUT);
  pinMode(pinG, OUTPUT);
  pinMode(C1, OUTPUT);
  pinMode(C2, OUTPUT);
  pinMode(C3, OUTPUT);
  pinMode(C4, OUTPUT);
  pinMode(LDR_pin, INPUT);  //Define pin as input

}



void loop() {
  //Is PIR motion detected?

  int reading = digitalRead(LDR_pin);
  if (reading != lastButtonState)
  {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay)
  {
    if (reading != buttonState)
    {
      buttonState = reading;
      if (buttonState == HIGH)
      {
        //ledState = !ledState;
        isMotionDetected = 1;
        last_display_on_time = millis();
      }
    }
  }
  lastButtonState = reading;


  
  if(isMotionDetected == 1)
  {
    float temperature = operateLMSensor();
    operateDigitalDisplay(temperature);
    if((millis() - last_display_on_time) > period_display_on_time)
    {
      operateDigitalDisplay(0);
      isMotionDetected = 0;
    }
  }




  //  int isMotionDetected = digitalRead(A2);
  //  if (isMotionDetected == HIGH)
  //  {
  //    float temperature = operateLMSensor();
  //    operateDigitalDisplay(temperature);
  //    Serial.println("Motion Detected !");
  //    isMotionExited = 0;
  //    Serial.print("Current Room Temperature is : ");
  //    Serial.print(temperature);
  //    Serial.println(" *C");
  //    digitalWrite(ledPin, HIGH);
  //  }
  //  else
  //  {
  //    if (isMotionExited == 0)
  //    {
  //      isMotionExited = 1;
  //      Serial.println("Motion Ended !");
  //    }
  //    //operateDigitalDisplay(26.6);
  //    digitalWrite(ledPin, LOW);
  //  }
  //  delay(1);
}
