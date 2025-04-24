const int buttonPins[] = {2, 3, 4, 5, 6, 7, 8, 9};
int buttonState[8];
const int buzzerPin = 12;

const int tones[8] = {262, 294, 330, 349, 262, 294, 330, 349}; // C4, D4, E4, F4

const int maxSequenceLength = 100;
int sequence[maxSequenceLength];
int sequenceLength = 0;

void setup() {
  for (int i = 0; i < 8; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }
  pinMode(buzzerPin, OUTPUT);
  randomSeed(analogRead(A0));
  Serial.begin(9600);
}

void loop() {
  startGame();
}

void startGame() {
  sequenceLength = 0;
  delay(1000);
  while (true) {
    sequence[sequenceLength] = random(0, 4);
    sequenceLength++;

    playSequence();

    if (!getPlayerInput()) {
      gameOver();
      break;
    }

    delay(500);
  }
}

void playSequence() {
  for (int i = 0; i < sequenceLength; i++) {
    playTone(sequence[i]);
    delay(200);
  }
}

void playTone(int index) {
  tone(buzzerPin, tones[index], 300);
  delay(300);
  noTone(buzzerPin);
  delay(100);
}

bool getPlayerInput() {
  for (int i = 0; i < sequenceLength; i++) {
    int input = 4;
    while(input > 3){
      input = waitForButton();
      if (input != sequence[i] && input < 4) {
        return false;
      }
      playTone(input);
    }
  }
  return true;
}

int waitForButton() {
  while (true) {
    for (int i = 0; i < 8; i++) {
      if (digitalRead(buttonPins[i]) == LOW) {
        while (digitalRead(buttonPins[i]) == LOW);
        delay(50);
        return i;
      }
    }
  }
}

void gameOver() {
  for (int i = 0; i < 3; i++) {
    tone(buzzerPin, 150, 200);
    delay(200);
    noTone(buzzerPin);
    delay(100);
  }
}

