sketch 3:
// C++ code
int const LED_GREEN = 9;
int const LED_RED = 8;
int const LED_YELLOW = 12;

void setup() {
  // put your setup code here, to run once:
pinMode(LED_GREEN, OUTPUT);
pinMode(LED_RED, OUTPUT);
pinMode(LED_YELLOW, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  
digitalWrite(LED_RED, HIGH);
delay(500);
digitalWrite(LED_RED, LOW);
  
  
digitalWrite(LED_YELLOW, HIGH);
delay(500);
digitalWrite(LED_YELLOW, LOW);
  
digitalWrite(LED_GREEN, HIGH);
delay(500);
digitalWrite(LED_GREEN, LOW);

}