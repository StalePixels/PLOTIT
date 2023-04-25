# ChangeLog

PLOTIT is a full-featured image editor, developed across multiple years.

## Controls
PLOTIT is designed to be controlled by a mouse, it also has keyboard shortcuts
which may help speed up some workflows or certain kinds of detail work.

|   **Key**   | **Use**
|-------------|----
|           q | Move mousepointer up one pixel
|           a | Move mousepointer down one pixel
|           o | Move mousepointer left one pixel
|           p | Move mousepointer right one pixel
| CapsShift+Q | Move mousepointer up eight pixels
| CapsShift+A | Move mousepointer down eight pixel
| CapsShift+O | Move mousepointer left eight pixel
| CapsShift+P | Move mousepointer right eight pixel
|           n | Left Mouse Button (Primary Action)
|           m | Right Mouse Button (Secondary Action)

The keyboard controls are intended as a suppliment to the mouse, and never as
a total replacement for the mouse - therefore there's likely many features and
functions that you can only do with the mouse.

## v0.8.0 - That *was* a mistake
### New Features
 * Undo
 * Rewrote Pens and Pencil tools
 * Entirely new Menu/HUD complete
 * Palette Editor
 * Preview when zoomed in
 * Beta Plugin API
### Bug Fixes ###
 * Fixed several UI rendering issues with stamps and sidebar
 * Better handling when switching from config mode to editor modes

## v0.7.9 - Growing just a little bit
### New Features
 * No more Canvas Scrolling
 * Tooltips in lower status bar
### Bug Fixes ###
 * Rewrote mouse driver

## v0.7.1 - Minimum Lovable Product
### New Features ###
 * Keyboard Input - Mouse now optional, but still the optimum control method. Keyboard input allows precise pixel-perfect positioning of your PLOTIT pointer, ideal when used in combination with the mouse.
### Bug Fixes ###
 * Speed ups and Overflow fixes on Fill tool

## v0.7.0 - Minimum Lovable Product
### New Features ###
 * Stand Alone .nex - only the demos used in the "Rogue's Gallery" external to the main app
 * Save your work, both Save, and Save As to keep backups as you go now work! 
 * Freeform Circles (a.k.a. Ellipses) 
 * EyeDropper - select colour from current canvas tool
 * Rubber Stamp tool, with paginated tool settings window
 * Better error handling
 * Corrupt .NXI detection
 * SL2 support
 * Keyboard Hotkey Support
### Bug Fixes ###
 * Sped up Pen Tool, 
 * Sped up Box Tool, especially after multiple uses
 * Left/Right panning arrows no longer backwards!
 * Wierd bug that meant you could not open any more files if you opened one whose filename was 8characters long!
 * Identified lots more still useful debugging to remove from release builds in future too for more speeds ups
 * Zoom Preview no longer corrupts main canvas
 * Fix crash where clicking between tools in Tool Settings window could crash app
 * Fix bug where opening file after viewing credits would sometimes crash app
 * Fix fill bug where paint would overflow under toolbar if window was panned hard left
### Developer Features ###
 * Single Fire Plugin API v0  
 
## v0.7.0
 * Internal Developer Release

### v0.6.7 - Lampros Made Me Do It
### New Features ###
 * ESXDOS file support

## v0.6.6 - #MerryNextmas
### New Features ###
 * All of them
### Bug Fixes ###
 * None

## v0.6.0 
 * Internal Developer Release
 * Initial closed alpha test
