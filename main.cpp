#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>
#include <string.h>
using namespace std;

const int keysLength = 68;
const string keys[keysLength] = {"ESCAPE", "ESC", "GUI", "WINDOWS", "COMMAND", "MENU", "APP", "END", "SPACE", "TAB", "PRINTSCREEN", "ENTER", "RETURN", "UPARROW", "DOWNARROW", "LEFTARROW", "RIGHTARROW", "UP", "DOWN", "LEFT", "RIGHT", "CAPSLOCK", "DELETE", "DEL", "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "F11", "F12", "PAGEUP", "PAGEDOWN", "ALT", "SHIFT", "CTRL", "CONTROL", "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"};
const string keyCodes[keysLength] = {"KEY_LEFT_ESC", "KEY_LEFT_ESC", "KEY_LEFT_GUI", "KEY_LEFT_GUI", "KEY_LEFT_GUI", "229", "229", "KEY_END", "\' \'", "KEY_TAB", "206", "KEY_RETURN", "KEY_RETURN", "KEY_UP_ARROW", "KEY_DOWN_ARROW", "KEY_LEFT_ARROW", "KEY_RIGHT_ARROW", "KEY_UP_ARROW", "KEY_DOWN_ARROW", "KEY_LEFT_ARROW", "KEY_RIGHT_ARROW", "KEY_CAPS_LOCK", "KEY_DELETE", "KEY_DELETE", "KEY_F1", "KEY_F2", "KEY_F3", "KEY_F4", "KEY_F5", "KEY_F6", "KEY_F7", "KEY_F8", "KEY_F9", "KEY_F10", "KEY_F11", "KEY_F12", "KEY_PAGE_UP", "KEY_PAGE_DOWN", "KEY_LEFT_ALT", "KEY_LEFT_SHIFT", "KEY_LEFT_CTRL", "KEY_LEFT_CTRL", "\'a\'", "\'b\'", "\'c\'", "\'d\'", "\'e\'", "\'f\'", "\'g\'", "\'h\'", "\'i\'", "\'j\'", "\'k\'", "\'l\'", "\'m\'", "\'n\'", "\'o\'", "\'p\'", "\'q\'", "\'r\'", "\'s\'", "\'t\'", "\'u\'", "\'v\'", "\'w\'", "\'x\'", "\'y\'", "\'z\'"};

unordered_map<string, string> keyMap;
unordered_map<string, string> argsMap = { // Default args values:
	{"i", "input.txt"}, // input file
	{"o", "output.ino"}, // output file
};

void initKeyMap() {
	for (int i = 0; i < keysLength; i++) {
		keyMap[keys[i]] = keyCodes[i];
	}
}

string findKey(const string& key) {
	unordered_map<string, string>::iterator it = keyMap.find(key);
  return it != keyMap.end() ? it->second : "";
}

void parseArgs(int argc, char** argv) {
	string key = "";
	for (int i = 0; i < argc; i++) {
		if (argv[i][0] == '-') {
			int size = strlen(argv[i]) - 1; // get size of argument key without initial '-'
			if (size == 0) continue; // if not key (only '-'), continue
			key = string(argv[i] + 1); // Copy argument key without initial '-' to key value.
		}
		else if (key.size() > 0) {
			argsMap[key] = string(argv[i]);
			cout << "arg: " << key << " -> " << argsMap[key] << endl;
			key = "";
		}
	}
}

int main(int argc, char** argv) {
	parseArgs(argc, argv);
	initKeyMap();

  bool isInLoop = false;

  ifstream inFile;
  ofstream outFile;
  inFile.open(argsMap["i"]);
  outFile.open(argsMap["o"]);

  if (!inFile.is_open()) { 
  	cerr << endl << "ERROR: Can't open input file \"" << argsMap["i"] << "\"" << endl;
  	return 1;
  }
  if (!outFile.is_open()) {
  	cerr << endl << "ERROR: Can't open output file \"" << argsMap["o"] << "\"" << endl;
  	return 1;
  }

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
      outLine = "";
      while (spaceIndex > 0) {
        spaceIndex = inLine.find_first_of(' ');
        outLine.append("  Keyboard.press(" + findKey(inLine.substr(0, spaceIndex)) + ");\n");
        inLine.replace(0, spaceIndex+1, "");
      }
      outLine.append("  Keyboard.releaseAll();");
    }

    outFile << outLine;
    if (!inFile.eof()) outFile << endl;
  }

  outFile << "  Keyboard.end();" << endl;
  outFile << "}" << endl;
  if (!isInLoop) outFile << endl << "void loop() {}" << endl;

  inFile.close();
  outFile.close();
  return 0;
}