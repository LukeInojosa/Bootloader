org 0x7e00
jmp 0x0000:start

;Textos menu
titulo      db 'FLAPPLY BIRD', 0
jogar       db 'Play (1)', 0
instrucoes  db 'Instruction (2)', 0
creditos    db 'Credits (3)', 0

;instrucoes

;creditos
creditos1 db 'Lucas Inojosa <lims>', 0
creditos2 db 'Luis Felipe <lfro2>', 0
creditos3 db 'Kaylane Lira <kgl>', 0
creditos4 db 'Press Esc to return', 0

;parte do jogo
points dw 0

;score

; macro
%macro delay_fps 0
    pusha
    mov ah,86h ;função delay da bios
    mov cx,0 ;high word
    mov dx,8236 ;low word
    int 15h
    popa
%endmacro

;funções do jogo
initvideo:
    mov al, 13h
    mov ah, 0
    int 10h
    ret


_writechar:
    mov ah, 0xe
    mov bx, 1
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

loopGame:
    inc cx
     cmp cx,1000;o loop roda enquanto cx for diferente de 1000
     je .end_game_loop
	;loop 
        call _writechar

     delay_fps;delay de 1/30 segundos
     jmp loopGame
    .end_game_loop:

;Inicio do programa
start:
    ;Zerando os registradores
    mov ax, 0
    mov ds, ax

    ;Chamando a função Menu
    call Menu

    jmp done

Menu:

    ;Carregando o video
    mov ah, 0
    mov al,12h
    int 10h

    ;Mudando a cor do background para azul escuro
    mov ah, 0bh
    mov bh, 0
    mov bl, 3
    int 10h 

    ;Colocando o Titulo
	mov ah, 02h  ;Setando o cursor
	mov bh, 0    ;Pagina 0
	mov dh, 10    ;Linha
	mov dl, 34   ;Coluna
	int 10h
    mov si, titulo
    call printString

    ;Colocando a string jogar
    mov ah, 02h  ;Setando o cursor
	mov bh, 0    ;Pagina 0
	mov dh, 13   ;Linha
	mov dl, 36   ;Coluna
	int 10h
    mov si, jogar
    call printString
    
    ;Colocando a string intrucoes
    mov ah, 02h  ;Setando o cursor
	mov bh, 0    ;Pagina 0
	mov dh, 16   ;Linha
	mov dl, 32   ;Coluna
	int 10h
    mov si, instrucoes
    call printString
    
    ;Colocando a string creditos
    mov ah, 02h  ;Setando o cursor
	mov bh, 0    ;Pagina 0
	mov dh, 19   ;Linha
	mov dl, 34   ;Coluna
	int 10h
    mov si, creditos
    call printString
    
    ;Selecionar a opcao do usuario
    selecao:
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
        jne selecao
     
play:
    call initvideo
    mov al,3

    call loopGame
    jmp done

;Caso seja selecionado "Instruction (2)"
instrucao:
    ;Carregando o video para limpar a tela
    mov ah, 0
    mov al,12h
    int 10h

    ;Mudando a cor do background para azul escuro
    mov ah, 0bh
    mov bh, 0
    mov bl, 1
    int 10h 

    ;Colocando o titulo
	mov ah, 02h  ;Setando o cursor
	mov bh, 0    ;Pagina 0
	mov dh, 3    ;Linha
	mov dl, 29   ;Coluna
	int 10h
    mov si, instrucoes
    call printString
    ret

ESCinstrucao:    
    ;Para receber o caractere
    mov ah, 0
    int 16h

    ;Apos receber 'Esc' volta pro menu
    cmp al, 27
	je Menu
	jne ESCinstrucao

;Caso seja selecionado "Credits (3)"
credito:
    ;Carregando o video para limpar a tela
    mov ah, 0
    mov al,12h
    int 10h

    ;Mudando a cor do background para azul escuro
    mov ah, 0bh
    mov bh, 0
    mov bl, 3
    int 10h 

    ;Colocando o titulo
	mov ah, 02h  ;Setando o cursor
	mov bh, 0    ;Pagina 0
	mov dh, 3    ;Linha
	mov dl, 29   ;Coluna
	int 10h
    mov si, creditos
    call printString

    ;Colocando a string creditos1
    mov ah, 02h  ;Setando o cursor
	mov bh, 0    ;Pagina 0
	mov dh, 7    ;Linha
	mov dl, 10   ;Coluna
	int 10h
    mov si, creditos1
    call printString

    ;Colocando a string creditos2
    mov ah, 02h  ;Setando o cursor
	mov bh, 0    ;Pagina 0
	mov dh, 9    ;Linha
	mov dl, 10   ;Coluna
	int 10h
    mov si, creditos2
    call printString

    ;Colocando a string creditos3
    mov ah, 02h  ;Setando o cursor
	mov bh, 0    ;Pagina 0
	mov dh, 11   ;Linha
	mov dl, 10   ;Coluna
	int 10h
    mov si, creditos3
    call printString

	;Colocando a string creditos4
    mov ah, 02h  ;Setando o cursor
	mov bh, 0    ;Pagina 0
	mov dh, 20   ;Linha
	mov dl, 10   ;Coluna
	int 10h
    mov si, creditos4
    call printString

ESCcreditos:
	;Para receber o caractere
    mov ah, 0
    int 16h

    ;Apos receber 'Esc' volta pro menu
    cmp al, 27
	je Menu
	jne ESCcreditos

score:
ret

done:
    jmp $
