#include "Keyboard.h"

void setup() {
Keyboard.begin();
delay(400);
Keyboard.press(KEY_LEFT_GUI);
Keyboard.press('d');
Keyboard.releaseAll();

Keyboard.press(KEY_LEFT_GUI);
delay(50);
Keyboard.release(KEY_LEFT_GUI);

Keyboard.print("https://i.imgflip.com/1dv8ac.jpg");

Keyboard.press(KEY_RETURN);
delay(50);
Keyboard.release(KEY_RETURN);

delay(100);

// Opens up window and goes to a image I created xD

Keyboard.press(KEY_LEFT_CTRL);
Keyboard.press('s');
Keyboard.releaseAll();

Keyboard.print("%userprofile%\Desktop\QUACKED");

Keyboard.press(KEY_RETURN);
delay(50);
Keyboard.release(KEY_RETURN);

// saving the picture to the user Desktop, pic name QUACKED...

delay(100);

Keyboard.press(KEY_LEFT_GUI);
Keyboard.press('d');
Keyboard.releaseAll();

// shows desktop

Keyboard.press(KEY_LEFT_GUI);
Keyboard.press('r');
Keyboard.releaseAll();

Keyboard.print("%userprofile%\Desktop\QUACKED.png");

Keyboard.press(KEY_RETURN);
delay(50);
Keyboard.release(KEY_RETURN);

// opens the png file

Keyboard.press(229);
delay(50);
Keyboard.release(229);

Keyboard.press(KEY_RETURN);
delay(50);
Keyboard.release(KEY_RETURN);

Keyboard.press(KEY_LEFT_ALT);
Keyboard.press(KEY_F4);
Keyboard.releaseAll();

// sets the background, and closes.

Keyboard.press(KEY_LEFT_GUI);
Keyboard.press('d');
Keyboard.releaseAll();

Keyboard.press(229);
delay(50);
Keyboard.release(229);

Keyboard.print("v");

Keyboard.print("d");

// I know its basic but tell what you think im only 14 and this is my first "program" thanks Darren

Keyboard.end();
}

void loop() {}
