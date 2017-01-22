#include <iostream>
#include <string>
#include <fstream>
using namespace std;

string findKey(string key) {
  int keysLength = 42;
  string keys[keysLength] = {"ESCAPE", "ESC", "GUI", "WINDOWS", "COMMAND", "MENU", "APP", "END", "SPACE", "TAB", "PRINTSCREEN", "ENTER", "RETURN", "UPARROW", "DOWNARROW", "LEFTARROW", "RIGHTARROW", "UP", "DOWN", "LEFT", "RIGHT", "CAPSLOCK", "DELETE", "DEL", "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "F11", "F12", "PAGEUP", "PAGEDOWN", "ALT", "SHIFT", "CTRL", "CONTROL"};
  string keyCodes[keysLength] = {"KEY_LEFT_ESC", "KEY_LEFT_ESC", "KEY_LEFT_GUI", "KEY_LEFT_GUI", "KEY_LEFT_GUI", "229", "229", "KEY_END", "\" \"", "KEY_TAB", "206", "KEY_RETURN", "KEY_RETURN", "KEY_UP_ARROW", "KEY_DOWN_ARROW", "KEY_LEFT_ARROW", "KEY_RIGHT_ARROW", "KEY_UP_ARROW", "KEY_DOWN_ARROW", "KEY_LEFT_ARROW", "KEY_RIGHT_ARROW", "KEY_CAPS_LOCK", "KEY_DELETE", "KEY_DELETE", "KEY_F1", "KEY_F2", "KEY_F3", "KEY_F4", "KEY_F5", "KEY_F6", "KEY_F7", "KEY_F8", "KEY_F9", "KEY_F10", "KEY_F11", "KEY_F12", "KEY_PAGE_UP", "KEY_PAGE_DOWN", "KEY_LEFT_ALT", "KEY_LEFT_SHIFT", "KEY_LEFT_CTRL", "KEY_LEFT_CTRL"};
  for (int i = 0; i < keysLength; i++) if (key == keys[i]) return keyCodes[i];
  return "";
}

int main() {
  int keysLength = 42;
  bool isInLoop = false;

  ifstream inFile;
  ofstream outFile;
  inFile.open("input.txt");
  outFile.open("output/output.ino");

  outFile << "#include \"Keyboard.h\"" << endl << endl;
  outFile << "void typeKey(int key) {" << endl;
  outFile << "  Keyboard.press(key);" << endl;
  outFile << "  delay(50);" << endl;
  outFile << "  Keyboard.release(key);" << endl;
  outFile << "}" << endl << endl;
  outFile << "void setup() {" << endl;
  outFile << "  Keyboard.begin();" << endl;
  outFile << "  delay(500);" << endl;

  while (!inFile.eof()) {
    string inLine;
    getline(inFile, inLine);

    int spaceIndex = inLine.find_first_of(' ');
    string command = inLine.substr(0, spaceIndex);
    cout << command << endl;
    string remain = inLine.substr(spaceIndex+1);
    string outLine = inLine;

    if (!findKey(inLine).empty()) outLine = "  typeKey(" + command + ");";
    else if (command == "STRING") outLine = "  Keyboard.print(\"" + remain + "\");";
    else if (command == "DELAY") outLine = "  delay(" + remain + ");";
    else if (command == "REM") outLine = "  // " + remain;
    else if (command == "LOOP" && !isInLoop) {
      outLine = "}\n\nvoid loop() {";
      isInLoop = true;
    } else if (!findKey(command).empty()) {
      outLine = "  Keyboard.press(" + findKey(command) + "\n";
      while (!remain.empty()) {
        spaceIndex = remain.find_first_of(' ');
        bool foundCommand = false;
        for (int i = 0; i < keysLength; i++) {
          string s = keys[i];
          if (remain.substr(0, spaceIndex) == s) {
            outLine.append("\nKeyboard.press(" + keyCodes[i] + ");");
            foundCommand = true;
            break;
          }
        }
        if (!foundCommand) outLine.append("\nKeyboard.press(\'" + remain.substr(0, spaceIndex) + "\');");
        remain.replace(0, spaceIndex, "");
      }
      if (foundKey) outLine.append("\nKeyboard.releaseAll();");
    }

    outFile << outLine;
    if (!inFile.eof()) outFile << endl << endl;
  }

  outFile << "  Keyboard.end();" << endl;
  outFile << "}" << endl;
  if (!isInLoop) outFile << endl << "void loop() {}" << endl;

  inFile.close();
  outFile.close();
  return 0;
}
