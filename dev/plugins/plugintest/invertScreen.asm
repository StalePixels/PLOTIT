; Simple plugin to flip every pixel in the active L2

	device zxspectrum48
    org $c000

.start push hl
    push de
    push bc
    push af
    push ix
    push iy
    exx
    push hl
    push de
    push bc
    ex af,af
    exx
    push af
    ex af,af

    ld d,9*2                    ;9 is our VRAM MMU

.LoopOuter	ld a,d              ; load the MMU into the accumulator
    nextreg $57,a               ; Technically this is our plugin memoryspace, but we have no
    ld hl,$e000                 ; code up here - if we did 4&5 contain only the core app code

.LoopInner	ld a,(hl)           ; load the pixel into the accumulator
    cpl                         ; flip all the bits
    ld (hl),a                   ; and put the pixel back
    inc l                       ; one down,
    jr nz,LoopInner             ; 48thousand more to go...      Inner Loop
    inc h                       ; and then
    jr nz,LoopInner             ;                               Outer Loop
    inc d                       ; bump the MMU
    ld a,d                      ; are we out of VRAM, because
    cp 12*2                     ; if we hit MMU 12 we have gone too far...
    jr nz,LoopOuter

    ex af,af
    pop af
    ex af,af
    exx
    pop bc
    pop de
    pop hl
    exx
    pop iy
    pop ix
    pop af
    pop bc
    pop de
    pop hl

.last   ret

	savebin "invertScreen.plg",start,.last-start
