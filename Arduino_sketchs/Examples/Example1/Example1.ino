sketch 1:  
int const LED1green = 9;
int const LED2red = 8 ;
int const LED3yellow = 12 ;

void setup()
{
  pinMode(LED1green, OUTPUT);
  pinMode(LED2red, OUTPUT);
  pinMode(LED3yellow, OUTPUT);
}

void loop()
{
  digitalWrite(LED1green, HIGH);
  digitalWrite(LED2red, HIGH);
  digitalWrite(LED3yellow, HIGH);
  delay(100); // Wait for 1000 millisecond(s)
  digitalWrite(LED1green, LOW);
  digitalWrite(LED2red, LOW);
  digitalWrite(LED3yellow, LOW);
  delay(100); // Wait for 1000 millisecond(s)
} }
