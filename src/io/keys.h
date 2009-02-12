#ifndef KEYS_H
#define KEYS_H

/* [Input_Keyboard1] */
prefs_bool  inputKeyboard1_enabled;
prefs_short inputKeyboard1_buttonGreen;
prefs_short inputKeyboard1_buttonRed;
prefs_short inputKeyboard1_buttonYellow;
prefs_short inputKeyboard1_buttonBlue;
prefs_short inputKeyboard1_buttonOrange;
prefs_short inputKeyboard1_buttonPickUp;
prefs_short inputKeyboard1_buttonPickDown;
prefs_short inputKeyboard1_buttonDirectionLeft;
prefs_short inputKeyboard1_buttonDirectionRight;
prefs_short inputKeyboard1_buttonDirectionUp; /* Can be the same as pick up key */
prefs_short inputKeyboard1_buttonDirectionDown;
prefs_short inputKeyboard1_whammyDown;
prefs_short inputKeyboard1_whammyUp;
prefs_short inputKeyboard1_buttonStart; /* Usually ENTER key */
prefs_short inputKeyboard1_buttonSelect;
prefs_short inputKeyboard1_buttonScreenshot;

/* [Input_Keyboard2] */
prefs_bool  inputKeyboard2_enabled;
prefs_short inputKeyboard2_buttonGreen;
prefs_short inputKeyboard2_buttonRed;
prefs_short inputKeyboard2_buttonYellow;
prefs_short inputKeyboard2_buttonBlue;
prefs_short inputKeyboard2_buttonOrange;
prefs_short inputKeyboard2_buttonPickUp;
prefs_short inputKeyboard2_buttonPickDown;
prefs_short inputKeyboard2_buttonDirectionLeft;
prefs_short inputKeyboard2_buttonDirectionRight;
prefs_short inputKeyboard2_buttonDirectionUp; /* Can be the same as pick up key */
prefs_short inputKeyboard2_buttonDirectionDown;
prefs_short inputKeyboard2_whammyDown;
prefs_short inputKeyboard2_whammyUp;
prefs_short inputKeyboard2_buttonStart; /* Usually ENTER key */
prefs_short inputKeyboard2_buttonSelect;
prefs_short inputKeyboard2_buttonScreenshot;

/* [Input_Keyboard3] */
prefs_bool  inputKeyboard3_enabled;
prefs_short inputKeyboard3_buttonGreen;
prefs_short inputKeyboard3_buttonRed;
prefs_short inputKeyboard3_buttonYellow;
prefs_short inputKeyboard3_buttonBlue;
prefs_short inputKeyboard3_buttonOrange;
prefs_short inputKeyboard3_buttonPickUp;
prefs_short inputKeyboard3_buttonPickDown;
prefs_short inputKeyboard3_buttonDirectionLeft;
prefs_short inputKeyboard3_buttonDirectionRight;
prefs_short inputKeyboard3_buttonDirectionUp; /* Can be the same as pick up key */
prefs_short inputKeyboard3_buttonDirectionDown;
prefs_short inputKeyboard3_whammyDown;
prefs_short inputKeyboard3_whammyUp;
prefs_short inputKeyboard3_buttonStart; /* Usually ENTER key */
prefs_short inputKeyboard3_buttonSelect;
prefs_short inputKeyboard3_buttonScreenshot;

int keys_mapKeystringToSDL(char keystring[]);

#endif
