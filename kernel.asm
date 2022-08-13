org 0x7e00
jmp 0x0000:start
videomem_addr dw 0a000h ;endereço da memoria de vídeo 

; flappy img
flappy db 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 14, 14, 14, 14, 14, 0, 15, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 14, 14, 14, 14, 14, 14, 0, 7, 15, 15, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 14, 14, 14, 14, 14, 0, 7, 15, 15, 0, 15, 0, 0, 0, 0, 0, 0, 0, 15, 15, 15, 15, 0, 14, 14, 14, 14, 0, 7, 7, 15, 0, 15, 0, 0, 0, 0, 0, 0, 0, 15, 15, 15, 15, 15, 0, 14, 14, 14, 14, 0, 7, 7, 15, 15, 0, 0, 0, 0, 0, 0, 0, 7, 15, 15, 15, 7, 0, 14, 14, 14, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 0, 14, 14, 14, 14, 0, 12, 12, 12, 12, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 14, 14, 14, 14, 0, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 6, 14, 14, 14, 14, 14, 0, 12, 12, 12, 12, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 6, 6, 6, 6, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0

;struct rectangle
 rec_X dw 0
 rec_Y dw 0
 rec_width dw 0
 rec_height  dw 0

;info screen
 screen_width dw 320
 screen_height dw 200

;vetor de alturas das barras
 vet_heights db 75,105,87,103,106,96,105,121,104,75,125
 pos_vet db 0

;cores de pixel
 preto db 0
 azul db 1
 verde db 2
 cyan db 3
 vermelho db 4
 magenta db 5
 marrom db 6
 branco db 7
 cinza db 8
 azul_claro db 9
 verde_claro db 10
 cyan_claro db 11
 rosa db 12
 magenta_claro db 13
 amarelo db 14
 branco_intenso db 15

; barra_roof (x,y)
 x_barra_roof dw 320
 y_barra_roof dw 0    
 height_barra_roof dw 70
 width_barra_roof dw 20
; barra_floor (x,y)
 x_barra_floor dw 320
 y_barra_floor dw 130
 speed_barra dw 4   
 height_barra_floor dw 70
 width_barra_floor dw 20
; Info do passaro
 bird_x dw 120
 bird_y dw 100

 bird_up dw 25
 bird_down dw 1

 bird_width dw 21
 bird_height dw 20

 bird_x_posFinal dw 141
 bird_y_posFinal dw 120

 bird_max_speed dw 5     ; velocidade max do passaro
 bird_count_speed dw 0   ; contador de velocidade do passaro

; Info tela inicial
 title db 'FLAPPLY BIRD', 0
 playName db 'Play (1)', 0
 instruction db 'Instruction (2)', 0
 credits db 'Credits (3)', 0

; instrucoes
 inst0 db 'INSTRUCOES', 0
 inst1 db '1. Aperte espaco para nao cair', 0
 inst2 db '2. Nao encoste no chao', 0
 inst3 db '3. Nao encoste nos tubos',0 

; creditos
 credits1 db 'Lucas Inojosa <lims>', 0
 credits2 db 'Luis Felipe <lfro2>', 0
 credits3 db 'Kaylane Lira <kgl>', 0
 credits4 db 'Press Esc to return', 0

; número aleatório
 current_number dw 103
 cont_time_random dw 0
 cont_parameter dw 81
 random_temp dw 0

;funcoes para a barra:
    update_Xbarra:
        ;deslocando barra
        mov ax,[x_barra_roof]
        sub ax,[speed_barra]
        cmp ax,0
        jge .nao_volta
        mov ax,320
        .nao_volta:
        ;atualizando posição da barra
        mov [x_barra_roof],ax
        mov [x_barra_floor],ax
    ret
    update_Ybarra:  ;escolher um numero aleatorio entre 125 e 75
        mov bx,[pos_vet]
        inc bx
        cmp bx,11
        jne .atualizar_y
        xor bx,bx

        .atualizar_y:

        mov [pos_vet],bx
        mov si,vet_heights
        add si,bx
        xor ax,ax
        lodsb
        mov [y_barra_roof],ax
    ret
; funcoes/macros base
%macro delay_fps 0
    pusha
    mov ah, 86h ; função delay da bios
    mov cx, 0 ; high word
    mov dx, 16000 ; low word
    int 15h
    popa
