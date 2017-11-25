#!/usr/bin/python

keys = {"ESCAPE": "KEY_LEFT_ESC", "ESC": "KEY_LEFT_ESC", "SPACE": "\' \'", "TAB": "KEY_TAB", "GUI": "KEY_LEFT_GUI", "WINDOWS": "KEY_LEFT_GUI", "COMMAND": "KEY_LEFT_GUI", "MENU": "229", "APP": "229", "ENTER": "KEY_RETURN", "RETURN": "KEY_RETURN", "UP": "KEY_UP_ARROW", "UPARROW": "KEY_UP_ARROW", "DOWN": "KEY_DOWN_ARROW", "DOWNARROW": "KEY_DOWN_ARROW", "LEFT": "KEY_LEFT_ARROW", "LEFTARROW": "KEY_LEFT_ARROW", "RIGHT": "KEY_RIGHT_ARROW", "RIGHTARROW": "KEY_RIGHT_ARROW", "CAPSLOCK": "KEY_CAPS_LOCK", "DELETE": "KEY_DELETE", "DEL": "KEY_DELETE", "PAGEUP": "KEY_PAGE_UP", "PAGEDOWN": "KEY_PAGE_DOWN", "PRINTSCREEN": "206", "END": "KEY_END", "ALT": "KEY_LEFT_ALT", "LALT": "KEY_LEFT_ALT", "RALT": "KEY_RIGHT_ALT", "SHIFT": "KEY_LEFT_SHIFT", "LSHIFT": "KEY_LEFT_SHIFT", "RSHIFT": "KEY_RIGHT_SHIFT", "CTRL": "KEY_LEFT_CTRL", "LCTRL": "KEY_LEFT_CTRL", "RCTRL": "KEY_RIGHT_CTRL", "CONTROL": "KEY_LEFT_CTRL", "F1": "KEY_F1", "F2": "KEY_F2", "F3": "KEY_F3", "F4": "KEY_F4", "F5": "KEY_F5", "F6": "KEY_F6", "F7": "KEY_F7", "F8": "KEY_F8", "F9": "KEY_F9", "F10": "KEY_F10", "F11": "KEY_F11", "F12": "KEY_F12", "a": "\'a\'", "b": "\'b\'", "c": "\'c\'", "d": "\'d\'", "e": "\'e\'", "f": "\'f\'", "g": "\'g\'", "h": "\'h\'", "i": "\'i\'", "j": "\'j\'", "k": "\'k\'", "l": "\'l\'", "m": "\'m\'", "n": "\'n\'", "o": "\'o\'", "p": "\'p\'", "q": "\'q\'", "r": "\'r\'", "s": "\'s\'", "t": "\'t\'", "u": "\'u\'", "v": "\'v\'", "w": "\'w\'", "x": "\'x\'", "y": "\'y\'", "z": "\'z\'"}

inFile = open("input.txt", "r")
outFile = open("output.ino", "w")

outFile.write("#include \"Keyboard.h\"\n\n")
outFile.write("void typeKey(int key) {\n")
outFile.write("	Keyboard.press(key);\n")
outFile.write("	delay(50);\n")
outFile.write("	Keyboard.release(key);\n")
outFile.write("}\n\n")
outFile.write("void setup() {\n")
outFile.write("	Keyboard.begin();\n")
outFile.write("	delay(500);\n")

isInLoop = False

for line in inFile:
	line = line[:-1]
	if line.find(" ") > 0: command = line[:line.find(" ")]
	else: command = line
	remain = line[line.find(" ")+1:]

	if keys.has_key(line):
		outFile.write("	typeKey(" + keys[line] + ");")

	elif command == "STRING":
		remain = remain.replace("\\", "\\\\")
		remain = remain.replace("\"", "\\\"")
		outFile.write("	Keyboard.print(\"" + remain + "\");")

	elif command == "DELAY":
		outFile.write("	delay(" + remain + ");")

	elif command == "REM":
		outFile.write("	// " + remain)

	elif command == "LOOP" and not isInLoop:
		outFile.write("}\n\nvoid loop() {")
		isInLoop = True

	elif keys.has_key(command):
		while len(line) > 0:
			space = line.find(" ")
			if space < 0: space = len(line)
			outFile.write("	Keyboard.press(" + keys[line[:space]] + ");\n")
			line = line[space+1:]
		outFile.write("	Keyboard.releaseAll();")

	else:
		outFile.write(line)

	outFile.write("\n")

outFile.write("	Keyboard.end();\n")
outFile.write("}\n")
if not isInLoop:
	outFile.write("\nvoid loop() {}\n")

inFile.close()
outFile.close()
