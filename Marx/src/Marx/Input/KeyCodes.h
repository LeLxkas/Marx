#pragma once

#define MX_KEY_CANCEL              0x03

#define MX_KEY_BACK                0x08
#define MX_KEY_TAB                 0x09
#define MX_KEY_CLEAR               0x0C
#define MX_KEY_RETURN              0x0D

#define MX_KEY_SHIFT               0x10
#define MX_KEY_CONTROL             0x11
#define MX_KEY_MENU                0x12
#define MX_KEY_PAUSE               0x13
#define MX_KEY_CAPITAL             0x14

#define MX_KEY_KANA                0x15
#define MX_KEY_HANGUL              0x15

#define MX_KEY_JUNJA               0x17
#define MX_KEY_FINAL               0x18
#define MX_KEY_HANJA               0x19
#define MX_KEY_KANJI               0x19

#define MX_KEY_ESCAPE              0x1B

#define MX_KEY_CONVERT             0x1C
#define MX_KEY_NONCONVERT          0x1D
#define MX_KEY_ACCEPT              0x1E
#define MX_KEY_MODECHANGE          0x1F

#define MX_KEY_SPACE               0x20
#define MX_KEY_PRIOR               0x21
#define MX_KEY_NEXT                0x22
#define MX_KEY_END                 0x23
#define MX_KEY_HOME                0x24
#define MX_KEY_LEFT                0x25
#define MX_KEY_UP                  0x26
#define MX_KEY_RIGHT               0x27
#define MX_KEY_DOWN                0x28
#define MX_KEY_SELECT              0x29
#define MX_KEY_PRINT               0x2A
#define MX_KEY_EXECUTE             0x2B
#define MX_KEY_SNAPSHOT            0x2C
#define MX_KEY_INSERT              0x2D
#define MX_KEY_DELETE              0x2E
#define MX_KEY_HELP                0x2F

#define MX_KEY_0                   0x30
#define MX_KEY_1                   0x31
#define MX_KEY_2                   0x32
#define MX_KEY_3                   0x33
#define MX_KEY_4                   0x34
#define MX_KEY_5                   0x35
#define MX_KEY_6                   0x36
#define MX_KEY_7                   0x37
#define MX_KEY_8                   0x38
#define MX_KEY_9                   0x39

#define MX_KEY_A                   0x41
#define MX_KEY_B                   0x42
#define MX_KEY_C                   0x43
#define MX_KEY_D                   0x44
#define MX_KEY_E                   0x45
#define MX_KEY_F                   0x46
#define MX_KEY_G                   0x47
#define MX_KEY_H                   0x48
#define MX_KEY_I                   0x49
#define MX_KEY_J                   0x4A
#define MX_KEY_K                   0x4B
#define MX_KEY_L                   0x4C
#define MX_KEY_M                   0x4D
#define MX_KEY_N                   0x4E
#define MX_KEY_O                   0x4F
#define MX_KEY_P                   0x50
#define MX_KEY_Q                   0x51
#define MX_KEY_R                   0x52
#define MX_KEY_S                   0x53
#define MX_KEY_T                   0x54
#define MX_KEY_U                   0x55
#define MX_KEY_V                   0x56
#define MX_KEY_W                   0x57
#define MX_KEY_X                   0x58
#define MX_KEY_Y                   0x59
#define MX_KEY_Z                   0x5A

#define MX_KEY_LWIN                0x5B
#define MX_KEY_RWIN                0x5C
#define MX_KEY_APPS                0x5D

#define MX_KEY_SLEEP               0x5F

#define MX_KEY_NUMPAD0             0x60
#define MX_KEY_NUMPAD1             0x61
#define MX_KEY_NUMPAD2             0x62
#define MX_KEY_NUMPAD3             0x63
#define MX_KEY_NUMPAD4             0x64
#define MX_KEY_NUMPAD5             0x65
#define MX_KEY_NUMPAD6             0x66
#define MX_KEY_NUMPAD7             0x67
#define MX_KEY_NUMPAD8             0x68
#define MX_KEY_NUMPAD9             0x69
#define MX_KEY_MULTIPLY            0x6A
#define MX_KEY_ADD                 0x6B
#define MX_KEY_SEPARATOR           0x6C
#define MX_KEY_SUBTRACT            0x6D
#define MX_KEY_DECIMAL             0x6E
#define MX_KEY_DIVIDE              0x6F
#define MX_KEY_F1                  0x70
#define MX_KEY_F2                  0x71
#define MX_KEY_F3                  0x72
#define MX_KEY_F4                  0x73
#define MX_KEY_F5                  0x74
#define MX_KEY_F6                  0x75
#define MX_KEY_F7                  0x76
#define MX_KEY_F8                  0x77
#define MX_KEY_F9                  0x78
#define MX_KEY_F10                 0x79
#define MX_KEY_F11                 0x7A
#define MX_KEY_F12                 0x7B
#define MX_KEY_F13                 0x7C
#define MX_KEY_F14                 0x7D
#define MX_KEY_F15                 0x7E
#define MX_KEY_F16                 0x7F
#define MX_KEY_F17                 0x80
#define MX_KEY_F18                 0x81
#define MX_KEY_F19                 0x82
#define MX_KEY_F20                 0x83
#define MX_KEY_F21                 0x84
#define MX_KEY_F22                 0x85
#define MX_KEY_F23                 0x86
#define MX_KEY_F24                 0x87