%endmacro

clear_registers:
    xor ax,ax
    xor bx,bx
    xor cx,cx
    xor dx,dx  
 ret

initvideo:
    mov al, 13h
    mov ah, 0
    int 10h
    ret

writechar:
    mov ah, 0xe
    mov bx, 3
    int 10h
    ret

printString:
    lodsb
    mov ah, 0xe
    mov bh, 0
    mov bl, 0xf
    int 10h

    cmp al, 0
    jne printString
    ret

scan_key:
        mov ah, 1h
        int 16h
        jnz .key_pressed
        ret
               
            .key_pressed:
                mov ah, 0h
                int 16h
               
        cmp al, 32
        je jump
    jump:
        call update_yBird_up
    ret
screen_clear:
    mov ax,13h
    int 10h
    ret

; funcoes/macros retangulo
%macro print_rectangle 4 ;(x,y,width,height)[posicao do canto superior esquerdo,tam]
     mov ax,%1
     mov bx,%2
     mov cx,%3
     mov dx,%4
     mov [rec_X],ax     ;pos x
     mov [rec_Y],bx     ;pos y
     mov [rec_width],cx     ;width
     mov [rec_height],dx    ;height
     cmp si, flappy
     je _print_bird
    call _print_rectangle
%endmacro

_print_rectangle:
    mov es,[videomem_addr]  ; colocando endereço da mem de video em extra segment
    
    mov bx,[screen_width]
    mov ax,[rec_Y]
    mul bx

    add ax,[rec_X]

    mov di,ax
    
    call clear_registers

    ; imprimindo pixels
    .print_pixel:       ; imprimir um pixel na memoria de video[320,200]
        mov bl, [verde_claro] 
        mov [es:di], bl  ; só di pode determinar deslocamento
        ; atualizando posição a ser escrita 
        inc cx ; contador da coluna
        inc di
        cmp cx,[rec_width]
        jle .same_row
            ; zera iterador da coluna
            xor cx,cx 
            inc dx
            cmp dx,[rec_height]
            jge .endprint_pixel
                ;atualizar linha onde pixel sera impresso
                dec di
                sub di,[rec_width]  ; retorna pro começo
                add di,[screen_width] ; linha de baixo
        .same_row:
         jmp .print_pixel   

    .endprint_pixel:
        ret

_print_bird:
    mov es,[videomem_addr]  ; colocando endereço da mem de video em extra segment
    
    mov bx,[screen_width]
    mov ax,[rec_Y]
    mul bx

    add ax,[rec_X]

    mov di,ax
    
    call clear_registers

    ; imprimindo pixels
    .print_pixel:       ; imprimir um pixel na memoria de video[320,200]
        lodsb 
        mov [es:di], al  ; só di pode determinar deslocamento
        ; atualizando posição a ser escrita 
        inc cx ; contador da coluna
        inc di
        cmp cx,[rec_width]
        jle .same_row
            ; zera iterador da coluna
            xor cx,cx 
            inc dx
            cmp dx,[rec_height]
            jge .endprint_pixel
                ;atualizar linha onde pixel sera impresso
                dec di
                sub di,[rec_width]  ; retorna pro começo
                add di,[screen_width] ; linha de baixo
        .same_row:
         jmp .print_pixel   

    .endprint_pixel:
        ret

; funcoes do passaro
update_yBird_up:
    mov ax, [bird_y]
    sub ax, [bird_up]
    mov [bird_y], ax

    mov ax, [bird_y_posFinal]
    sub ax, [bird_up]
    mov [bird_y_posFinal], ax

    mov ax, 1
    mov [bird_down], ax
    ret

update_yBird_down:
    mov ax, [bird_y]
    add ax, [bird_down]
    mov [bird_y], ax

    mov ax, [bird_y_posFinal]
    add ax, [bird_down]
    mov [bird_y_posFinal], ax
    ret

update_birdSpeed:
    inc word[bird_count_speed]
    mov ax, [bird_count_speed]
    mov bx, [bird_max_speed]
    cmp ax, bx
    je inc_birdSpeed
    ret

inc_birdSpeed:
    mov ax, [bird_down]
    cmp ax, 3
    jne .sum_speed
    .sum_speed:   
        inc word[bird_down]
        mov ax, 0
        mov [bird_count_speed], ax
    ret
 ret

