/*
  Smoothing

  Reads repeatedly from an analog input, calculating a running moyenne

  created 22 Apr 2007
  by David A. Mellis  <dam@mellis.org>
  modified 9 Apr 2012
  by Tom Igoe

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Smoothing

  **************
  v05 : update la valeur du potard si différebnte de la dernière…
        utilise un lissage des valeurs (le potentiometre n'est pas très stable) sur 30 valeurs
        il reste que parfois le final oscille entre 2 entiers

  TODO: mémoriser les 2 dernières valeurs et vérifier avant de renvoyer la nouvelle

  bricodé par mrbbp
  5 janv. 2023

  **************
  
*/
#include "Keyboard.h"

// Define the number of samples to keep track of. The higher the number, the
// more the readings will be smoothed, but the slower the output will respond to
// the input. Using a constant rather than a normal variable lets us use this
// value to determine the size of the readings array.
const int numReadings = 30;

int readings[numReadings];  // la table des mesures
int readIndex = 0;          // l'index courant de lecture
int total = 0;              // le total des mesures
int moyenne = 0;            // la moyenne

const int potPin = A1; // le potentiometre à lisser
int oVal = -1;
int ooVal = -1;

void setup() {
  // initialise les pin du µc
  pinMode(potPin, INPUT);
  SerialUSB.begin(9600); // initialise le debugage
  // initialize toutes les valeurs de lecture à 0:
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
}

void loop() {
  // lissage
  // subtract the last reading:
  total = total - readings[readIndex];
  // read from the sensor: to stabilize analogRead less 1bit
  readings[readIndex] = analogRead(potPin)/8;
  // add the reading to the total:
  total = total + readings[readIndex];
  // advance to the next position in the array:
  readIndex = readIndex + 1;

  // si à la fin de la table...
  if (readIndex >= numReadings) {
    // ...met l'index au début
    readIndex = 0;
  }

  // calcule de la moyenne:
  moyenne = total / numReadings;
  if (moyenne <= oVal-1 || moyenne >= oVal+1) {
    if (moyenne <= ooVal-1 || moyenne >= ooVal+1) {
      // evite le "flicking" sur 2 valeurs
      Keyboard.println(moyenne);
      // SerialUSB.println(moyenne);
      ooVal = oVal;
      oVal = moyenne;
    }
  }
  // premiere valeur
  if (oVal == -1 || ooVal == -1) {
    ooVal = oVal;
    oVal = moyenne;
    
  }
}
