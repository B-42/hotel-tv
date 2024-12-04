#include <Servo.h>

// Servos
const Servo
  SERVO_VAN,
  SERVO_DOOR,
  SERVO_JOHNNY,
  SERVO_JOHNNY2,
  SERVO_QUASIMODO,
  SERVO_CROWD,
  SERVO_TEST;

// Pin values
const int
  PIN_SERVO_VAN       = 2,
  PIN_SERVO_DOOR      = 9,
  PIN_SERVO_JOHNNY    = 4,
  PIN_SERVO_QUASIMODO = 13,
  PIN_SERVO_CROWD     = 8,
  PIN_TAPE_VAN        = 12,
  PIN_TAPE_DOOR       = 3,
  PIN_TAPE_JOHNNY_1   = 6,
  PIN_TAPE_BUTTON     = 7,
  PIN_TAPE_JOHNNY_2   = 10,
  PIN_SERVO_TEST = 8;


// Servo min/max angles
const int
  VAN_MIN = 30,
  VAN_MAX = 85,
  QUASIMODO_MIN = 20,
  QUASIMODO_MAX = 60,
  DOOR_MIN = 0,
  DOOR_MAX = 90;


// Copper tape readings
int
  tapeVan, pTapeVan,
  tapeDoor, pTapeDoor,
  tapeJohnny1, pTapeJohnny1,
  tapeButton, pTapeButton,
  tapeJohnny2, pTapeJohnny2;

void setup() {
  // Attach servos
  SERVO_VAN.attach(PIN_SERVO_VAN);
  SERVO_DOOR.attach(PIN_SERVO_DOOR);
  SERVO_JOHNNY.attach(PIN_SERVO_JOHNNY);
  SERVO_JOHNNY2.attach(PIN_SERVO_JOHNNY);
  SERVO_QUASIMODO.attach(PIN_SERVO_QUASIMODO);
  SERVO_CROWD.attach(PIN_SERVO_CROWD);

  // Set input pins for copper tape
  
  pinMode(PIN_TAPE_JOHNNY_1, INPUT);
  pinMode(PIN_TAPE_JOHNNY_2, INPUT);
  pinMode(PIN_TAPE_BUTTON, INPUT);
  pinMode(PIN_TAPE_VAN, INPUT);
  pinMode(PIN_TAPE_DOOR, INPUT);
  SERVO_VAN.write(VAN_MIN);
  SERVO_QUASIMODO.write(QUASIMODO_MIN);
  SERVO_DOOR.write(DOOR_MIN);
  SERVO_CROWD.write(180);
  SERVO_JOHNNY.write(0);

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
  tapeDoor = digitalRead(PIN_TAPE_DOOR);
  tapeJohnny1 = digitalRead(PIN_TAPE_JOHNNY_1);
  tapeJohnny2 = digitalRead(PIN_TAPE_JOHNNY_2);

  Serial.println(tapeDoor);

  //Scene 1
  //Run Van servo once johnny & monsters tape is connected
  if(SERVO_VAN.read() < VAN_MAX - 5){
    if (tapeJohnny1 == LOW && tapeVan == HIGH) {
        for(int i=VAN_MIN; i<VAN_MAX; i++) {
          SERVO_VAN.write(i);
          delay(20);
      }
    }
  }

  //Scene 2
  //Opem Door once Johnny is spun
  if (tapeDoor == HIGH){
    for(int i=DOOR_MIN; i<DOOR_MAX; i++){
      SERVO_DOOR.write(i);
      delay(20);
    }
  }

  //Scene 3
  //Make Quasimodo sniff once button is pressed
  if(tapeButton == HIGH && tapeButton != pTapeButton) {
      for(int i=QUASIMODO_MIN; i<QUASIMODO_MAX; i++) {
        SERVO_QUASIMODO.write(i);
        delay(10);
      }
  }
  
  //Scene 4
  //Run Servo Crowd once Quasi is spun to expose Johnny
  if(tapeJohnny2 == HIGH && tapeJohnny2 != pTapeJohnny2){
    for(int i=0; i<180; i--){
      SERVO_CROWD.write(i);
      delay(10);
    }
  }
  //Run Johnny Servo once Quasi is spun to expose him
  if(tapeJohnny2 == HIGH && tapeJohnny2 != pTapeJohnny2){
    for(int i=0; i<180; i++){
      SERVO_JOHNNY.write(i);
      delay(10);
    }
  }


  /*
  if(millis() % 10000 == 0) {
    for(int i=0; i<180; i++) {
      SERVO_JOHNNY.write(i);
      SERVO_CROWD.write(i);
      delay(10);
    }
  }
  */

  // Reset previous state memory
  pTapeVan = tapeVan;
  pTapeJohnny1 = tapeJohnny1;
  pTapeButton = tapeButton;
  pTapeJohnny2 = tapeJohnny2;

}