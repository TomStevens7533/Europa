#pragma once

#define EU_RELEASE                0

#define EU_PRESS                  1

#define EU_REPEAT                 2

#define EU_HAT_CENTERED           0
#define EU_HAT_UP                 1
#define EU_HAT_RIGHT              2
#define EU_HAT_DOWN               4
#define EU_HAT_LEFT               8
#define EU_HAT_RIGHT_UP           (EU_HAT_RIGHT | EU_HAT_UP)
#define EU_HAT_RIGHT_DOWN         (EU_HAT_RIGHT | EU_HAT_DOWN)
#define EU_HAT_LEFT_UP            (EU_HAT_LEFT  | EU_HAT_UP)
#define EU_HAT_LEFT_DOWN          (EU_HAT_LEFT  | EU_HAT_DOWN)

	/* The unknown key */
#define EU_KEY_UNKNOWN            -1

/* Printable keys */
#define EU_KEY_SPACE              32
#define EU_KEY_APOSTROPHE         39  /* ' */
#define EU_KEY_COMMA              44  /* , */
#define EU_KEY_MINUS              45  /* - */
#define EU_KEY_PERIOD             46  /* . */
#define EU_KEY_SLASH              47  /* / */
#define EU_KEY_0                  48
#define EU_KEY_1                  49
#define EU_KEY_2                  50
#define EU_KEY_3                  51
#define EU_KEY_4                  52
#define EU_KEY_5                  53
#define EU_KEY_6                  54
#define EU_KEY_7                  55
#define EU_KEY_8                  56
#define EU_KEY_9                  57
#define EU_KEY_SEMICOLON          59  /* ; */
#define EU_KEY_EQUAL              61  /* = */
#define EU_KEY_A                  65
#define EU_KEY_B                  66
#define EU_KEY_C                  67
#define EU_KEY_D                  68
#define EU_KEY_E                  69
#define EU_KEY_F                  70
#define EU_KEY_G                  71
#define EU_KEY_H                  72
#define EU_KEY_I                  73
#define EU_KEY_J                  74
#define EU_KEY_K                  75
#define EU_KEY_L                  76
#define EU_KEY_M                  77
#define EU_KEY_N                  78
#define EU_KEY_O                  79
#define EU_KEY_P                  80
#define EU_KEY_Q                  81
#define EU_KEY_R                  82
#define EU_KEY_S                  83
#define EU_KEY_T                  84
#define EU_KEY_U                  85
#define EU_KEY_V                  86
#define EU_KEY_W                  87
#define EU_KEY_X                  88
#define EU_KEY_Y                  89
#define EU_KEY_Z                  90
#define EU_KEY_LEFT_BRACKET       91  /* [ */
#define EU_KEY_BACKSLASH          92  /* \ */
#define EU_KEY_RIGHT_BRACKET      93  /* ] */
#define EU_KEY_GRAVE_ACCENT       96  /* ` */
#define EU_KEY_WORLD_1            161 /* non-US #1 */
#define EU_KEY_WORLD_2            162 /* non-US #2 */

/* Function keys */
#define EU_KEY_ESCAPE             256
#define EU_KEY_ENTER              257
#define EU_KEY_TAB                258
#define EU_KEY_BACKSPACE          259
#define EU_KEY_INSERT             260
#define EU_KEY_DELETE             261
#define EU_KEY_RIGHT              262
#define EU_KEY_LEFT               263
#define EU_KEY_DOWN               264
#define EU_KEY_UP                 265
#define EU_KEY_PAGE_UP            266
#define EU_KEY_PAGE_DOWN          267
#define EU_KEY_HOME               268
#define EU_KEY_END                269
#define EU_KEY_CAPS_LOCK          280
#define EU_KEY_SCROLL_LOCK        281
#define EU_KEY_NUM_LOCK           282
#define EU_KEY_PRINT_SCREEN       283
#define EU_KEY_PAUSE              284
#define EU_KEY_F1                 290
#define EU_KEY_F2                 291
#define EU_KEY_F3                 292
#define EU_KEY_F4                 293
#define EU_KEY_F5                 294
#define EU_KEY_F6                 295
#define EU_KEY_F7                 296
#define EU_KEY_F8                 297
#define EU_KEY_F9                 298
#define EU_KEY_F10                299
#define EU_KEY_F11                300
#define EU_KEY_F12                301
#define EU_KEY_F13                302
#define EU_KEY_F14                303
#define EU_KEY_F15                304
#define EU_KEY_F16                305
#define EU_KEY_F17                306
#define EU_KEY_F18                307
#define EU_KEY_F19                308
#define EU_KEY_F20                309
#define EU_KEY_F21                310
#define EU_KEY_F22                311
#define EU_KEY_F23                312
#define EU_KEY_F24                313
#define EU_KEY_F25                314
#define EU_KEY_KP_0               320
#define EU_KEY_KP_1               321
#define EU_KEY_KP_2               322
#define EU_KEY_KP_3               323
#define EU_KEY_KP_4               324
#define EU_KEY_KP_5               325
#define EU_KEY_KP_6               326
#define EU_KEY_KP_7               327
#define EU_KEY_KP_8               328
#define EU_KEY_KP_9               329
#define EU_KEY_KP_DECIMAL         330
#define EU_KEY_KP_DIVIDE          331
#define EU_KEY_KP_MULTIPLY        332
#define EU_KEY_KP_SUBTRACT        333
#define EU_KEY_KP_ADD             334
#define EU_KEY_KP_ENTER           335
#define EU_KEY_KP_EQUAL           336
#define EU_KEY_LEFT_SHIFT         340
#define EU_KEY_LEFT_CONTROL       341
#define EU_KEY_LEFT_ALT           342
#define EU_KEY_LEFT_SUPER         343
#define EU_KEY_RIGHT_SHIFT        344
#define EU_KEY_RIGHT_CONTROL      345
#define EU_KEY_RIGHT_ALT          346
#define EU_KEY_RIGHT_SUPER        347
#define EU_KEY_MENU               348

