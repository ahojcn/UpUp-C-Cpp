; 改进程序3-3，
; 要求从键盘输入一个十进制数（带符号数）
; 在屏幕上显示输出。

data segment
	num dw 0
data ends

code segment
	assume cs:code,  ds:data
	
start:
	mov ax, data
	mov ds, ax
	
	call dealSign
	
	mov ax, num	; prt ready
	call newline
	call signPrtDec
	
	; return dos
	mov ah, 4ch
	int 21h
	
	dealSign proc near
        mov bx, 0
		mov ah, 1
		int 21h
		cmp al, '-'	; 符号
		jnz SIGN	; 不是'-'
		mov num, 1
		jmp GOGETNUM
		SIGN:	
			;sub al, 30h
			;mov ah, 0
			mov ax, 0	; clear ax -> 0
			mov bx, ax
		GOGETNUM:	
			call getNum	; getNum
			cmp num, 1	;
			jnz	EXIT
			neg bx	; 
		EXIT:
			mov num,  bx
			ret
	dealSign endp
	
	; 十进制输入(无符号)->bx
	getNum proc near
		mov bx,  0
		
		NEXT:
		mov ah,  1	; 获取键盘字符输入	存入al中
		int 21h
		sub al,  30h	; 减去 '0'
		jb RETEXIT	; cf == 1 && zf == 0
		cmp al,  9
		ja RETEXIT	; cf==0 && zf == 0
		cbw	; 字节转换为字 al + ax -> ax
		xchg ax,  bx	; ax <-> bx
		mov cx,  10
		mul cx	; al * cx -> ax
		xchg ax,  bx	; ax <-> bx
		add bx,  ax	; ax+bx -> bx
		jmp NEXT
		
		RETEXIT:
			ret
	getNum endp
	
	; 十进制带符号输出
	signPrtDec proc near
		and ax,  ax
		jns prt10	;不是负数（正数），直接输出
		;负数：取反+1，输出
		mov dl,  '-'	;输出'-'号
		mov ah,  2
		int 21h
		
		; 0110
		; 1111
		; 1001
		;xor bx,  0fh
		;inc bx	;inc 1
		mov ax,  num;;;;;;;;;;;;;;;;
		;mov ax,  data1
		neg ax
	
	prt10:
		;mov ax,  bx
		call prtDec
		ret
	signPrtDec endp
	
	; 十进制输出->ax
	prtDec proc near
		mov cx,  0	; cx -> 0，计数器清 0
		mov bx,  10	; bx -> 10，除10
	q1:
		mov dx,  0	; dx 存余数，清0
		div bx		; dx:ax / bx ->(ax)商，(dx)余数
		xor dx,  30h	; dx ^ 110000
		push dx	; push dx，dx中存的余数，压栈
		inc cx	; cx++，计数器++
		cmp ax,  0
		jnz q1 	; 如果ax（商）不为 0 就继续上面除10操作
	q2:
		pop dx
		mov ah,  2
		int 21h
		loop q2
		ret
	prtDec endp
	
	; \n
	newline proc near
		push ax
		push dx
		mov dx,  0ah
		mov ah,  2
		int 21h
		mov dx,  0dh
		mov ah,  2
		int 21h
		pop dx
		pop ax
		ret
	newline endp
	
code ends
end start