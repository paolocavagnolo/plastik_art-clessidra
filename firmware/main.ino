#define BTN_1 2 //
#define BTN_2 3
#define BTN_3 A2
#define BTN_4 A5
#define BTN_5 13
#define BTN_6 4
#define BTN_7 12

#define MOTOR_A 11
#define MOTOR_B 10
#define END_A 5
#define END_B 6
#define END_LIFT 7

#define PRESS_SENS A0

#define TURN_SPEED 140 //from 0 to 255
#define MIN_SPEED 60 //from 0 to 255
#define TURN_ACC 8
//microseconds of delay in the foor loop from 0 to TURN_SPEED

#define LAST 1

#define SERIAL_BAUD 9600

void setup() {
  // led
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);

  // read data from raspberry:
  Serial.begin(SERIAL_BAUD);

  // motor
  pinMode(MOTOR_A, OUTPUT);
  pinMode(MOTOR_B, OUTPUT);

  // end switch
  pinMode(END_A, INPUT_PULLUP);
  pinMode(END_B, INPUT_PULLUP);
  pinMode(END_LIFT, INPUT_PULLUP);

  // buttons
  pinMode(BTN_1, INPUT_PULLUP);
  pinMode(BTN_2, INPUT_PULLUP);
  pinMode(BTN_3, INPUT_PULLUP);
  pinMode(BTN_4, INPUT_PULLUP);
  pinMode(BTN_5, INPUT_PULLUP);
  pinMode(BTN_6, INPUT_PULLUP);
  pinMode(BTN_7, INPUT_PULLUP);

  // ev
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);

}

int dataIn = 0;
uint8_t pushed = 0;

void loop() {

  pushed = leggiPulsanti();

  if (Serial.available()) {
    pushed = Serial.read() - 48;
  }
  
  if (pushed == 7) {
    turn();
  }
  else if (pushed == 1) {
    analogWrite(11,25);
    digitalWrite(10,LOW);
  }
  else if (pushed == 5) {
    analogWrite(10,25);
    digitalWrite(11,LOW);
  }
  else if (pushed == 2) {
    digitalWrite(9,HIGH);
  }
  else if (pushed == 6) {
    digitalWrite(8,HIGH);
  }
   else if (pushed == 4) {
    digitalWrite(8,HIGH);
    delay(2700);
    digitalWrite(8,LOW);
    digitalWrite(9,HIGH);
    delay(2700);
    digitalWrite(9,LOW);
  }
  else {
    digitalWrite(11,LOW);
    digitalWrite(10,LOW);
    digitalWrite(8,LOW);
    digitalWrite(9,LOW);
  }



}

uint8_t leggiPulsanti() {

  uint8_t rd = 0;
  uint8_t sampling[10];
  uint8_t numero[7] = {0, 0, 0, 0, 0, 0, 0};

  if (!digitalRead(BTN_1) || !digitalRead(BTN_2) || !digitalRead(BTN_3) || !digitalRead(BTN_4) || !digitalRead(BTN_5) || !digitalRead(BTN_6) || !digitalRead(BTN_7)) {

    // riempi un array da 10
    for (uint8_t i = 0; i < 10; i++) {
      if (!digitalRead(BTN_1)) {
        rd = 1;
      }
      else if (!digitalRead(BTN_2)) {
        rd = 2;
      }
      else if (!digitalRead(BTN_3)) {
        rd = 3;
      }
      else if (!digitalRead(BTN_4)) {
        rd = 4;
      }
      else if (!digitalRead(BTN_5)) {
        rd = 5;
      }
      else if (!digitalRead(BTN_6)) {
        rd = 6;
      }
      else if (!digitalRead(BTN_7)) {
        rd = 7;
      }
      sampling[i] = rd;
    }



    // guarda quello che è piu presente
    for (uint8_t i = 0; i < 10; i++) {
      if (sampling[i] ==  1) {
        numero[0]++;
      }
      else if (sampling[i] == 2) {
        numero[1]++;
      }
      else if (sampling[i] ==  3) {
        numero[2]++;
      }
      else if (sampling[i] ==  4) {
        numero[3]++;
      }
      else if (sampling[i] ==  5) {
        numero[4]++;
      }
      else if (sampling[i] ==  6) {
        numero[5]++;
      }
      else if (sampling[i] ==  7) {
        numero[6]++;
      }
    }
    uint8_t massimo = 0;

    for (uint8_t i = 0; i < 7; i++) {
      for (uint8_t j = 0; j < 7; j++) {
        if ((numero[i] > numero[j]) && (numero[i] >= massimo)) {
          massimo = i + 1;
        }
      }
    }

    return massimo;

  }
  else {
    return 0;
  }


}

void turn() {
  bool fine = false;
  uint8_t s;

  if (check() == 1) {
    s = 11;
  }
  else if (check() == 2) {
    s = 10;
  }
  else {
    return;
  }

  // partenza
  for (int i = 0; i < TURN_SPEED; i++) {
    analogWrite(s, i);
    delay(TURN_ACC*1.2);
  }
  // costanza
  delay(LAST);

  // frenata
  for (int i = TURN_SPEED; i >= MIN_SPEED; i--) {
    if (check() == 0) {
      analogWrite(s, i);
    }
    else {
      digitalWrite(s, LOW);
    }
    delay(TURN_ACC);

  }

  // continua dopo frenata
  while (check() == 0) {
    analogWrite(s, MIN_SPEED);
  }

  digitalWrite(s, LOW);



}


int check() {
  if (!digitalRead(END_A) && digitalRead(END_B)) {
    return 1;
  }
  else if (digitalRead(END_A) && !digitalRead(END_B)) {
    return 2;
  }
  else {
    return 0;
  }
}

void allunga(long timing) {
  digitalWrite(9, HIGH);
  delay(timing);
  digitalWrite(9, LOW);
}

void accorcia(long timing) {
  digitalWrite(8, HIGH);
  delay(timing);
  digitalWrite(8, LOW);
}


