section .rodata
align 16
f_line: dd 0.131, 0.168, 0.189
align 16
s_line: dd 0.534, 0.686, 0.769
align 16
t_line: dd 0.272, 0.349, 0.393

section .text
; rdi - ширина
; rsi - высота
; rdx - указатель на массив оригинальных пикселей
; rcx - указатель на массив новых пикселей

; rdi - указатель на структуру оригинального изображения
; rsi - указатель на структуру нового изображения
global sepia_filter_asm
sepia_filter_asm:
    ; Получение из структур image нужных данных
    xor rax, rax
    
    mov r10, rdi
    mov r11, rsi
    
    mov rdi, [r11]
    mov rsi, [r11+8]
    
    add r10, 16
    add r11, 16
    
    mov rdx, qword[r10]
    mov rcx, qword[r11]
    
    xor r10, r10
    
    xor r8, r8  ; counter height
    .loop_height:
        xor r9, r9  ; counter width
        .loop_width:
            pxor xmm0, xmm0
            pxor xmm1, xmm1
            pxor xmm2, xmm2    
            
            ; Сохранение blue в регистр
            pxor mm0, mm0
            xor rax, rax
            mov al, [rdx]        
            movq mm0, rax  
            cvtpi2ps xmm0, mm0   
            pshufd xmm0, xmm0, 0x00
            xor rax, rax
            movq rax, xmm0
            
            ; Сохранение green в регистр
            pxor mm0, mm0
            xor rax, rax
            mov al, [rdx+1]
            movq mm0, rax
            cvtpi2ps xmm1, mm0
            pshufd xmm1, xmm1, 0x00
            xor rax, rax
            movq rax, xmm1
            
            ; Сохранение red в регистр
            pxor mm0, mm0
            xor rax, rax
            mov al, [rdx+2]
            movq mm0, rax
            cvtpi2ps xmm2, mm0
            pshufd xmm2, xmm2, 0x00
            xor rax, rax
            movq rax, xmm2
            
            ; Перемножение с коэффициентами для сепиа эффекта
            mulps xmm0, [f_line]
            mulps xmm1, [s_line]
            mulps xmm2, [t_line]
            
            ; Суммирование для получения итоговых цветов
            addps xmm0, xmm1
            addps xmm0, xmm2
            
            cvtps2dq xmm0, xmm0
            
            ; Сохранение в память новых цветов
            movd eax, xmm0
            mov [rcx], al
            pshufd xmm0, xmm0, 0xe5
            movd eax, xmm0
            mov [rcx+1], al
            pshufd xmm0, xmm0, 0xe6
            movd eax, xmm0
            mov [rcx+2], al
            
            add rdx, 3
            add rcx, 3
            inc r9
            cmp r9, rdi
            js .loop_width
        inc r8
        cmp r8, rsi
        js .loop_height   
    ret