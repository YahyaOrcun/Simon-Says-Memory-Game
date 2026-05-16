// ===================== NOTE DEFINITIONS =====================
#define NOTE_B0 31
#define NOTE_C1 33
#define NOTE_CS1 35
#define NOTE_D1 37
#define NOTE_DS1 39
#define NOTE_E1 41
#define NOTE_F1 44
#define NOTE_FS1 46
#define NOTE_G1 49
#define NOTE_GS1 52
#define NOTE_A1 55
#define NOTE_AS1 58
#define NOTE_B1 62
#define NOTE_C2 65
#define NOTE_CS2 69
#define NOTE_D2 73
#define NOTE_DS2 78
#define NOTE_E2 82
#define NOTE_F2 87
#define NOTE_FS2 93
#define NOTE_G2 98
#define NOTE_GS2 104
#define NOTE_A2 110
#define NOTE_AS2 117
#define NOTE_B2 123
#define NOTE_C3 131
#define NOTE_CS3 139
#define NOTE_D3 147
#define NOTE_DS3 156
#define NOTE_E3 165
#define NOTE_F3 175
#define NOTE_FS3 185
#define NOTE_G3 196
#define NOTE_GS3 208
#define NOTE_A3 220
#define NOTE_AS3 233
#define NOTE_B3 247
#define NOTE_C4 262
#define NOTE_CS4 277
#define NOTE_D4 294
#define NOTE_DS4 311
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_FS4 370
#define NOTE_G4 392
#define NOTE_GS4 415
#define NOTE_A4 440
#define NOTE_AS4 466
#define NOTE_B4 494
#define NOTE_C5 523
#define NOTE_CS5 554
#define NOTE_D5 587
#define NOTE_DS5 622
#define NOTE_E5 659
#define NOTE_F5 698
#define NOTE_FS5 740
#define NOTE_G5 784
#define NOTE_GS5 831
#define NOTE_A5 880
#define NOTE_AS5 932
#define NOTE_B5 988
#define NOTE_C6 1047
#define NOTE_CS6 1109
#define NOTE_D6 1175
#define NOTE_DS6 1245
#define NOTE_E6 1319
#define NOTE_F6 1397
#define NOTE_FS6 1480
#define NOTE_G6 1568
#define NOTE_GS6 1661
#define NOTE_A6 1760
#define NOTE_AS6 1865
#define NOTE_B6 1976
#define NOTE_C7 2093
#define NOTE_CS7 2217
#define NOTE_D7 2349
#define NOTE_DS7 2489
#define NOTE_E7 2637
#define NOTE_F7 2794
#define NOTE_FS7 2960
#define NOTE_G7 3136
#define NOTE_GS7 3322
#define NOTE_A7 3520
#define NOTE_AS7 3729
#define NOTE_B7 3951
#define NOTE_C8 4186
#define NOTE_CS8 4435
#define NOTE_D8 4699
#define NOTE_DS8 4978

// ===================== CHOICE & OYUN PIN TANIMLARI =====================
#define CHOICE_OFF    0
#define CHOICE_NONE   0
#define CHOICE_RED    (1 << 0)
#define CHOICE_GREEN  (1 << 1)
#define CHOICE_BLUE   (1 << 2)
#define CHOICE_YELLOW (1 << 3)

#define LED_RED    10
#define LED_GREEN  3
#define LED_BLUE   13
#define LED_YELLOW 5

#define BUTTON_RED    9
#define BUTTON_GREEN  2
#define BUTTON_BLUE   12
#define BUTTON_YELLOW 6

#define BUZZER1 4
#define BUZZER2 7

// ===================== ZORLUK GÖSTERGESİ LED'LERİ =====================
#define LED_DIFF_EASY   A0   // Yeşil LED
#define LED_DIFF_MEDIUM A1   // Sarı LED
#define LED_DIFF_HARD   A2   // Kırmızı LED

// ===================== OYUN PARAMETRELERİ =====================
#define ROUNDS_TO_WIN 9  // 3 Kolay + 3 Orta + 3 Zor = 9 Toplam Tur

// ===================== OYUN DEĞİŞKENLERİ =====================
byte gameBoard[32];
byte gameRound = 0;

// ===================== ZORLUK FONKSİYONLARI =====================

int getEntryTimeLimit() {
  if (gameRound <= 3)  return 5000;  // Kolay
  if (gameRound <= 6)  return 4000;  // Orta
  return 2500;                       // Zor
}

int getPlaybackDelay() {
  if (gameRound <= 3)  return 200;   // Kolay
  if (gameRound <= 6)  return 150;   // Orta
  return 75;                         // Zor
}

int getToneLength() {
  if (gameRound <= 3)  return 200;   // Kolay
  if (gameRound <= 6)  return 150;   // Orta
  return 100;                        // Zor
}

