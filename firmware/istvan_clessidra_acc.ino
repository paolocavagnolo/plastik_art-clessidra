
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

#define TURN_SPEED 170 //170
#define MIN_SPEED 40 //40
#define TURN_ACC 4 //8

#define LAST_A 200
#define LAST_B 300 //300

#define BACCHETTA_TIME 600

#define SERIAL_BAUD 9600

#define BIG_STEP 430
#define MAX_STEP 2700
#define DEB 500

int steppi[] = {1220};

void setup() {
  //better
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A4, OUTPUT);

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

  digitalWrite(8, HIGH);
  delay(MAX_STEP + 300);
  digitalWrite(8, LOW);

}

int dataIn = 0;
uint8_t pushed = 0;
long steps = 0;
int plm = 0;

void loop() {

  pushed = leggiPulsanti();

  if (Serial.available()) {
    delay(3);
    int lettura[4];
    for (uint8_t i = 0; i < 4; i++) {
      lettura[i] = Serial.read();
      delay(3);
    }
    if (lettura[0] == 97) {
      if (lettura[1] == 100) {
        if (lettura[2] == 101) {
          pushed = lettura[3] - 48;
        }
      }
    }
  }

  // GIRA
  if (pushed == 7) {
    if (!digitalRead(END_LIFT)) {
      turn();
    }
  }
  // SVUOTA
  else if (pushed == 1) {
    digitalWrite(9, HIGH);
    delay(MAX_STEP - steps);
    digitalWrite(9, LOW);
    steps = MAX_STEP;
    delay(DEB);
  }
  // BLOCCA
  else if (pushed == 5) {
    steps = 0;
    digitalWrite(8, HIGH);
    delay(MAX_STEP + 300);
    digitalWrite(8, LOW);
    steps = 0;
  }
  // A
  else if (pushed == 2) {
    if (steps <= (MAX_STEP - steppi[0])) {
      steps = steps + steppi[0];

      digitalWrite(9, HIGH);
      delay(steppi[0]);
      digitalWrite(9, LOW);
    }
    delay(DEB);
  }
  // B
  else if (pushed == 3) {
    if (steps <= (MAX_STEP - BACCHETTA_TIME)) {

      digitalWrite(9, HIGH);
      delay(BACCHETTA_TIME);
      digitalWrite(9, LOW);
      delay(10);
      digitalWrite(8, HIGH);
      delay(BACCHETTA_TIME);
      digitalWrite(8, LOW);

    }
    delay(DEB);
  }
  // C
  else if (pushed == 6) {
    digitalWrite(8, HIGH);
    delay(BIG_STEP);
    digitalWrite(8, LOW);
    delay(DEB);
    steps = steps - BIG_STEP;
  }
  // D
  else if (pushed == 4) {
    if (steps <= (MAX_STEP - BIG_STEP)) {
      steps = steps + BIG_STEP;
      digitalWrite(9, HIGH);
      delay(BIG_STEP);
      digitalWrite(9, LOW);
    }

    delay(DEB);
  }

  else {
    digitalWrite(11, LOW);
    digitalWrite(10, LOW);
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
  }


}

uint8_t leggiPulsanti() {
  const int num_read = 1000;
  uint8_t rd = 0;
  uint8_t sampling[num_read];
  int numero[7] = {0, 0, 0, 0, 0, 0, 0};

  if (!digitalRead(BTN_1) || !digitalRead(BTN_2) || !digitalRead(BTN_3) || !digitalRead(BTN_4) || !digitalRead(BTN_5) || !digitalRead(BTN_6) || !digitalRead(BTN_7)) {

    // riempi un array da 1000
    for (int i = 0; i < num_read; i++) {
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
    for (int i = 0; i < num_read; i++) {
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
    if (numero[massimo - 1] > 700) {
      return massimo;
    }
    else {
      return 0;
    }
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
    delay(TURN_ACC);

  }
  if (s == 11) {
    delay(700);
  }
  else if (s == 10) {
    delay(300);
  }
  // costanza
  while (check() == 0) {
    analogWrite(s, TURN_SPEED);
  }

  if (s == 11) {
    delay(200);
  }
  else if (s == 10) {
    delay(70);
  }

//  // frenata
//  for (int i = TURN_SPEED; i >= MIN_SPEED; i--) {
//
//    analogWrite(s, i);
//
//  }
//  if (s == 11) {
//    //dura
//    delay(LAST_B);
//  }
//  else if (s == 10) {
//    delay(1);
//  }

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