#define EU_KEY_LAST               EU_KEY_MENU

#define EU_MOD_SHIFT           0x0001

#define EU_MOD_CONTROL         0x0002

#define EU_MOD_ALT             0x0004


#define EU_MOD_SUPER           0x0008

#define EU_MOD_CAPS_LOCK       0x0010

#define EU_MOD_NUM_LOCK        0x0020



#define EU_MOUSE_BUTTON_1         0
#define EU_MOUSE_BUTTON_2         1
#define EU_MOUSE_BUTTON_3         2
#define EU_MOUSE_BUTTON_4         3
#define EU_MOUSE_BUTTON_5         4
#define EU_MOUSE_BUTTON_6         5
#define EU_MOUSE_BUTTON_7         6
#define EU_MOUSE_BUTTON_8         7
#define EU_MOUSE_BUTTON_LAST      EU_MOUSE_BUTTON_8
#define EU_MOUSE_BUTTON_LEFT      EU_MOUSE_BUTTON_1
#define EU_MOUSE_BUTTON_RIGHT     EU_MOUSE_BUTTON_2
#define EU_MOUSE_BUTTON_MIDDLE    EU_MOUSE_BUTTON_3
//joystick
#define EU_JOYSTICK_1             0
#define EU_JOYSTICK_2             1
#define EU_JOYSTICK_3             2
#define EU_JOYSTICK_4             3
#define EU_JOYSTICK_5             4
#define EU_JOYSTICK_6             5
#define EU_JOYSTICK_7             6
#define EU_JOYSTICK_8             7
#define EU_JOYSTICK_9             8
#define EU_JOYSTICK_10            9
#define EU_JOYSTICK_11            10
#define EU_JOYSTICK_12            11
#define EU_JOYSTICK_13            12
#define EU_JOYSTICK_14            13
#define EU_JOYSTICK_15            14
#define EU_JOYSTICK_16            15
#define EU_JOYSTICK_LAST          EU_JOYSTICK_16
//gamepad
#define EU_GAMEPAD_BUTTON_A               0
#define EU_GAMEPAD_BUTTON_B               1
#define EU_GAMEPAD_BUTTON_X               2
#define EU_GAMEPAD_BUTTON_Y               3
#define EU_GAMEPAD_BUTTON_LEFT_BUMPER     4
#define EU_GAMEPAD_BUTTON_RIGHT_BUMPER    5
#define EU_GAMEPAD_BUTTON_BACK            6
#define EU_GAMEPAD_BUTTON_START           7
#define EU_GAMEPAD_BUTTON_GUIDE           8
#define EU_GAMEPAD_BUTTON_LEFT_THUMB      9
#define EU_GAMEPAD_BUTTON_RIGHT_THUMB     10
#define EU_GAMEPAD_BUTTON_DPAD_UP         11
#define EU_GAMEPAD_BUTTON_DPAD_RIGHT      12
#define EU_GAMEPAD_BUTTON_DPAD_DOWN       13
#define EU_GAMEPAD_BUTTON_DPAD_LEFT       14
#define EU_GAMEPAD_BUTTON_LAST            EU_GAMEPAD_BUTTON_DPAD_LEFT

#define EU_GAMEPAD_BUTTON_CROSS       EU_GAMEPAD_BUTTON_A
#define EU_GAMEPAD_BUTTON_CIRCLE      EU_GAMEPAD_BUTTON_B
#define EU_GAMEPAD_BUTTON_SQUARE      EU_GAMEPAD_BUTTON_X
#define EU_GAMEPAD_BUTTON_TRIANGLE    EU_GAMEPAD_BUTTON_Y

#define EU_GAMEPAD_AXIS_LEFT_X        0
#define EU_GAMEPAD_AXIS_LEFT_Y        1
#define EU_GAMEPAD_AXIS_RIGHT_X       2
#define EU_GAMEPAD_AXIS_RIGHT_Y       3
#define EU_GAMEPAD_AXIS_LEFT_TRIGGER  4
#define EU_GAMEPAD_AXIS_RIGHT_TRIGGER 5
#define EU_GAMEPAD_AXIS_LAST          EU_GAMEPAD_AXIS_RIGHT_TRIGGER