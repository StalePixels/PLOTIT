PLOTIT API
-

PUBLIC MEMORY MAP
--
Data in this area is intended to be "used" by your plugin.  
The definition of what that use is is your choice. Remember to restore it if you change it is all!


ENTRYPOINT TYPE BITMASKS
--

| BIT  | WHEN SET
|------|----
|  1   | Instant Execute
|      | Plugin will execute as soon as selected (CapsJ in current dev-build)
|  -   | 
|  2   | Execute on Mouse Click
|      | Menu will close immediately but plug in not execute until the next mouseclick
|  -   | 
|  3   | *reserved*
|  -   | 
|  4   | *reserved*
|  -   | 
|  5   | *reserved*
|  -   | 
|  6   | *reserved*
|  -   | 
|  7   | *reserved*
|  -   | 
|  8   | *reserved*


ENTRYPOINT TYPE BITMASKS
--
| BIT  | WHEN SET
|------|----
|  1   | Create Undo entry before execution
|  -   |
|  2   | *reserved*
|  -   |
|  3   | *reserved*
|  -   |
|  4   | *reserved*
|  -   |
|  5   | *reserved*
|  -   |
|  6   | *reserved*
|  -   |
|  7   | *reserved*
|  -   |
|  8   | *reserved*

ENTRYPOINT TYPE BITMASKS
--
