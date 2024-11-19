#include <Servo.h>

// Servos
const Servo
  SERVO_VAN,
  SERVO_JOHNNY,
  SERVO_QUASIMODO,
  SERVO_CROWD,
  SERVO_TEST;

// Pin values
const int
  PIN_SERVO_VAN       = 2,
  PIN_SERVO_JOHNNY    = 4,
  PIN_SERVO_QUASIMODO = 13,
  PIN_SERVO_CROWD     = 8,
  PIN_TAPE_VAN        = 12,
  PIN_TAPE_JOHNNY_1   = -1,
  PIN_TAPE_BUTTON     = 7,
  PIN_TAPE_JOHNNY_2   = -1,
  PIN_SERVO_TEST = 8;


// Servo min/max angles
const int
  VAN_MIN = 20,
  VAN_MAX = 80,
  QUASIMODO_MIN = 20,
  QUASIMODO_MAX = 130;


// Copper tape readings
int
  tapeVan, pTapeVan,
  tapeJohnny1, pTapeJohnny1,
  tapeButton, pTapeButton,
  tapeJohnny2, pTapeJohnny2;

void setup() {
  // Attach servos
  SERVO_VAN.attach(PIN_SERVO_VAN);
  SERVO_JOHNNY.attach(PIN_SERVO_JOHNNY);
  SERVO_QUASIMODO.attach(PIN_SERVO_QUASIMODO);
  SERVO_CROWD.attach(PIN_SERVO_CROWD);

  // Set input pins for copper tape
  /*
  pinMode(PIN_TAPE_JOHHNY_1, INPUT);
  pinMode(PIN_TAPE_JOHNNY_2, INPUT);
  */
  pinMode(PIN_TAPE_BUTTON, INPUT);
  pinMode(PIN_TAPE_VAN, INPUT);
  SERVO_VAN.write(VAN_MIN);

  Serial.begin(9600);
}

void loop() {
  /*for(int i=0; i<150; i++) {
    SERVO_TEST.write(i);
    delay(25);
  }*/

  // Read copper tape inputs
  /*
  tapeJohnny1 = digitalRead(PIN_TAPE_JOHNNY_1)
  tapeJohnny2 = digitalRead(PIN_TAPE_JOHNNY_2)

  if(tapeVan == HIGH && tapeVan != pTapeVab) {
    for(int i=25; i<70; i++) {
      SERVO_VAN.write(i);
      delay(10);
    }
  }*/
  tapeButton = digitalRead(PIN_TAPE_BUTTON);
  tapeVan = digitalRead(PIN_TAPE_VAN);

  if(tapeButton == HIGH && tapeButton != pTapeButton) {
    for(int i=30; i<130; i++) {
      SERVO_QUASIMODO.write(i);
      delay(10);
    }
  }

  if(tapeVan == HIGH && tapeVan != pTapeVan) {
    for(int i=VAN_MIN; i<VAN_MAX; i++) {
      SERVO_VAN.write(i);
      delay(20);
    }
  }

  if(millis() % 10000 == 0) {
    for(int i=0; i<180; i++) {
      SERVO_JOHNNY.write(i);
      SERVO_CROWD.write(i);
      delay(10);
    }
  }


  // Reset previous state memory
  pTapeVan = tapeVan;
  pTapeJohnny1 = tapeJohnny1;
  pTapeButton = tapeButton;
  pTapeJohnny2 = tapeJohnny2;

}