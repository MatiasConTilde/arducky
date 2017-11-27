#!/usr/bin/python

keys = {"ESCAPE": "KEY_LEFT_ESC", "ESC": "KEY_LEFT_ESC", "SPACE": "\' \'", "TAB": "KEY_TAB", "GUI": "KEY_LEFT_GUI", "WINDOWS": "KEY_LEFT_GUI", "COMMAND": "KEY_LEFT_GUI", "MENU": "229", "APP": "229", "ENTER": "KEY_RETURN", "RETURN": "KEY_RETURN", "UP": "KEY_UP_ARROW", "UPARROW": "KEY_UP_ARROW", "DOWN": "KEY_DOWN_ARROW", "DOWNARROW": "KEY_DOWN_ARROW", "LEFT": "KEY_LEFT_ARROW", "LEFTARROW": "KEY_LEFT_ARROW", "RIGHT": "KEY_RIGHT_ARROW", "RIGHTARROW": "KEY_RIGHT_ARROW", "CAPSLOCK": "KEY_CAPS_LOCK", "DELETE": "KEY_DELETE", "DEL": "KEY_DELETE", "PAGEUP": "KEY_PAGE_UP", "PAGEDOWN": "KEY_PAGE_DOWN", "PRINTSCREEN": "206", "END": "KEY_END", "ALT": "KEY_LEFT_ALT", "LALT": "KEY_LEFT_ALT", "RALT": "KEY_RIGHT_ALT", "SHIFT": "KEY_LEFT_SHIFT", "LSHIFT": "KEY_LEFT_SHIFT", "RSHIFT": "KEY_RIGHT_SHIFT", "CTRL": "KEY_LEFT_CTRL", "LCTRL": "KEY_LEFT_CTRL", "RCTRL": "KEY_RIGHT_CTRL", "CONTROL": "KEY_LEFT_CTRL", "F1": "KEY_F1", "F2": "KEY_F2", "F3": "KEY_F3", "F4": "KEY_F4", "F5": "KEY_F5", "F6": "KEY_F6", "F7": "KEY_F7", "F8": "KEY_F8", "F9": "KEY_F9", "F10": "KEY_F10", "F11": "KEY_F11", "F12": "KEY_F12", "a": "\'a\'", "b": "\'b\'", "c": "\'c\'", "d": "\'d\'", "e": "\'e\'", "f": "\'f\'", "g": "\'g\'", "h": "\'h\'", "i": "\'i\'", "j": "\'j\'", "k": "\'k\'", "l": "\'l\'", "m": "\'m\'", "n": "\'n\'", "o": "\'o\'", "p": "\'p\'", "q": "\'q\'", "r": "\'r\'", "s": "\'s\'", "t": "\'t\'", "u": "\'u\'", "v": "\'v\'", "w": "\'w\'", "x": "\'x\'", "y": "\'y\'", "z": "\'z\'"}

in_file = open("input.txt", "r")
out_file = open("output.ino", "w")

out_file.write("#include \"Keyboard.h\"\n\n")
out_file.write("void typeKey(int key) {\n")
out_file.write("	Keyboard.press(key);\n")
out_file.write("	delay(50);\n")
out_file.write("	Keyboard.release(key);\n")
out_file.write("}\n\n")
out_file.write("void setup() {\n")
out_file.write("	Keyboard.begin();\n")
out_file.write("	Mouse.begin();\n")
out_file.write("	delay(500);\n\n")

in_loop = False
default_delay = 0

for line in in_file:
	line = line[:-1]
	words = line.split(" ")
	remain = line[line.find(" ")+1:]

	if keys.has_key(line):
		out_file.write("	typeKey(" + keys[line] + ");\n")

	elif words[0] == "STRING":
		remain = remain.replace("\\", "\\\\")
		remain = remain.replace("\"", "\\\"")
		out_file.write("	Keyboard.print(\"" + remain + "\");\n")

	elif words[0] == "DELAY":
		out_file.write("	delay(" + remain + ");\n")

	elif words[0] == "DEFAULTDELAY" or words[0] == "DEFAULT_DELAY":
		default_delay = int(remain);

	elif words[0] == "REM":
		out_file.write("	// " + remain + "\n")

	elif words[0] == "LOOP" and not in_loop:
		out_file.write("}\n\nvoid loop() {\n")
		in_loop = True

	elif words[0] == "MOUSE":
		if words[1] == "CLICK":
			if len(words) > 2:
				if words[2] == "LEFT":
					out_file.write("	Mouse.click(MOUSE_LEFT);\n")
				if words[2] == "RIGHT":
					out_file.write("	Mouse.click(MOUSE_RIGHT);\n")
				if words[2] == "MIDDLE":
					out_file.write("	Mouse.click(MOUSE_MIDDLE);\n")
			else:
				out_file.write("	Mouse.click();\n")
		elif words[1] == "PRESS":
			if len(words) > 2:
				if words[2] == "LEFT":
					out_file.write("	Mouse.press(MOUSE_LEFT);\n")
				if words[2] == "RIGHT":
					out_file.write("	Mouse.press(MOUSE_RIGHT);\n")
				if words[2] == "MIDDLE":
					out_file.write("	Mouse.press(MOUSE_MIDDLE);\n")
			else:
				out_file.write("	Mouse.press();\n")
		elif words[1] == "RELEASE":
			if len(words) > 2:
				if words[2] == "LEFT":
					out_file.write("	Mouse.release(MOUSE_LEFT);\n")
				if words[2] == "RIGHT":
					out_file.write("	Mouse.release(MOUSE_RIGHT);\n")
				if words[2] == "MIDDLE":
					out_file.write("	Mouse.release(MOUSE_MIDDLE);\n")
			else:
				out_file.write("	Mouse.release();\n")

		else:
			out_file.write("	Mouse.move(" + words[1] + ", " + words[2] + ");\n")

	elif keys.has_key(words[0]):
		while len(line) > 0:
			space = line.find(" ")
			if space < 0: space = len(line)
			out_file.write("	Keyboard.press(" + keys[line[:space]] + ");\n")
			line = line[space+1:]
		out_file.write("	Keyboard.releaseAll();\n")

	else:
		out_file.write(line + "\n")

	if default_delay > 0 and words[0] != "REM":
		out_file.write("	delay(" + str(default_delay) + ");\n")

out_file.write("}\n")
if not in_loop:
	out_file.write("\nvoid loop() {}\n")

in_file.close()
out_file.close()
