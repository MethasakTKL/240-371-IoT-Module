int ledPin = 23;
int buttonPin = 19;

int ledState = LOW;
int ISR_count = 0;

void LED_func_ISR(){
    ledState = !ledState;
    digitalWrite(ledPin, ledState);
    ISR_count += 1 ;
}

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  attachInterrupt(buttonPin, LED_func_ISR, RISING);
}

void loop() {
  Serial.printf("Interupt Service %d\n", ISR_count);

}
