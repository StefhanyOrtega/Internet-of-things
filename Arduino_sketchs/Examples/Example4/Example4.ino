Sketch 4:
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

  // ROJO 5 VECES

  
 for (int i = 0; i < 5; i++) {
    digitalWrite(LED_RED, HIGH);
    delay(300);           // espera 500 ms
    digitalWrite(LED_RED, LOW);
    delay(300);
  }
  
  // AMARILLO 5 VECES
  

  
 for (int i = 0; i < 5; i++) {
    digitalWrite(LED_YELLOW, HIGH);
    delay(300);           // espera 500 ms
    digitalWrite(LED_YELLOW, LOW);
    delay(300);
  }
  

  // VERDE 5 VECES
  

  
 for (int i = 0; i < 5; i++) {
    digitalWrite(LED_GREEN, HIGH);
    delay(300);           // espera 500 ms
    digitalWrite(LED_GREEN, LOW);
    delay(300);
  }
  


}