.setcpu "6502"
.segment "VECTORS"
    .word Start
    .word Start
    .word Start

.segment "CODE"
Screen0 = $8000
Screen1 = $8100
Screen2 = $8200
Screen3 = $8300

; Starting points for the four quarters of the screen.  Using this
; logic, the screen really ends at 0x83E8, but I don't think we need to
; handle that special case.

Start:
                    ; A holds screen base address
        LDA #$00
        LDX #$00
MainLoop:
        STA Screen0, X
        STA Screen1, X
        STA Screen2, X
        ;STA Screen3, X
        INX
        BNE MainLoop
        TAX         ; Save A
        INX         ; Increment it
        TXA         ; Put it back
        LDX #$00    ; Clear X
        JMP MainLoop
                    ; Define reset vectors
