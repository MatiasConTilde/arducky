#include "Keyboard.h"

void typeKey(int key) {
	Keyboard.press(key);
	delay(50);
	Keyboard.release(key);
}

void setup() {
	Keyboard.begin();
	Mouse.begin();
	delay(500);

	// This is an example duckyscript to show how the interpreter works

	// Write text with STRING
	Keyboard.print("This text will be written");
	// Characters will be escaped
	Keyboard.print("asdf\" \\ \"asdasd\"");

	// Wait with DELAY
	delay(1000);

	// Put all the following code in loop(){}
}

void loop() {

	// Press key sequences
	Keyboard.press(KEY_LEFT_CTRL);
	Keyboard.press('s');
	Keyboard.releaseAll();

	Keyboard.press(KEY_LEFT_ALT);
	Keyboard.press(KEY_F4);
	Keyboard.releaseAll();

	Keyboard.press(KEY_LEFT_GUI);
	Keyboard.press('r');
	Keyboard.releaseAll();

	Keyboard.press(KEY_LEFT_GUI);
	Keyboard.press(' ');
	Keyboard.releaseAll();

	// Set a default delay to be executed after each command
	// Differently to real Duckyscript, this can be changed throuought the program
	delay(100);
	Keyboard.print("hello");
	delay(100);
	Keyboard.print("eins zwei polizei");
	delay(100);

	// Move the mouse and click
	// To move, the two values have to be separated by space
	Mouse.move(100, 100);
	Mouse.move(random(0,100), random(0,100));
	Mouse.click();
	Mouse.click(MOUSE_LEFT);
	Mouse.click(MOUSE_RIGHT);
	Mouse.click(MOUSE_MIDDLE);
	Mouse.press();
	Mouse.press(MOUSE_LEFT);
	Mouse.press(MOUSE_RIGHT);
	Mouse.press(MOUSE_MIDDLE);
	Mouse.release();
	Mouse.release(MOUSE_LEFT);
	Mouse.release(MOUSE_RIGHT);
	Mouse.release(MOUSE_MIDDLE);

	// Write Arduino code directly
	for (int i = 0; i < 10; i ++) {
		Keyboard.print("lololo");
		typeKey(KEY_RETURN);
	}
}
