#!/bin/bash
#  VERSION 1
#
#  DEV NOTES
#
#   Current BITMASK for entrypoint types
#     BIT     WHEN SET
#      1       Instant Execute
#               Plugin will execute as soon as selected
#      2       Execute on Mouse Click
#               Menu will close, plug in execute on next
#               mouseclick
#      3
#      4
#      5
#      6
#      7
#      8       Writes Banks 17->24 (128k total) to SD
#               and reloads original data after plugin
#               exits.

#   Current BITMASK for pre-flight options
#     BIT     WHEN SET
#      1       Create undo restore point before execute
#      2
#      3
#      4
#      5
#      6
#      7
#      8
#   See dev/docs/api.md for more details

## A Shell script to turn a .BIN file into a .PLP file
#
#  A .PLP file is an exported memorybank, starting at 0xC000, and ending at most 0xFFFF
#   prepended with a special header to tell PLOTIT how to handle and display the menu

##
#
# Plugin headers are exactly 44bytes long, including the entry count, and menu name
#  *PLUS* an additional 18bytes per entry point
# Plugin bodies are 16384 bytes long (the below script takes care of padding any
#  that is required during assembly
# Plugins *ARE* checked for a size-match against their Entry Count in the plugin
#  header - i.e. a valid PLP file is *at least* 16446 - malformed plugins are rejected

# Create a new blank file, exactly 16k long. We cheat here, and use a premade one - exactly 16k of NULL bytes...
cp util/blank16k.bin /tmp/test.plotit_plugin_bin

# Replace the NULL bytes with the output of our compile -- this handles any insances where we're too short with padding
dd conv=notrunc if=bank.bin of=/tmp/test.plotit_plugin_bin

# PLOTIT VERSION CHECK HEADER - RESERVED (DO NOT CHANGE)
echo -n -e "PLOTIT-PLUGIN-v1\x00" > test.plotit_plugin_header

# PLUGIN MENU TITLE - UCHAR[16] Fixed length string - menu title
echo -n -e "Jim Was 'Ere    " >> test.plotit_plugin_header

# PLUGIN VERSION MAJOR - UINT8
echo -n -e "\x00" >> test.plotit_plugin_header

# PLUGIN VERSION MINOR - UINT8
echo -n -e "\x01" >> test.plotit_plugin_header

# PLUGIN VERSION HASH - UCHAR[8]
echo -n -e "ANY HASH" >> test.plotit_plugin_header

# PLUGIN ENTRY COUNT - UINT8
echo -n -e "\x04" >> test.plotit_plugin_header                           # Entry Count in this plugin (4)


## PLUGIN ENTRY LOOP STARTS NOW #1
### PLUGIN DEFINITION FLAGS - UINT8
echo -n -e "\x01"               >> test.plotit_plugin_header             # INSTANT EXECUTE
### PLUGIN PREFLIGHT FLAGS - UINT8
echo -n -e "\x00"               >> test.plotit_plugin_header             # No undo created before execute
### PLUGIN ENTRY NAME = UCHAR[16]
echo -n -e "Invert Now      "   >> test.plotit_plugin_header             # String, fixed length, no terminator
## PLUGIN ENTRY LOOP ENDS NOW #2


## PLUGIN ENTRY LOOP STARTS NOW #2
### PLUGIN DEFINITION FLAGS - UINT8
echo -n -e "\x01"               >> test.plotit_plugin_header             # INSTANT EXECUTE
### PLUGIN PREFLIGHT FLAGS - UINT8
echo -n -e "\x01"               >> test.plotit_plugin_header             # Restore point created before execute
### PLUGIN ENTRY NAME = UCHAR[16]
echo -n -e "Pnoid Invert Now"   >> test.plotit_plugin_header             # String, fixed length, no terminator
## PLUGIN ENTRY LOOP ENDS NOW #2


## PLUGIN ENTRY LOOP STARTS NOW #3
### PLUGIN DEFINITION FLAGS - UINT8
echo -n -e "\x02"               >> test.plotit_plugin_header             # CLICK EXECUTE
### PLUGIN PREFLIGHT FLAGS - UINT8
echo -n -e "\x00"               >> test.plotit_plugin_header             # No undo created before execute
### PLUGIN ENTRY NAME = UCHAR[16]
echo -n -e "      Invert L8r"   >> test.plotit_plugin_header             # String, fixed length, no terminator
## PLUGIN ENTRY LOOP ENDS NOW #3


## PLUGIN ENTRY LOOP STARTS NOW #4
### PLUGIN DEFINITION FLAGS - UINT8
echo -n -e "\x02"               >> test.plotit_plugin_header             # CLICK EXECUTE
### PLUGIN PREFLIGHT FLAGS - UINT8
echo -n -e "\x01"               >> test.plotit_plugin_header             # Restore point created before execute
### PLUGIN ENTRY NAME = UCHAR[16]
echo -n -e "Pnoid Invert L8r"   >> test.plotit_plugin_header             # String, fixed length, no terminator
## PLUGIN ENTRY LOOP ENDS NOW #4


cat test.plotit_plugin_header > test.plp
cat /tmp/test.plotit_plugin_bin >> test.plp
rm /tmp/test.plotit_plugin_bin