print_bird:
    call update_birdSpeed
    call update_yBird_down
    call clear_registers
    mov si, flappy
    print_rectangle [bird_x], [bird_y], [bird_width], [bird_height]
 ret 

; funcoes do jogo
collision:    
    mov ax,[bird_x]
    add ax,10
    mov bx,[bird_y]
    add bx,10

    mov cx,[x_barra_floor]
    cmp ax,cx
    jle .collision_not_exist
    add cx,[width_barra_floor]
    cmp ax,cx
    jge .collision_not_exist
    mov cx,[y_barra_floor]
    cmp bx,cx
    jge collision_exist
    mov cx,[y_barra_roof]
    add cx,[height_barra_roof]
    cmp bx,cx
    jle collision_exist
 .collision_not_exist:
 ret

collision_exist:
    ; Reiniciando vairáveis
    mov ax, 320
    mov [x_barra_roof], ax
    mov [x_barra_floor], ax


    mov ax, 120
    mov [bird_x], ax

    mov ax, 100
    mov [bird_y], ax

    mov ax, 120
    mov [bird_y_posFinal], ax

    add ax, 20
    mov [bird_y_posFinal], ax

    mov ax, 1
    mov [bird_down], ax
    
    mov ax, 21
    mov [bird_width], ax

    mov ax, 20
    mov [bird_height], ax

    mov ax, 0
    mov [bird_count_speed], ax


    delay_fps
    call screen_clear 
    jmp menu 
 ret

; funcoes para número aleatório:
random_int:
    mov ax, [current_number]
    mov bx, 15
    mul bx
    mov bx, 177
    mul bx
    mov bx, 127
    div bx
    mov [current_number], dx
    ret

update_random_number:
    mov ax, [cont_time_random]
    add ax, 1
    mov [cont_time_random], ax
    cmp ax, [cont_parameter]
    je new_random
    ret

new_random:
    xor bx, bx
    mov [cont_time_random], bx

    call random_int
    mov ax, [current_number]
    mov [height_barra_roof], ax

    add ax, 60
    mov [y_barra_floor], ax
    xor bx, bx
    
    add bx, 200
    sub bx, ax
    mov [height_barra_floor], bx

    ret

loopGame:   ;loop cx[xbarra,xbarra+3]
    call scan_key
    call print_bird
    call update_Xbarra
    call update_random_number
    print_rectangle [x_barra_floor], [y_barra_floor], [width_barra_floor], [height_barra_floor]
    print_rectangle [x_barra_roof], [y_barra_roof], [width_barra_roof], [height_barra_roof]
    call collision

    delay_fps               ; delay de 1/30 segundos
    call screen_clear       ; limpar screen a cada frame
    jmp loopGame

    .end_game_loop:


;Inicio do programa
start:
    ;Zerando os registradores
    mov ax, 0
    mov ds, ax

    call menu

    jmp done

menu:

    ;Colocando um número pseudoaleatório
    int 0x1A
    mov [current_number], dx

    ;Carregando o video
    mov ah, 0
    mov al,12h
    int 10h

    ;Mudando a cor do background para ciano
    mov ah, 0bh
    mov bh, 0
    mov bl, [cyan]
    int 10h 

    ;Colocando o titulo
	mov ah, 02h  ;Setando o cursor
	mov bh, 0    ;Pagina 0
	mov dh, 10   ;Linha
	mov dl, 34   ;Coluna
	int 10h
    mov si, title
    call printString

    ;Colocando a string play
    mov ah, 02h  ;Setando o cursor
	mov bh, 0    ;Pagina 0
	mov dh, 13   ;Linha
	mov dl, 36   ;Coluna
	int 10h
    mov si, playName
    call printString
    
    ;Colocando a string intrucoes
    mov ah, 02h  ;Setando o cursor
	mov bh, 0    ;Pagina 0
	mov dh, 16   ;Linha
	mov dl, 32   ;Coluna
	int 10h
    mov si, instruction
    call printString
    
    ;Colocando a string credits
    mov ah, 02h  ;Setando o cursor
	mov bh, 0    ;Pagina 0
	mov dh, 19   ;Linha
	mov dl, 34   ;Coluna
	int 10h
    mov si, credits
    call printString

    
    ;Selecionar a opcao do usuario
    selected_key:
        ;Receber a opção
        mov ah, 0
        int 16h
        
        ;Comparando com '1'
        cmp al, 49
        je play
        
        ;Comparando com '2'
        cmp al, 50
        je instrucao
        
        ;Comparando com '3'
        cmp al, 51
        je credito
        
        ;Caso não seja nem '1' ou '2' ou '3' ele vai receber a string dnv
        jne selected_key
     
