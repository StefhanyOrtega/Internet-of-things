// Ciclar modos con cada pulsación (INPUT_PULLUP), debounce con millis,
// parpadeo no bloqueante, y compatibilidad con la interfaz Serial.

const int BTN_PIN = 2;
const int LED_RED = 11;   // rojo
const int LED_YEL = 12;   // amarillo
const int LED_GRN = 13;   // verde

const unsigned long DEBOUNCE_DELAY = 50;   // ms anti-rebote
const unsigned long BLINK_INTERVAL  = 300; // ms parpadeo

// button state
int lastRawButton = HIGH;
int buttonState = HIGH;
unsigned long lastDebounceTime = 0;

// modos
enum Mode {
  MODE_MANUAL,
  MODE_RED_ONLY,
  MODE_GREEN_ONLY,
  MODE_YELLOW_ONLY,
  MODE_ALL_OFF,
  MODE_ALL_ON,
  MODE_BLINK
};

const int NUM_CYCLE_MODES = 6; // modos que recorrerá el botón: RED, GREEN, YELLOW, ALL_OFF, ALL_ON, BLINK
int modeIndex = 0;            // 0..5
Mode currentMode = MODE_MANUAL;

// estados manuales (cuando operas por Serial con encender/apagar individuales)
bool ledRedState = false;
bool ledYelState = false;
bool ledGrnState = false;

// blinking
unsigned long lastBlinkMillis = 0;
bool blinkOn = false;

void setup() {
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_YEL, OUTPUT);
  pinMode(LED_GRN, OUTPUT);
  pinMode(BTN_PIN, INPUT_PULLUP);

  Serial.begin(9600);
  Serial.println("Welcome");
  Serial.println("Press any key to show menu...");
  setAllOff();
}

void loop() {
  handleButtonCycle();   // detecta pulsación y avanza al siguiente modo
  handleSerial();        // si hay entrada serial, procesa y puede cambiar modo
  applyMode();           // aplica el modo actual (sin delay)
}

/* ---------- BUTTON: cada pulsacion avanza al siguiente modo ---------- */
void handleButtonCycle() {
  int raw = digitalRead(BTN_PIN); // HIGH en reposo, LOW al presionar

  if (raw != lastRawButton) {
    lastDebounceTime = millis();
  }

  if (millis() - lastDebounceTime > DEBOUNCE_DELAY) {
    if (raw != buttonState) {
      buttonState = raw;
      // contamos sólo en la transición a PRESSED (HIGH->LOW)
      if (buttonState == LOW) {
        // avanzar al siguiente modo cíclicamente
        modeIndex = (modeIndex + 1) % NUM_CYCLE_MODES;
        switch (modeIndex) {
          case 0: currentMode = MODE_RED_ONLY;    Serial.println("Button -> MODE_RED_ONLY");    break;
          case 1: currentMode = MODE_GREEN_ONLY;  Serial.println("Button -> MODE_GREEN_ONLY");  break;
          case 2: currentMode = MODE_YELLOW_ONLY; Serial.println("Button -> MODE_YELLOW_ONLY"); break;
          case 3: currentMode = MODE_ALL_OFF;     Serial.println("Button -> MODE_ALL_OFF");     break;
          case 4: currentMode = MODE_ALL_ON;      Serial.println("Button -> MODE_ALL_ON");      break;
          case 5: currentMode = MODE_BLINK;       Serial.println("Button -> MODE_BLINK");       break;
        }
        // reiniciar variables de blink para comportamiento consistente
        lastBlinkMillis = millis();
        blinkOn = false;
      }
    }
  }
  lastRawButton = raw;
}

