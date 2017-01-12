#include "Keyboard.h"

void setup() {
  Keyboard.begin();
  delay(400);

  Keyboard.end();
}

void loop() {

}

if (wordArray.length == 1){
  if (comboMap[wordArray[0]] !== undefined){
    commandKnown = true;

    parsedOut = '  typeKey(' + comboMap[wordArray[0]] + ');\n';
  }else if (commandMap[wordArray[0]] !== undefined) {
    commandKnown = true;

    parsedOut = '  typeKey(' + commandMap[wordArray[0]] + ');\n';
  }else {
    commandKnown = false;
    break;
  }
  wordArray.shift();
}
while (wordArray.length){
  if (comboMap[wordArray[0]] !== undefined){
    commandKnown = true;
    releaseAll = true;

    parsedOut += '  Keyboard.press(' + comboMap[wordArray[0]] + ');\n';
  }else if (commandMap[wordArray[0]] !== undefined) {
    commandKnown = true;
    releaseAll = true;

    parsedOut += '  Keyboard.press(' + commandMap[wordArray[0]] + ');\n';
  }else if (keyMap[wordArray[0]] !== undefined) {
    commandKnown = true;
    releaseAll = true;

    parsedOut += '  Keyboard.press(\'' + keyMap[wordArray[0]] + '\');\n';
  }else {
    commandKnown = false;
    break;
  }
  wordArray.shift();
}
