char opt;
int const LED_RED =13;

void menu (){
Serial.println("Main menu ");
Serial.println("[1]. Turn on led red ");
Serial.println("[2]. Turn off led red ");
Serial.println("press any option: ");
}

void setup() {
  pinMode (LED_RED,OUTPUT);
Serial.begin(9600);
 Serial.println("WELCOME");
   Serial.println("press any key to show menu");

}
void loop (){

  if (Serial.available() >0){
    menu();
    opt = Serial.read();
   
    if (opt == '1')
      digitalWrite (LED_RED, HIGH);
    if (opt == '2')
      digitalWrite ( LED_RED, LOW);
}
}
