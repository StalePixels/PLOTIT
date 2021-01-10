//
// Created by D Rimron-Soutter on 30/12/2020.
//


/*
 * NOTE 0
 *      The public memory map is yours to do with as you see fit,
 *      but not without consequences.  It is best to consider all of
 *      it essential for the correct operation of PLOTIT, _outside_
 *      of your plugin, and thus - anything you change, you should put
 *      back when done.
 *
 *      You can page the public memory space in and out as you see fit,
 *      and plugins are executed with interrupts disabled for this reason
 *      although PLOTIT expects BANK5 (the public memory) back in the
 *      default location when you return control to the main app.
 *
 *      There are also certain areas of the public memory map that are
 *      used to pass either parameters to your plugin, or for hardware
 *      support, and those are listed below.
 *
 * NOTE 1
 *      The ULA screen is used exclusively by PLOTIT for tool previews.
 *      Default paper is non-bright blue, and using this will make the ULA
 *      appear transparent, allowing you to do similar FX for your plugin.
 *
 * NOTE 2
 *      PLOTIT doesn't use the system variables for itself, except when
 *      the file browser is opened - buy they are preserved intact so that
 *      your plugin has the same OS options available to it (outwith channels)
 *
 * NOTE 3
 *      The tile definitions will be placed at address 0x5c00.
 *      However the ROM source font only defines characters 32 - 127
 *      which is the printable part of the ascii set so we will
 *      only be using those tile definitions stored in addresses
 *      0x5d00 to 0x5fff --Allen
 *
 *      You can replace the tile "entities" from 0 to 31 with your own when creating
 *      custom UIs, but you should to replace the sysvars when done rendering.
 *
 * NOTE 4
 *      The Video memory is broadly split into (public) sections
 *      1) visible_screen_MMU - this is where you can draw, drawing to this is
 *          drawing to the user's canvas.
 *      2) backing_store_MMU - Backikng store used during creation of custom user
 *          interfaces - when configured plugins will be launched with a copy of
 *          the canvas already in this memory, making changes to visible_screen_MMU
 *          non distructive.  Upon exiting the UI of your plugin this memory is
 *          restored over visible_screen_MMU.  You should not draw to backing_store_MMU
 *          directly without understanding the consequences.
 *      3) scratch_screen_MMU - 48k of usable as an SD load cache, or area of creating
 *          custom effects, blit space, etc.  Also can be used as extra scratch data
 *          for your plugin, if required.   Cannot be relied up to be in the same state
 *          as left between plugin executions.  You can write to this as required, there
 *          is no need to back up data before changing it.
 *      The structures of memory in this area is as follows:
 *          Byte 00:    reserved
 *          Byte 01:    reserved
 *          Byte 02:    MMU Bank number, top 16k
 *          Byte 03:    MMU Bank number, middle 16k
 *          Byte 04:    MMU Bank number, bottom 16k
 *          Byte 05:    MMU Bank number, calling bank when using zxnext_layer2 api (deprecated - do not use)
 *
 * NOTE 5
 *      undo_screen_MMU is the state of the previous undo step - this permits you to perform related effects between
 *      an image, and the previous state, in a plugin if required.  Etiquette says "don't edit this" in case the user
 *      ever wants to actually "undo" to it, it's part of the live "undo stack" memory.
 *
 * NOTE 6
 *      The builtin tools use two kinds of shared memory
 *      1) Tool Registers - 8 total, 16bit unsigned integers to allow tools to pass data outside of their own bank
 *          to your plugin
 *      2) Tool Memory    - 16 total, 16bit unsigned integers used to allow tools to pass persistent memory (e.g.
 *          last used brush) settings outside their bank/change tool defaults at startup.  (currently only 9/16 of
 *          the memory locations are used)
 *
 * NOTE 7
 *      The mouse is stored in a number of "precompued" forms, since it's used in many places like this - it
 *      speeds up the app to cache the sums - here are the versions found here:
 *          mouseX, mouseY              uInt16          raw coorddinate data
 *          canvasX, canvasY            uInt8           data precalcuated to fit within 48K L2 bounds
 */

#include <stdint.h>
#include <stdbool.h>
#include "zxnext_layer2.h"

#ifndef PLOTIT_API_H
#define PLOTIT_API_H

#define PLOTIT_MMU_SCRATCH      0x02
#define PLOTIT_MMU_DEFAULT      0x06

