org 0x7e00
jmp 0x0000:start

%macro delay_fps 0
    pusha
    mov ah,86h ;função delay da bios
    mov cx,0 ;high word
    mov dx,8236 ;low word
    int 15h
    popa
%endmacro
initvideo:
    mov al, 13h
    mov ah, 0
    mov bh, 0
    int 10h
    ret
_writechar:
    mov ah, 0xe
    mov bx, 1
    int 10h
    ret
start:
    xor ax,ax 
    mov ds, ax
    mov es, ax

    call initvideo
    mov al,3

    xor cx,cx
    start_game_loop:
     inc cx
     cmp cx,1000;o loop roda enquanto cx for diferente de 1000
     je .end_game_loop
	;loop 
        call _writechar

     delay_fps;delay de 1/30 segundos
     jmp start_game_loop
    .end_game_loop:
