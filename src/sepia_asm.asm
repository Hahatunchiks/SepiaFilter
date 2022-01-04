global sepia_asm

section .data
 ;.393f, .769f, .189f
 ;.349f, .686f, .168f
 ;.272f, .543f, .131f
 ; store colums

    c1: dd 0.393, 0.349, 0.272, 0.393
    c2: dd 0.769, 0.686, 0.543, 0.769
    c3: dd 0.189, 0.168, 0.131, 0.189

section .text

calculate:
    movdqa xmm3, [rel c1]
    movdqa xmm4, [rel c2]
    movdqa xmm5, [rel c3]
    movdqu xmm0, [rdi]
    movdqu xmm1, [rsi]
    movdqu xmm2, [rdx]
    mulps  xmm0, xmm3
    mulps  xmm1, xmm4
    mulps  xmm2, xmm5
    addps  xmm0, xmm1
    addps  xmm0, xmm2
    movdqu [rdi], xmm0
    ret


sepia_asm:
    mov rsi,  16
    add rsi, rdi
    mov rdx, 32
    add rdx, rdi
    push rdi
    push rsi
    push rdx
    call calculate
    pop rdx
    pop rsi
    pop rdi
    ret