play:
    call initvideo ;set video mode 
    mov al,3

    mov cx,160
    mov dx,100
    call loopGame
    jmp done

;Caso seja selecionado "Instruction (2)"
instrucao:
    ;Carregando o video para limpar a screen
    mov ah, 0
    mov al,12h
    int 10h

    ;Mudando a cor do background para ciano
    mov ah, 0bh
    mov bh, 0
    mov bl, [cyan]
    int 10h 

    ;Colocando o title
	mov ah, 02h  ;Setando o cursor
	mov bh, 0    ;Pagina 0
	mov dh, 5   ;Linha
	mov dl, 34   ;Coluna
	int 10h
    mov si, inst0
    call printString

    ;Colocando a string 
    mov ah, 02h  ;Setando o cursor
	mov bh, 0    ;Pagina 0
	mov dh, 10   ;Linha
	mov dl, 23   ;Coluna
	int 10h
    mov si, inst1
    call printString
    
    ;Colocando a string 
    mov ah, 02h  ;Setando o cursor
	mov bh, 0    ;Pagina 0
	mov dh, 13   ;Linha
	mov dl, 23   ;Coluna
	int 10h
    mov si, inst2
    call printString
    
    ;Colocando a string
    mov ah, 02h  ;Setando o cursor
	mov bh, 0    ;Pagina 0
	mov dh, 16   ;Linha
	mov dl, 23   ;Coluna
	int 10h
    mov si, inst3
    call printString

    ;Colocando a string
    mov ah, 02h  ;Setando o cursor
	mov bh, 0    ;Pagina 0
	mov dh, 23   ;Linha
	mov dl, 29   ;Coluna
	int 10h
    mov si, credits4
    call printString

ESCinstrucao:    
    ;Para receber o caractere
    mov ah, 0
    int 16h

    ;Apos receber 'Esc' volta pro menu
    cmp al, 27
	je menu
	jne ESCinstrucao

;Caso seja selecionado "Credits (3)"
credito:
    ;Carregando o video para limpar a screen
    mov ah, 0
    mov al,12h
    int 10h

    ;Mudando a cor do background para ciano
    mov ah, 0bh
    mov bh, 0
    mov bl, [cyan]
    int 10h 

    ;Colocando o title
	mov ah, 02h  ;Setando o cursor
	mov bh, 0    ;Pagina 0
	mov dh, 3    ;Linha
	mov dl, 29   ;Coluna
	int 10h
    mov si, credits
    call printString

    ;Colocando a string credits1
    mov ah, 02h  ;Setando o cursor
	mov bh, 0    ;Pagina 0
	mov dh, 7    ;Linha
	mov dl, 10   ;Coluna
	int 10h
    mov si, credits1
    call printString

    ;Colocando a string credits2
    mov ah, 02h  ;Setando o cursor
	mov bh, 0    ;Pagina 0
	mov dh, 9    ;Linha
	mov dl, 10   ;Coluna
	int 10h
    mov si, credits2
    call printString

    ;Colocando a string credits3
    mov ah, 02h  ;Setando o cursor
	mov bh, 0    ;Pagina 0
	mov dh, 11   ;Linha           
	mov dl, 10   ;Coluna
	int 10h
    mov si, credits3
    call printString

	;Colocando a string credits4
    mov ah, 02h  ;Setando o cursor
	mov bh, 0    ;Pagina 0
	mov dh, 20   ;Linha
	mov dl, 10   ;Coluna
	int 10h
    mov si, credits4
    call printString

ESCcredits:
	;Para receber o caractere
    mov ah, 0
    int 16h

    ;Apos receber 'Esc' volta pro menu
    cmp al, 27
	je menu
	jne ESCcredits

score:
ret

done:
    jmp $
