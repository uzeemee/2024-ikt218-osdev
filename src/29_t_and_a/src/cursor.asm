global move_cursor
global enable_cursor

section .text

; Enable the cursor
enable_cursor:
    mov ah, 0x01         ; AH = 0x01 (function to set cursor properties)
    mov ch, byte [start_scanline]   ; CH = start scanline
    mov cl, byte [end_scanline]     ; CL = end scanline
    int 0x10             ; BIOS interrupt call
    ret

; Disable the cursor
disable_cursor:
    mov ah, 0x01         ; AH = 0x01 (function to set cursor properties)
    mov ch, 0x3F         ; CH = 0x3F (disable cursor)
    int 0x10             ; BIOS interrupt call
    ret

; Move the cursor
move_cursor:
    mov ah, 0x02         ; AH = 0x02 (function to set cursor position)
    mov bh, 0x00         ; BH = display page (usually 0)
    mov dh, byte [row]   ; DH = row
    mov dl, byte [column] ; DL = column
    int 0x10             ; BIOS interrupt call
    ret

; Get cursor data
get_cursor_data:
    mov ah, 0x03         ; AH = 0x03 (function to get cursor position and shape)
    mov bh, 0x00         ; BH = display page (usually 0)
    int 0x10             ; BIOS interrupt call
    ; The return values:
    ; CH = start scanline
    ; CL = end scanline
    ; DH = row
    ; DL = column
    ret

section .data
start_scanline db 0   ; Define start scanline variable
end_scanline db 15    ; Define end scanline variable
row db 0              ; Define row variable
column db 0           ; Define column variable


