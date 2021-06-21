#include <iostream>
#include <string>
#include <cstring>
#include <3ds.h>

#include "keyboard.hpp"




const char *Keyboard_GetText(const char *hint_text) {

	static SwkbdState swkbd;
	static SwkbdStatusData swkbdStatus;
	static bool reload = false;
	static char input_string[256];

	swkbdInit(&swkbd, SWKBD_TYPE_QWERTY, 2, 256);

	if (strlen(hint_text) != 0)
		swkbdSetHintText(&swkbd, hint_text);

	swkbdSetButton(&swkbd, SWKBD_BUTTON_LEFT, "Cancel", false);
	swkbdSetButton(&swkbd, SWKBD_BUTTON_RIGHT, "Confirm", true);

	swkbdSetFeatures(&swkbd, SWKBD_ALLOW_HOME);
	swkbdSetFeatures(&swkbd, SWKBD_ALLOW_RESET);
	swkbdSetFeatures(&swkbd, SWKBD_ALLOW_POWER);
	//swkbdSetFeatures(&swkbd, SWKBD_PREDICTIVE_INPUT);

	swkbdSetValidation(&swkbd, SWKBD_NOTEMPTY_NOTBLANK, 0, 0);
	swkbdSetStatusData(&swkbd, &swkbdStatus, reload, true);

	reload = true;

	swkbdInputText(&swkbd, input_string, sizeof(input_string));

	return input_string;
}

const char* Keyboard_GetNumber() {
    static SwkbdState swkbd;
	static char input_string[256];

    swkbdInit(&swkbd, SWKBD_TYPE_NUMPAD, 1, -1);
	swkbdSetValidation(&swkbd, SWKBD_ANYTHING, 0, 0);
	swkbdSetFeatures(&swkbd, SWKBD_FIXED_WIDTH);
	swkbdSetNumpadKeys(&swkbd, 0, 0);
	swkbdInputText(&swkbd, input_string, sizeof(input_string));

    return input_string;
}