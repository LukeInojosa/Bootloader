org 0x500
jmp 0x0000:start
 
;como o endereço dado para o kernel é 0x7e00, devemos
;utilizar o método de shift left (hexadecimal)
;e somar o offset no adress base, para rodarmos o kernel.

runningKernel db 'Rodando Kernel', 0
dot db '.', 0
finalDot db '.', 10, 13, 0

cleanScreen:
;; Limpa a tela dos caracteres colocados pela BIOS
	; Set the cursor to top left-most corner of screen
	mov dx, 0 
    mov bh, 0      
    mov ah, 0x2
    int 0x10

    ; print 2000 blanck chars to clean  
    mov cx, 2000 
    mov bh, 0
    mov al, 0x20 ; blank char
    mov ah, 0x9
    int 0x10
    
    ;Reset cursor to top left-most corner of screen
    mov dx, 0 
    mov bh, 0      
    mov ah, 0x2
    int 0x10
ret

printString: 
;; Printa a string que esta em si    
	
	lodsb
	cmp al, 0
	je exit

	mov ah, 0xe
	int 10h	

	mov dx, 70;tempo do delay
	call delay 
	
	jmp printString
exit:
ret

delay: 
;; Função que aplica um delay(improvisado) baseado no valor de dx
	mov bp, dx
	back:
	dec bp
	nop
	jnz back
	dec dx
	cmp dx,0    
	jnz back
ret

printDots:
;; Printa os pontos das reticências
	mov cx, 2

	for:
		mov si, dot
		call printString
		mov dx, 200
		call delay
	dec cx
	cmp cx, 0
	jne for

	mov dx, 300
	call delay
	mov si, finalDot
	call printString
	
ret

start:

	mov bl, 10 ; Seta cor dos caracteres para verde
	call cleanScreen

    ;parte pra printar as mensagens que quisermos

    mov si, runningKernel
    call printString
	call printDots

	xor ax, ax
    mov ds, ax
    mov es, ax

    reset:
        mov ah, 00h ;reseta o controlador de disco
        mov dl, 0   ;floppy disk
        int 13h

        jc reset    ;se o acesso falhar, tenta novamente

        jmp load_kernel

    load_kernel:
        ;Setando a posição do disco onde kernel.asm foi armazenado(ES:BX = [0x7E00:0x0])
        mov ax,0x7E0	;0x7E0<<1 + 0 = 0x7E00
        mov es,ax
        xor bx,bx		;Zerando o offset

        mov ah, 0x02 ;le o setor do disco
        mov al, 20  ;porção de setores ocupados pelo kernel.asm
        mov ch, 0   ;track 0
        mov cl, 3   ;setor 3
        mov dh, 0   ;head 0
        mov dl, 0   ;drive 0
        int 13h

        jc load_kernel ;se o acesso falhar, tenta novamente

        jmp 0x7e00  ;pula para o setor de endereco 0x7e00, que é o kernel

  


    times 510-($-$$) db 0 ;512 bytes
    dw 0xaa55	
