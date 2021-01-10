PUBLIC _ula_display
defc _ula_display = 0x4000

PUBLIC _ula_attributes
defc _ula_attributes = 0x5800

PUBLIC _sysvars
defc _sysvars = 0x5b00

PUBLIC _tiles
defc _tiles = 0x5c00

PUBLIC _tilemap
defc _tilemap = 0x6000

PUBLIC _fgColor
defc _fgColor = 0x6A00

PUBLIC _bgColor
defc _bgColor = 0x6A01

PUBLIC _plotit_core_state
defc _plotit_core_state = 0x6A02

PUBLIC _toolRegisters;
defc _toolRegisters = 0x6A03    ; 32bytes

PUBLIC _activeTool;
defc _activeTool = 0x6A24       ; uInt 8

PUBLIC _mouseBtns;
defc _mouseBtns = 0x6A25        ; uInt 8

PUBLIC _mouseX;
defc _mouseX = 0x6A26           ; uInt16

PUBLIC _mouseY;
defc _mouseY = 0x6A28           ; uInt16

PUBLIC _keyboard;
defc _keyboard = 0x6A2A         ; unsigned char

PUBLIC _canvasX;
defc _canvasX = 0x6A2B          ; uInt8

PUBLIC _canvasY;
defc _canvasY = 0x6A2C          ; uInt8

PUBLIC _plotColour;
defc _plotColour = 0x6A2D       ; uInt8

PUBLIC _plotTarget;
defc _plotTarget = 0x6A2E       ; uInt8

PUBLIC _undoMaxLevels;
defc _undoMaxLevels = 0x6A2F         ; uInt 8

PUBLIC _visible_screen_MMU;
defc _visible_screen_MMU = 0x6A30

PUBLIC _backing_store_MMU;
defc _backing_store_MMU = 0x6A36

PUBLIC _scratch_screen_MMU;
defc _scratch_screen_MMU = 0x6A40

PUBLIC _undo_screen_MMU;
defc _undo_screen_MMU = 0x6A46

PUBLIC _toolMemory;
defc _toolMemory = 0x6A50

PUBLIC _mouseCX;
defc _mouseCX = 0x6A70         ; uInt 8

PUBLIC _mouseCY;
defc _mouseCY = 0x6A71         ; uInt 8

PUBLIC _pluginActiveID;
defc _pluginActiveID = 0x6A72         ; uInt 8

PUBLIC _pluginEntryPoint;
defc _pluginEntryPoint = 0x6A73         ; uInt 8

PUBLIC _scratchUser;
defc _scratchUser = 0x6A74         ; uInt 8


; 0x6A75 next...

PUBLIC _paletteMemory;
defc _paletteMemory = 0x6B00

PUBLIC _buf_256;
defc _buf_256 = 0x6D00

; 0x6E00 next...