/* ---------- SERIAL: menú y control (mantiene compatibilidad con el menu original) ---------- */
void handleSerial() {
  if (Serial.available() > 0) {
    char c = Serial.read();
    if (c == '\r' || c == '\n') return;
    menu();

    switch (c) {
      case '1': // Turn on led red -> lo mapeo a RED_ONLY (coincide con ciclo botón)
        currentMode = MODE_RED_ONLY;
        modeIndex = 0;
        Serial.println("Serial: RED ONLY");
        break;
      case '2': // Turn off led red (manual)
        ledRedState = false;
        currentMode = MODE_MANUAL;
        Serial.println("Serial: RED OFF (manual)");
        break;
      case '3': // Turn on led yellow -> YELLOW_ONLY
        currentMode = MODE_YELLOW_ONLY;
        modeIndex = 2;
        Serial.println("Serial: YELLOW ONLY");
        break;
      case '4': // Turn off led yellow (manual)
        ledYelState = false;
        currentMode = MODE_MANUAL;
        Serial.println("Serial: YELLOW OFF (manual)");
        break;
      case '5': // Turn on led green -> GREEN_ONLY
        currentMode = MODE_GREEN_ONLY;
        modeIndex = 1;
        Serial.println("Serial: GREEN ONLY");
        break;
      case '6': // Turn off led green (manual)
        ledGrnState = false;
        currentMode = MODE_MANUAL;
        Serial.println("Serial: GREEN OFF (manual)");
        break;
      case '7': // Turn on all
        setAllOn();
        currentMode = MODE_ALL_ON;
        modeIndex = 4;
        Serial.println("Serial: ALL ON");
        break;
      case '8': // Turn off all
        setAllOff();
        currentMode = MODE_ALL_OFF;
        modeIndex = 3;
        Serial.println("Serial: ALL OFF");
        break;
      case '9': // Intermitence
        currentMode = MODE_BLINK;
        modeIndex = 5;
        lastBlinkMillis = millis();
        blinkOn = false;
        Serial.println("Serial: BLINK MODE");
        break;
      default:
        Serial.print("Unknown option: "); Serial.println(c);
    }
  }
}

/* ---------- Aplicar modo (no bloqueante) ---------- */
void applyMode() {
  switch (currentMode) {
    case MODE_MANUAL:
      digitalWrite(LED_RED,  ledRedState ? HIGH : LOW);
      digitalWrite(LED_YEL,  ledYelState ? HIGH : LOW);
      digitalWrite(LED_GRN,  ledGrnState ? HIGH : LOW);
      break;

    case MODE_RED_ONLY:
      digitalWrite(LED_RED, HIGH);
      digitalWrite(LED_YEL, LOW);
      digitalWrite(LED_GRN, LOW);
      break;

    case MODE_GREEN_ONLY:
      digitalWrite(LED_RED, LOW);
      digitalWrite(LED_YEL, LOW);
      digitalWrite(LED_GRN, HIGH);
      break;

    case MODE_YELLOW_ONLY:
      digitalWrite(LED_RED, LOW);
      digitalWrite(LED_YEL, HIGH);
      digitalWrite(LED_GRN, LOW);
      break;

    case MODE_ALL_OFF:
      setAllOff();
      break;

    case MODE_ALL_ON:
      setAllOn();
      break;

    case MODE_BLINK:
      if (millis() - lastBlinkMillis >= BLINK_INTERVAL) {
        lastBlinkMillis = millis();
        blinkOn = !blinkOn;
        digitalWrite(LED_RED,  blinkOn ? HIGH : LOW);
        digitalWrite(LED_YEL,  blinkOn ? HIGH : LOW);
        digitalWrite(LED_GRN,  blinkOn ? HIGH : LOW);
      }
      break;
  }
}

/* ---------- util ---------- */
void setAllOff() {
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_YEL, LOW);
  digitalWrite(LED_GRN, LOW);
  ledRedState = ledYelState = ledGrnState = false;
}

void setAllOn() {
  digitalWrite(LED_RED, HIGH);
  digitalWrite(LED_YEL, HIGH);
  digitalWrite(LED_GRN, HIGH);
  ledRedState = ledYelState = ledGrnState = true;
}

void menu() {
  Serial.println("\nMain menu");
  Serial.println("1. Turn on led red");
  Serial.println("2. Turn off led red");
  Serial.println("3. Turn on led yellow");
  Serial.println("4. Turn off led yellow");
  Serial.println("5. Turn on led green");
  Serial.println("6. Turn off led green");
  Serial.println("7. Turn on all");
  Serial.println("8. Turn off all");
  Serial.println("9. Intermitence");
  Serial.print("Press any option: ");
}
