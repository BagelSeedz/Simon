// C++ code
// David Martinez
// SIMON

// PIN CONSTANTS
const int buttonAnalog = A0;
const int greenButton = 5;
const int yellowButton = 4;
const int blueButton = 3;
const int redButton = 2;
const int piezoPin = 6;
const int greenLED = 7;
const int yellowLED = 8;
const int blueLED = 9;
const int redLED = 10;

// LOGIC CONSTANTS
const int buttonDebounceMaxLoops = 30;
const int redTone = 262; // C4
const int blueTone = 294; // D4
const int yellowTone = 330; // E4
const int greenTone = 370; // FS4
const int startGameTone = 392; // G4
const int endGameTone = 131; // C3

// GAME CONSTANTS
const double delayDivision = 1.1;
const double initialLightDelay = 500;

// LOGIC VARS
int redState = 0;
int blueState = 0;
int yellowState = 0;
int greenState = 0;
bool buttonDebounce = false;
int buttonDebounceLoops = 0;
int lastButtonPressed = 0;
bool buttonDown = false;

// GAME VARS
double lightDelay = initialLightDelay; // YIELDS
int gameRound = 1;
bool gamePlaying = false;
bool awaitingResponse = false;
int indexBeingChecked = 0;
bool gotSomethingCorrect = false;

// MAIN
void setup()
{
  Serial.begin(9600);
  
  pinMode(buttonAnalog, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(piezoPin, OUTPUT);
  
  // Fix Random
  randomSeed(analogRead(piezoPin));
             
  // Allow buttons to be pressed
  activateButtons();
}

void loop()
{
  updateButtonStates();
  fixButtonDown();
  Serial.println("Main Loop");
  // Set up debounce
  if ((redState + blueState + yellowState + greenState) >= 1 && (!(buttonDown))) {
    buttonDown = true;
    lastButtonPressed = getButtonPressed();
    deactivateButtons();
    buttonDebounce = true;
    
    if (!(gamePlaying)) {
      startGame();
    }
  } else if (!(buttonDebounce) && (!(buttonDown))) {
    activateButtons();
  }
  
  if (gamePlaying) {
  	nextRound({});  
  }
}

// METHODS
void activateButtons() {
  digitalWrite(buttonAnalog, HIGH);
}

void deactivateButtons() {
  digitalWrite(buttonAnalog, LOW);
}

int getButtonPressed() {
  if (redState == HIGH) {
    return redButton;
  } else if (blueState == HIGH) {
    return blueButton;
  } else if (yellowState == HIGH) {
    return yellowButton;
  } else if (greenState == HIGH) {
    return greenButton;
  }
  return -1;
}

void lightUpLED(int LED, int freq) {
  digitalWrite(LED, HIGH);
  tone(piezoPin, freq, 1000);
  delay(lightDelay); // REAL DELAY
  digitalWrite(LED, LOW);
  noTone(piezoPin);
  buttonDebounce = false;
  delay(lightDelay/2); // REAL DELAY
}

void playOrder(int order[]) {
  deactivateButtons();

  for (int i = 0; i<gameRound; i++) {
    switch (order[i]) {
      case redButton:
      	lightUpLED(redLED, redTone);
      	break;
      case blueButton:
      	lightUpLED(blueLED, blueTone);
      	break;
      case yellowButton:
      	lightUpLED(yellowLED, yellowTone);
      	break;
      case greenButton:
      	lightUpLED(greenLED, greenTone);
      	break;
    }
  }
  awaitingResponse = true;
  activateButtons();
}

void startGame() {
  digitalWrite(redLED, HIGH);
  digitalWrite(blueLED, HIGH);
  digitalWrite(yellowLED, HIGH);
  digitalWrite(greenLED, HIGH);
  tone(piezoPin, startGameTone, 1000);
  delay(lightDelay * 2); // REAL DELAY
  digitalWrite(redLED, LOW);
  digitalWrite(blueLED, LOW);
  digitalWrite(yellowLED, LOW);
  digitalWrite(greenLED, LOW);
  noTone(piezoPin);
  delay(lightDelay * 2); // REAL DELAY
  gamePlaying = true;
}

void endGame() {
  indexBeingChecked = 0;
  awaitingResponse = false;
  lightDelay = initialLightDelay;
  gameRound = 1;
  digitalWrite(redLED, HIGH);
  digitalWrite(blueLED, HIGH);
  digitalWrite(yellowLED, HIGH);
  digitalWrite(greenLED, HIGH);
  tone(piezoPin, endGameTone, 1000);
  delay(2000);
  digitalWrite(redLED, LOW);
  digitalWrite(blueLED, LOW);
  digitalWrite(yellowLED, LOW);
  digitalWrite(greenLED, LOW);
  noTone(piezoPin);
  delay(1000);
  gamePlaying = false;
}

void updateButtonStates() {
  redState = digitalRead(redButton);
  blueState = digitalRead(blueButton);
  yellowState = digitalRead(yellowButton);
  greenState = digitalRead(greenButton); 
}

void fixButtonDown() {
 switch (lastButtonPressed) {
    case redButton:
      if (redState == LOW) {
        buttonDown = false;
      }
      break;
    case blueButton:
      if (blueState == LOW) {
        buttonDown = false;
      }
      break;
    case yellowButton:
      if (yellowState == LOW) {
        buttonDown = false;
      }
      break;
    case greenButton:
      if (greenState == LOW) {
        buttonDown = false;
      }
      break;
  } 
}


void nextRound(int oldOrder[]) {
  // Create Order
  int gameOrder[gameRound] = {};

  for (int i = 0; i<gameRound-1; i++) {
    gameOrder[i] = oldOrder[i];
  }

  int randomNumber = random(4);
  switch(randomNumber) {
    case 0:
    gameOrder[gameRound-1] = redButton;
    break;
    case 1:
    gameOrder[gameRound-1] = blueButton;
    break;
    case 2:
    gameOrder[gameRound-1] = yellowButton;
    break;
    case 3:
    gameOrder[gameRound-1] = greenButton;
    break;
  }

  playOrder(gameOrder);
  gotSomethingCorrect = false;

  while (!(gotSomethingCorrect)) {
    // Fix Buttons
    updateButtonStates();
    fixButtonDown();
    if ((redState + blueState + yellowState + greenState) >= 1 && (!(buttonDown))) {
      buttonDown = true;
      lastButtonPressed = getButtonPressed();
      deactivateButtons();
      buttonDebounce = true;
    } else if (!(buttonDebounce) && (!(buttonDown))) {
      activateButtons();
    }

    // Light up correct LED
    if ((buttonDebounce) && (lastButtonPressed >= 0) && awaitingResponse) {
      bool correct = false;
      if (lastButtonPressed == gameOrder[indexBeingChecked]) {
        indexBeingChecked++;
        correct = true;
      }

      switch (lastButtonPressed) {
        case redButton:
        lightUpLED(redLED, redTone);
        break;
        case blueButton:
        lightUpLED(blueLED, blueTone);
        break;
        case yellowButton:
        lightUpLED(yellowLED, yellowTone);
        break;
        case greenButton:
        lightUpLED(greenLED, greenTone);
        break;
      }

      if (correct) {
        if (indexBeingChecked > gameRound-1) {
          indexBeingChecked = 0;
          awaitingResponse = false;
          lightDelay = lightDelay/delayDivision;
          gameRound++;
          gotSomethingCorrect = true;

          nextRound(gameOrder);
          break;
        }
      } else {
        endGame();
        break;
      }
    }
  }
}
