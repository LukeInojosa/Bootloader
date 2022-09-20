org 0x7c00
jmp 0x0000:start
videomem_addr dw 0a000h ;endereço da memoria de vídeo 
;contadores
 Xcount dw 0
 Ycount dw 0
;struct rectangle
 rec_X       dw 0
 rec_Y       dw 0
 rec_largura dw 0
 rec_altura  dw 0
;tela
 tela_largura dw 320
 tela_altura dw 200
%macro delay_fps 0
    pusha
    mov ah,86h ;função delay da bios
    mov cx,0 ;high word
    mov dx,8236 ;low word
    int 15h
    popa
%endmacro
%macro imprimir_retangulo 4 ;(x,y,largura,altura)[posicao do canto superior esquerdo,tamanho]
     mov ax,%1
     mov bx,%2
     mov cx,%3
     mov dx,%4
     mov [rec_X],ax;pos x
     mov [rec_Y],bx;pos y
     mov [rec_largura],cx;largura
     mov [rec_altura],dx;altura
    call _imprimir_retangulo
%endmacro
_imprimir_retangulo:
    mov es,[videomem_addr];colocando endereço da mem de video em extra segment
    
    mov bx,[tela_largura]
    mov ax,[rec_Y]
    mul bx

    add ax,[rec_X]

    mov di,ax
    
    call clear_registers
   ;imprimindo pixels

    .print_pixel:;imprimir um pixel na memoria de video[320,200]
       ;escrevendo cor no video na posição ax
        mov bl,15

        mov [es:di],bl;só di pode determinar deslocamento
       ;atualizando posição a ser escrita 
        inc cx ;contador da coluna
        inc di
        cmp cx,[rec_largura]
        jle .nao_muda_linha
           ;zera iterador da coluna
            xor cx,cx 
            inc dx
            cmp dx,[rec_altura]

            jge .endprint_pixel

               ;atualizar linha onde pixel sera impresso
                dec di
                sub di,[rec_largura]  ; retorna pro começo
                add di,[tela_largura] ;linha de baixo
                
        .nao_muda_linha:
     jmp .print_pixel   
    .endprint_pixel:
 ret

clear_registers:
    xor ax,ax
    xor bx,bx
    xor cx,cx
    xor dx,dx  
 ret 
initvideo:
    mov al, 13h
    mov ah, 0
    mov bh, 0
    int 10h
    ret
clear_screem:
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

    ; start_game_loop:
    ;     call clear_screem
       imprimir_retangulo 50,50,50,50
    ;  delay_fps
    ;  jmp start_game_loop
    ; .end_game_loop:
    
times 510-($-$$) db 0 ;512 bytes
dw 0xaa55             ;assinatura