#define PLOTIT_STAMP_PATTERN    30

#define ZXNEXTOS_MMU_VRAM1      0x09//09
#define ZXNEXTOS_MMU_VRAM2      0x0A//10
#define ZXNEXTOS_MMU_VRAM3      0x0B//11
#define PLOTIT_MMU_IMAGE_DATA1  0x0C//12
#define PLOTIT_MMU_IMAGE_DATA2  0x0D//13
#define PLOTIT_MMU_IMAGE_DATA3  0x0E//14

#define PLOTIT_MMU_PLUGIN_CODE  0x0F//15

// -- UNDO START
#define PLOTIT_MMU_UNDO_6_1     0x10//16
#define PLOTIT_MMU_UNDO_6_2     0x11//17
#define PLOTIT_MMU_UNDO_6_3     0x12//18

#define PLOTIT_MMU_UNDO_5_1     0x13//19
#define PLOTIT_MMU_UNDO_5_2     0x14//20
#define PLOTIT_MMU_UNDO_5_3     0x15//21

#define PLOTIT_MMU_UNDO_4_1     0x16//22
#define PLOTIT_MMU_UNDO_4_2     0x17//23
#define PLOTIT_MMU_UNDO_4_3     0x18//24

#define PLOTIT_MMU_UNDO_3_1     0x19//25
#define PLOTIT_MMU_UNDO_3_2     0x1A//26
#define PLOTIT_MMU_UNDO_3_3     0x1B//27

#define PLOTIT_MMU_UNDO_2_1     0x1C//28
#define PLOTIT_MMU_UNDO_2_2     0x1D//29
#define PLOTIT_MMU_UNDO_2_3     0x1E//30

#define PLOTIT_MMU_UNDO_1_1     0x1F//31
#define PLOTIT_MMU_UNDO_1_2     0x20//32
#define PLOTIT_MMU_UNDO_1_3     0x21//33
// -- UNDO END

#define PLOTIT_MMU_SCRATCH_1    0x22//34
#define PLOTIT_MMU_SCRATCH_2    0x23//35
#define PLOTIT_MMU_SCRATCH_3    0x24//36

#define PLOTIT_MMU_RESERVED_4   0x25//37
#define PLOTIT_MMU_RESERVED_3   0x26//38

#define PLOTIT_MMU_STAMP_BOOK   0x27//39
#define PLOTIT_MMU_UI_SPRITES   0x28//40

#define PLOTIT_MMU_RESERVED_2   0x29//41
#define PLOTIT_MMU_RESERVED_1   0x2A//42

#define PLOTIT_MMU_PLUGINS      0x2B//43
#define PLOTIT_MMU_CREDITS      0x2C//44
#define PLOTIT_MMU_TOOLS        0x2D//45
#define PLOTIT_MMU_ENGINE       0x2E//46
#define PLOTIT_MMU_UTILS        0x2F//47
#define PLOTIT_MMU_ROM          0xFF//FF

#define MOUSE_BTN_PRIMARY       0x01
#define MOUSE_BTN_SECONDARY     0x02

#define TOOL_PENCIL             0x00
#define TOOL_PEN                0x01
#define TOOL_LINE               0x02
#define TOOL_BOX                0x03
#define TOOL_CIRCLE             0x04
#define TOOL_FILL               0x05
#define TOOL_MAGNIFY            0x06
#define TOOL_EYEDROPPER         0x07
#define TOOL_STAMP              0x08
#define TOOL_NOTREADY           0x09

//#define DEFAULT_DEBOUNCE_MS  400
#define DEFAULT_DEBOUNCE_FRAMES  10

#define DEFAULT_UNDO_LEVELS     6