#define MX_KEY_NAVIGATION_VIEW     0x88 // reserved
#define MX_KEY_NAVIGATION_MENU     0x89 // reserved
#define MX_KEY_NAVIGATION_UP       0x8A // reserved
#define MX_KEY_NAVIGATION_DOWN     0x8B // reserved
#define MX_KEY_NAVIGATION_LEFT     0x8C // reserved
#define MX_KEY_NAVIGATION_RIGHT    0x8D // reserved
#define MX_KEY_NAVIGATION_ACCEPT   0x8E // reserved
#define MX_KEY_NAVIGATION_CANCEL   0x8F // reserved

#define MX_KEY_NUMLOCK             0x90
#define MX_KEY_SCROLL              0x91

#define MX_KEY_OEM_NEC_EQUAL       0x92   // '=' key on numpad

#define MX_KEY_OEM_FJ_JISHO        0x92   // 'Dictionary' key
#define MX_KEY_OEM_FJ_MASSHOU      0x93   // 'Unregister word' key
#define MX_KEY_OEM_FJ_TOUROKU      0x94   // 'Register word' key
#define MX_KEY_OEM_FJ_LOYA         0x95   // 'Left OYAYUBI' key
#define MX_KEY_OEM_FJ_ROYA         0x96   // 'Right OYAYUBI' key


#define MX_KEY_LSHIFT              0xA0
#define MX_KEY_RSHIFT              0xA1
#define MX_KEY_LCONTROL            0xA2
#define MX_KEY_RCONTROL            0xA3
#define MX_KEY_LMENU               0xA4
#define MX_KEY_RMENU               0xA5

#define MX_KEY_BROWSER_BACK        0xA6
#define MX_KEY_BROWSER_FORWARD     0xA7
#define MX_KEY_BROWSER_REFRESH     0xA8
#define MX_KEY_BROWSER_STOP        0xA9
#define MX_KEY_BROWSER_SEARCH      0xAA
#define MX_KEY_BROWSER_FAVORITES   0xAB
#define MX_KEY_BROWSER_HOME        0xAC

#define MX_KEY_VOLUME_MUTE         0xAD
#define MX_KEY_VOLUME_DOWN         0xAE
#define MX_KEY_VOLUME_UP           0xAF
#define MX_KEY_MEDIA_NEXT_TRACK    0xB0
#define MX_KEY_MEDIA_PREV_TRACK    0xB1
#define MX_KEY_MEDIA_STOP          0xB2
#define MX_KEY_MEDIA_PLAY_PAUSE    0xB3
#define MX_KEY_LAUNCH_MAIL         0xB4
#define MX_KEY_LAUNCH_MEDIA_SELECT 0xB5
#define MX_KEY_LAUNCH_APP1         0xB6
#define MX_KEY_LAUNCH_APP2         0xB7

#define MX_KEY_OEM_1               0xBA   // ';:' for US
#define MX_KEY_OEM_PLUS            0xBB   // '+' any country
#define MX_KEY_OEM_COMMA           0xBC   // ',' any country
#define MX_KEY_OEM_MINUS           0xBD   // '-' any country
#define MX_KEY_OEM_PERIOD          0xBE   // '.' any country
#define MX_KEY_OEM_2               0xBF   // '/?' for US
#define MX_KEY_OEM_3               0xC0   // '`~' for US

#define MX_KEY_OEM_4               0xDB  //  '[{' for US
#define MX_KEY_OEM_5               0xDC  //  '\|' for US
#define MX_KEY_OEM_6               0xDD  //  ']}' for US
#define MX_KEY_OEM_7               0xDE  //  ''"' for US
#define MX_KEY_OEM_8               0xDF

#define MX_KEY_OEM_AX              0xE1  //  'AX' key on Japanese AX kbd
#define MX_KEY_OEM_102             0xE2  //  "<>" or "\|" on RT 102-key kbd.
#define MX_KEY_ICO_HELP            0xE3  //  Help key on ICO
#define MX_KEY_ICO_00              0xE4  //  00 key on ICO

#define MX_KEY_PROCESSKEY          0xE5

#define MX_KEY_ICO_CLEAR           0xE6

#define MX_KEY_PACKET              0xE7

#define MX_KEY_OEM_RESET           0xE9
#define MX_KEY_OEM_JUMP            0xEA
#define MX_KEY_OEM_PA1             0xEB
#define MX_KEY_OEM_PA2             0xEC
#define MX_KEY_OEM_PA3             0xED
#define MX_KEY_OEM_WSCTRL          0xEE
#define MX_KEY_OEM_CUSEL           0xEF
#define MX_KEY_OEM_ATTN            0xF0
#define MX_KEY_OEM_FINISH          0xF1
#define MX_KEY_OEM_COPY            0xF2
#define MX_KEY_OEM_AUTO            0xF3
#define MX_KEY_OEM_ENLW            0xF4
#define MX_KEY_OEM_BACKTAB         0xF5

#define MX_KEY_ATTN                0xF6
#define MX_KEY_CRSEL               0xF7
#define MX_KEY_EXSEL               0xF8
#define MX_KEY_EREOF               0xF9
#define MX_KEY_PLAY                0xFA
#define MX_KEY_ZOOM                0xFB
#define MX_KEY_NONAME              0xFC
#define MX_KEY_PA1                 0xFD
#define MX_KEY_OEM_CLEAR           0xFE