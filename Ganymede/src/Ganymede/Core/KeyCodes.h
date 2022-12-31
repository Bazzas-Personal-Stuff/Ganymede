#pragma once

// KeyCodes from glfw3.h

/* The unknown key */
#define GNM_KEY_UNKNOWN            -1

/* Printable keys */
#define GNM_KEY_SPACE              32
#define GNM_KEY_APOSTROPHE         39  /* ' */
#define GNM_KEY_COMMA              44  /* , */
#define GNM_KEY_MINUS              45  /* - */
#define GNM_KEY_PERIOD             46  /* . */
#define GNM_KEY_SLASH              47  /* / */
#define GNM_KEY_0                  48
#define GNM_KEY_1                  49
#define GNM_KEY_2                  50
#define GNM_KEY_3                  51
#define GNM_KEY_4                  52
#define GNM_KEY_5                  53
#define GNM_KEY_6                  54
#define GNM_KEY_7                  55
#define GNM_KEY_8                  56
#define GNM_KEY_9                  57
#define GNM_KEY_SEMICOLON          59  /* ; */
#define GNM_KEY_EQUAL              61  /* = */
#define GNM_KEY_A                  65
#define GNM_KEY_B                  66
#define GNM_KEY_C                  67
#define GNM_KEY_D                  68
#define GNM_KEY_E                  69
#define GNM_KEY_F                  70
#define GNM_KEY_G                  71
#define GNM_KEY_H                  72
#define GNM_KEY_I                  73
#define GNM_KEY_J                  74
#define GNM_KEY_K                  75
#define GNM_KEY_L                  76
#define GNM_KEY_M                  77
#define GNM_KEY_N                  78
#define GNM_KEY_O                  79
#define GNM_KEY_P                  80
#define GNM_KEY_Q                  81
#define GNM_KEY_R                  82
#define GNM_KEY_S                  83
#define GNM_KEY_T                  84
#define GNM_KEY_U                  85
#define GNM_KEY_V                  86
#define GNM_KEY_W                  87
#define GNM_KEY_X                  88
#define GNM_KEY_Y                  89
#define GNM_KEY_Z                  90
#define GNM_KEY_LEFT_BRACKET       91  /* [ */
#define GNM_KEY_BACKSLASH          92  /* \ */
#define GNM_KEY_RIGHT_BRACKET      93  /* ] */
#define GNM_KEY_GRAVE_ACCENT       96  /* ` */
#define GNM_KEY_WORLD_1            161 /* non-US #1 */
#define GNM_KEY_WORLD_2            162 /* non-US #2 */

/* Function keys */
#define GNM_KEY_ESCAPE             256
#define GNM_KEY_ENTER              257
#define GNM_KEY_TAB                258
#define GNM_KEY_BACKSPACE          259
#define GNM_KEY_INSERT             260
#define GNM_KEY_DELETE             261
#define GNM_KEY_RIGHT              262
#define GNM_KEY_LEFT               263
#define GNM_KEY_DOWN               264
#define GNM_KEY_UP                 265
#define GNM_KEY_PAGE_UP            266
#define GNM_KEY_PAGE_DOWN          267
#define GNM_KEY_HOME               268
#define GNM_KEY_END                269
#define GNM_KEY_CAPS_LOCK          280
#define GNM_KEY_SCROLL_LOCK        281
#define GNM_KEY_NUM_LOCK           282
#define GNM_KEY_PRINT_SCREEN       283
#define GNM_KEY_PAUSE              284
#define GNM_KEY_F1                 290
#define GNM_KEY_F2                 291
#define GNM_KEY_F3                 292
#define GNM_KEY_F4                 293
#define GNM_KEY_F5                 294
#define GNM_KEY_F6                 295
#define GNM_KEY_F7                 296
#define GNM_KEY_F8                 297
#define GNM_KEY_F9                 298
#define GNM_KEY_F10                299
#define GNM_KEY_F11                300
#define GNM_KEY_F12                301
#define GNM_KEY_F13                302
#define GNM_KEY_F14                303
#define GNM_KEY_F15                304
#define GNM_KEY_F16                305
#define GNM_KEY_F17                306
#define GNM_KEY_F18                307
#define GNM_KEY_F19                308
#define GNM_KEY_F20                309
#define GNM_KEY_F21                310
#define GNM_KEY_F22                311
#define GNM_KEY_F23                312
#define GNM_KEY_F24                313
#define GNM_KEY_F25                314
#define GNM_KEY_KP_0               320
#define GNM_KEY_KP_1               321
#define GNM_KEY_KP_2               322
#define GNM_KEY_KP_3               323
#define GNM_KEY_KP_4               324
#define GNM_KEY_KP_5               325
#define GNM_KEY_KP_6               326
#define GNM_KEY_KP_7               327
#define GNM_KEY_KP_8               328
#define GNM_KEY_KP_9               329
#define GNM_KEY_KP_DECIMAL         330
#define GNM_KEY_KP_DIVIDE          331
#define GNM_KEY_KP_MULTIPLY        332
#define GNM_KEY_KP_SUBTRACT        333
#define GNM_KEY_KP_ADD             334
#define GNM_KEY_KP_ENTER           335
#define GNM_KEY_KP_EQUAL           336
#define GNM_KEY_LEFT_SHIFT         340
#define GNM_KEY_LEFT_CONTROL       341
#define GNM_KEY_LEFT_ALT           342
#define GNM_KEY_LEFT_SUPER         343
#define GNM_KEY_RIGHT_SHIFT        344
#define GNM_KEY_RIGHT_CONTROL      345
#define GNM_KEY_RIGHT_ALT          346
#define GNM_KEY_RIGHT_SUPER        347
#define GNM_KEY_MENU               348

// Key modifier flags
#define GNM_MOD_SHIFT           0x0001
#define GNM_MOD_CONTROL         0x0002
#define GNM_MOD_ALT             0x0004
#define GNM_MOD_SUPER           0x0008
#define GNM_MOD_CAPS_LOCK       0x0010
#define GNM_MOD_NUM_LOCK        0x0020