void updateDifficultyLED() {
  if (gameRound <= 3) {
    digitalWrite(LED_DIFF_EASY,   HIGH);
    digitalWrite(LED_DIFF_MEDIUM, LOW);
    digitalWrite(LED_DIFF_HARD,   LOW);
  } else if (gameRound <= 6) {
    digitalWrite(LED_DIFF_EASY,   LOW);
    digitalWrite(LED_DIFF_MEDIUM, HIGH);
    digitalWrite(LED_DIFF_HARD,   LOW);
  } else {
    digitalWrite(LED_DIFF_EASY,   LOW);
    digitalWrite(LED_DIFF_MEDIUM, LOW);
    digitalWrite(LED_DIFF_HARD,   HIGH);
  }
}

void playDifficultyTransition(byte newDiffLED, int toneFreq) {
  digitalWrite(LED_DIFF_EASY,   LOW);
  digitalWrite(LED_DIFF_MEDIUM, LOW);
  digitalWrite(LED_DIFF_HARD,   LOW);

  for (byte i = 0; i < 3; i++) {
    digitalWrite(newDiffLED, HIGH);
    buzz_sound(80, toneFreq);
    digitalWrite(newDiffLED, LOW);
    delay(80);
  }

  digitalWrite(newDiffLED, HIGH);
  buzz_sound(400, toneFreq / 2);
  delay(600);
}

// ===================== SETUP =====================
void setup() {
  pinMode(BUTTON_RED,    INPUT_PULLUP);
  pinMode(BUTTON_GREEN,  INPUT_PULLUP);
  pinMode(BUTTON_BLUE,   INPUT_PULLUP);
  pinMode(BUTTON_YELLOW, INPUT_PULLUP);

  pinMode(LED_RED,    OUTPUT);
  pinMode(LED_GREEN,  OUTPUT);
  pinMode(LED_BLUE,   OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);

  pinMode(BUZZER1, OUTPUT);
  pinMode(BUZZER2, OUTPUT);

  pinMode(LED_DIFF_EASY,   OUTPUT);
  pinMode(LED_DIFF_MEDIUM, OUTPUT);
  pinMode(LED_DIFF_HARD,   OUTPUT);

  digitalWrite(LED_DIFF_EASY,   HIGH);
  digitalWrite(LED_DIFF_MEDIUM, LOW);
  digitalWrite(LED_DIFF_HARD,   LOW);

  if (checkButton() == CHOICE_YELLOW) play_beegees();
  while (checkButton() != CHOICE_NONE);
  play_winner();
}

// ===================== ANA DÖNGÜ =====================
void loop() {
  attractMode();

  setLEDs(CHOICE_RED | CHOICE_GREEN | CHOICE_BLUE | CHOICE_YELLOW);
  delay(1000);
  setLEDs(CHOICE_OFF);
  delay(250);

  if (play_memory()) {
    play_winner();
  } else {
    play_loser();
  }
}

// ===================== BELLEK OYUNU =====================
boolean play_memory(void) {
  randomSeed(millis());
  gameRound = 0;

  updateDifficultyLED();

  while (gameRound < ROUNDS_TO_WIN) {
    add_to_moves(); 

    // 4. tura girerken Orta seviye efekti
    if (gameRound == 4) {
      playDifficultyTransition(LED_DIFF_MEDIUM, 638);
    }
    // 7. tura girerken Zor seviye efekti
    else if (gameRound == 7) {
      playDifficultyTransition(LED_DIFF_HARD, 1136);
    }

    playMoves();

    for (byte currentMove = 0; currentMove < gameRound; currentMove++) {
      byte choice = wait_for_button();
      if (choice == 0) return false;
      if (choice != gameBoard[currentMove]) return false;
    }

    delay(1000);
  }

  return true;
}

// ===================== YARDIMCI FONKSİYONLAR =====================
void playMoves(void) {
  for (byte currentMove = 0; currentMove < gameRound; currentMove++) {
    toner(gameBoard[currentMove], getToneLength());
    delay(getPlaybackDelay());
  }
}

void add_to_moves(void) {
  byte newButton = random(0, 4);
  if      (newButton == 0) newButton = CHOICE_RED;
  else if (newButton == 1) newButton = CHOICE_GREEN;
  else if (newButton == 2) newButton = CHOICE_BLUE;
  else if (newButton == 3) newButton = CHOICE_YELLOW;
  gameBoard[gameRound++] = newButton;
}

void setLEDs(byte leds) {
  digitalWrite(LED_RED,    (leds & CHOICE_RED)    ? HIGH : LOW);
  digitalWrite(LED_GREEN,  (leds & CHOICE_GREEN)  ? HIGH : LOW);
  digitalWrite(LED_BLUE,   (leds & CHOICE_BLUE)   ? HIGH : LOW);
  digitalWrite(LED_YELLOW, (leds & CHOICE_YELLOW) ? HIGH : LOW);
}

byte wait_for_button(void) {
  long startTime = millis();
  while ((millis() - startTime) < getEntryTimeLimit()) {
    byte button = checkButton();
    if (button != CHOICE_NONE) {
      toner(button, 150);
      while (checkButton() != CHOICE_NONE);
      delay(10);
      return button;
    }
  }
  return CHOICE_NONE;
}