///////////////////////////////
// PUBLIC MEMORY MAP (NOTE 0)
///////////////////////////////
/*
 * 0x4000 ULA Display File
 * 0x5800 Attributes                    NOTE 1
 * 0x5b00 System Variables              NOTE 2
 * 0x5c00 System Variables              NOTE 3: re: _tiles[0-31]
 * 0x5d00 _tiles[32-127]
 * 0x6000 _tilemap[32][40]
 * 0x6A00 _fgColor
 * 0x6A01 _bgColor
 * 0x6A02 _plotit_core_state
 * 0x6A03 _toolRegisters[8]             NOTE 6: para 1
 * 0x6A24 _activeTool
 * 0x6A25 _mouseBtns
 * 0x6A26 _mouseX                       NOTE 7
 * 0x6A28 _mouseY                       NOTE 7
 * 0x6A2A _keyboard
 * 0x6A2B _canvasX                      NOTE 7
 * 0x6A2C _canvasY                      NOTE 7
 * 0x6A2D _plotColour
 * 0x6A2E _plotTarget
 * 0x6A2F _undoMaxLevels
 * 0x6A30 _visible_screen_MMU           NOTE 4: area 1
 * 0x6A36 _backing_store_MMU            NOTE 4: area 2
 * 0x6A40 _scratch_screen_MMU           NOTE 4: area 3
 * 0x6A46 _undo_screen_MMU              NOTE 5
 * 0x6A50 _toolMemory[16]               NOTE 6: para 2
 * 0x6A70 _mouseCX
 * 0x6A71 _mouseCY
 * 0x6A72 _pluginActiveID
 * 0x6A73 _pluginEntryPoint
 * 0x6A74 _scratchUser;
 *
 *
 */

// Mostly here as a conceptual hack
extern uint8_t __ula_display[32][192];
extern uint8_t __ula_attributes[32][24];

struct __tiles
{
    unsigned char bmp[8];                       // each tile image is 8 bytes (64px@1bpp)
};
extern struct __tiles tiles[128];               // 128 tile images in total

struct __tilemap
{
    unsigned char tile;     // 0-7 = 8 bit tile number

    // Flags match NEXTREG: 0x6C (108) R/W => Default Tilemap Attribute format
    //  bits 7-1 = Palette Offset
    //  bit 0    = ULA over tilemap
    unsigned char flags;    // tile attribute (palette offset, rotation, etc)
};
extern struct __tilemap tilemap[32][40];        // 32 rows, 40 columns in each...

// Painting colours
extern uint8_t fgColor, bgColor;

// App's internal flag state
#define PLOTIT_STATE_DIRTY              1
extern uint8_t plotit_core_state;

// 32bytes of space reserved for tools to operate on when running so they can pass settings to other memory areas
extern int16_t toolRegisters[8];

// And what the current tool is
extern uint8_t activeTool;

// User Input - Mouse
extern uint8_t mouseBtns;
extern int16_t mouseX;
extern int16_t mouseY;

// Last key scanned
extern unsigned char keyboard;

extern uint8_t canvasX;
extern uint8_t canvasY;
extern uint8_t plotColour;
extern uint8_t plotTarget;

// How many undo levels the app has enabled (to see if you can steal any)
extern uint8_t undoMaxLevels;

// Some memstructs for handling screen addresses
extern layer2_screen_t visible_screen_MMU;
extern layer2_screen_t backing_store_MMU;
extern layer2_screen_t scratch_screen_MMU;
extern layer2_screen_t undo_screen_MMU;

// Tools persist their selections (e.g., brush selection) - 16 slots, only 9 currently used.
extern int16_t toolMemory[16];

// Some tools pass X&Y coords between each other, plugins can use this for local coord maths/cache
extern uint8_t mouseCX;
extern uint8_t mouseCY;

// Your plugin could be loaded in any order, so when you're executed your order ID will be here (starts at 0)
extern uint8_t pluginActiveID;

// When your plugin is called, this will be an integer marking which entry point (aka menu item)
// in the PLP file triggered it  (starts at 0)
extern uint8_t pluginEntryPoint;

// If the ID in scratchUser matches your pluginActiveID - you can use the scratch memory without backing it up to SD first
// -- backing the scratch memory up to SD isn't forced, but if you don't, make sure you change the scratchUser ID on exit
// so other plugins can tell you've changed it.
// You should leave your own pluginActiveID in this memory location _if_ you have left data here after your plugin
// has finished running -- but be warned, this it's an honour system.  This is probably best used for
// "start up code" or loading extra assets/binaries into, you can save repeated startup time if the 'cache' is "yours".
// And not important/irreplacable state data.
extern uint8_t scratchUser;

// The currently active pallete as last uploaded into the L2 hardware - here for easy reference, do not edit
extern uint16_t paletteMemory[256];

// Simple 0.25K buffer, used for file ops, UI &  stamp management - you can use it for your plugin, if desired
extern uint8_t buf_256[256];



#endif //PLOTIT_API_H
