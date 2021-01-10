; This began life as the same code in the "plugintest" folder, by Jim Bagley - please see there for his
;  original version - here I've done nothing more than tweak the memory checks, and port it to sjasmplus
;
;           build with
;                   sjasmplus invertScreen.asm
;           will result in a "bank.bin", exactly 16k in size
;           this file is suitable for use with make.sh for adding headers;
;
;               -Dx 2012/01/08

                DEVICE ZXSPECTRUMNEXT
                ORG $c000

                push hl                     ; All these pushes are paranoia, and not required
                push de                     ; but this "boilerplate" is useful for other plugin
                push bc                     ; authors.   This "short and sweet" version is that
                push af                     ; you should back up, and restore, anything you change
                push ix                     ; that's not explicitly named as "changable" or
                push iy                     ; restored at exit by the plugin docs.
                exx                         ;
                push hl                     ; And, yes, that includes MMUs, SysVars, and
                push de                     ; the registers - *ALL* the registers, if
                push bc                     ; that turns out to be something you're changing...
                ex af,af                    ;
                exx                         ;
                push af                     ; And (see the bottom for details) remember to put
                ex af,af                    ;  everything back again

                ld d,9*2                    ;9 is our VRAM MMU

LoopOuter:	    ld a,d                      ; load the MMU into the accumulator
                nextreg $57,a               ; Technically this is our plugin memoryspace, but we have no
                ld hl,$e000                 ; code up here - if we did 4&5 contain only the core app code

LoopInner:	    ld a,(hl)                   ; load the pixel into the accumulator
                cpl                         ;   flip all the bits
                ld (hl),a                   ;   and put the pixel back
                inc l                       ; one down,
                jr nz,LoopInner             ; 48thousand more to go...      Inner Loop Low Byte &
                inc h                       ;                   and then
                jr nz,LoopInner             ;                               High Byte part
                inc d                       ; bump the MMU
                ld a,d                      ;   are we out of VRAM?
                cp 12*2                     ; if we hit MMU 12 we have gone too far...
                jr nz,LoopOuter             ;   Start on next MMU

                ex af,af                    ; Basically undo all the boilerplate from the top.
                pop af                      ;
                ex af,af                    ; And, as mentioned up there, you probably don't
                exx                         ; need all of this - it's just here to both "remind you"
                pop bc                      ; and as to serve as a boilerplate new plugin authors
                pop de                      ; can use and built upon
                pop hl                      ;
                exx                         ; Andand, just like above, all the registers... :)
                pop iy                      ;
                pop ix                      ;
                pop af                      ;
                pop bc                      ;
                pop de                      ;
                pop hl                      ;

                ret                         ; Andandand, remember to return to PLOTIT when done :-P

                SAVEBIN "bank.bin",$c000,$ffff