byte checkButton(void) {
  if      (digitalRead(BUTTON_RED)    == 0) return CHOICE_RED;
  else if (digitalRead(BUTTON_GREEN)  == 0) return CHOICE_GREEN;
  else if (digitalRead(BUTTON_BLUE)   == 0) return CHOICE_BLUE;
  else if (digitalRead(BUTTON_YELLOW) == 0) return CHOICE_YELLOW;
  return CHOICE_NONE;
}

void toner(byte which, int buzz_length_ms) {
  setLEDs(which);
  switch (which) {
    case CHOICE_RED:    buzz_sound(buzz_length_ms, 1136); break;
    case CHOICE_GREEN:  buzz_sound(buzz_length_ms, 568);  break;
    case CHOICE_BLUE:   buzz_sound(buzz_length_ms, 851);  break;
    case CHOICE_YELLOW: buzz_sound(buzz_length_ms, 638);  break;
  }
  setLEDs(CHOICE_OFF);
}

void buzz_sound(int buzz_length_ms, int buzz_delay_us) {
  long buzz_length_us = buzz_length_ms * (long)1000;
  while (buzz_length_us > (buzz_delay_us * 2)) {
    buzz_length_us -= buzz_delay_us * 2;
    digitalWrite(BUZZER1, LOW);
    digitalWrite(BUZZER2, HIGH);
    delayMicroseconds(buzz_delay_us);
    digitalWrite(BUZZER1, HIGH);
    digitalWrite(BUZZER2, LOW);
    delayMicroseconds(buzz_delay_us);
  }
}

void play_winner(void) {
  setLEDs(CHOICE_GREEN | CHOICE_BLUE);
  winner_sound();
  setLEDs(CHOICE_RED | CHOICE_YELLOW);
  winner_sound();
  setLEDs(CHOICE_GREEN | CHOICE_BLUE);
  winner_sound();
  setLEDs(CHOICE_RED | CHOICE_YELLOW);
  winner_sound();
}

void winner_sound(void) {
  for (byte x = 250; x > 70; x--) {
    for (byte y = 0; y < 3; y++) {
      digitalWrite(BUZZER2, HIGH);
      digitalWrite(BUZZER1, LOW);
      delayMicroseconds(x);
      digitalWrite(BUZZER2, LOW);
      digitalWrite(BUZZER1, HIGH);
      delayMicroseconds(x);
    }
  }
}

void play_loser(void) {
  setLEDs(CHOICE_RED | CHOICE_GREEN);
  buzz_sound(255, 1500);
  setLEDs(CHOICE_BLUE | CHOICE_YELLOW);
  buzz_sound(255, 1500);
  setLEDs(CHOICE_RED | CHOICE_GREEN);
  buzz_sound(255, 1500);
  setLEDs(CHOICE_BLUE | CHOICE_YELLOW);
  buzz_sound(255, 1500);

  digitalWrite(LED_DIFF_EASY,   HIGH);
  digitalWrite(LED_DIFF_MEDIUM, LOW);
  digitalWrite(LED_DIFF_HARD,   LOW);
}

void attractMode(void) {
  while (1) {
    setLEDs(CHOICE_RED);    delay(100); if (checkButton() != CHOICE_NONE) return;
    setLEDs(CHOICE_BLUE);   delay(100); if (checkButton() != CHOICE_NONE) return;
    setLEDs(CHOICE_GREEN);  delay(100); if (checkButton() != CHOICE_NONE) return;
    setLEDs(CHOICE_YELLOW); delay(100); if (checkButton() != CHOICE_NONE) return;
  }
}

// ===================== BEE GEES EASTER EGG =====================
int melody[] = {
  NOTE_G4, NOTE_A4, 0, NOTE_C5, 0, 0, NOTE_G4, 0, 0, 0,
  NOTE_E4, 0, NOTE_D4, NOTE_E4, NOTE_G4, 0,
  NOTE_D4, NOTE_E4, 0, NOTE_G4, 0, 0,
  NOTE_D4, 0, NOTE_E4, 0, NOTE_G4, 0, NOTE_A4, 0, NOTE_C5, 0
};
int noteDuration = 115;
int LEDnumber = 0;

void play_beegees() {
  setLEDs(CHOICE_YELLOW);
  toner(CHOICE_YELLOW, 150);
  setLEDs(CHOICE_RED | CHOICE_GREEN | CHOICE_BLUE);
  while (checkButton() != CHOICE_NONE);
  setLEDs(CHOICE_NONE);
  delay(1000);
  digitalWrite(BUZZER1, LOW);

  while (checkButton() == CHOICE_NONE) {
    for (int thisNote = 0; thisNote < 32; thisNote++) {
      changeLED();
      tone(BUZZER2, melody[thisNote], noteDuration);
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
      noTone(BUZZER2);
    }
  }
}

void changeLED(void) {
  setLEDs(1 << LEDnumber);
  LEDnumber++;
  if (LEDnumber > 3) LEDnumber = 0;
}