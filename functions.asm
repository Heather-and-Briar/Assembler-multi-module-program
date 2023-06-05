section .data
    a dq 0.35
    b dq 0.95
    c dq 2.7
    three dd 3
    two dd 2
    four dd 4
    six dd 6

global f1
global f2
global f3
global f1test
global f2test
global f3test

global f1p
global f2p
global f3p
global f1testp
global f2testp
global f3testp

section .text
f1:
    push ebp
    mov ebp, esp
    finit
    
    ;   0.35 * x^2 - 0.95 * x + 2.7 = x*(0.35 * x - 0.95) + 2.7
    fld qword[ebp + 8]          ;   x
    fld st0
    fld qword[a]
    fmulp                       ;   0.35 * x
    fld qword[b]
    fsubp                       ;   0.35 * x - 0.95
    fmulp                       ;   x*(0.35 * x - 0.95)
    fld qword[c]
    faddp                       ;   x*(0.35 * x - 0.95) + 2.7
    
    leave
    ret

f1p:
    push ebp
    mov ebp, esp
    finit
    
    ;   0.35 * x - 0.95
    fld qword[ebp + 8]          ;   x
    fld qword[a]
    fmulp                       ;   0.35 * x
    fld qword[b]
    fsubp                       ;   0.35 * x - 0.95
    
    leave
    ret

f2:
    push ebp
    mov ebp, esp
    finit
    
    ;   3*x + 1
    fld qword[ebp + 8]          ;   x
    fild dword[three]
    fmulp                       ;   3*x
    fld1
    faddp                       ;   3*x + 1
    
    leave
    ret
    
f2p:
    push ebp
    mov ebp, esp
    finit
    
    ;   3
    fild dword[three]
    
    leave
    ret
    
f3:
    push ebp
    mov ebp, esp
    finit
    
    ;   1 / (x + 2)
    fld1
    fld qword[ebp + 8]          ;   x
    fild dword[two]
    faddp                       ;   x + 2
    fdivp                       ;   1 / (x + 2)
    
    leave
    ret
    
f3p:
    push ebp
    mov ebp, esp
    finit
    
    ;   -1 / ((x + 2)^2)
    fld1
    fld qword[ebp + 8]          ;   x
    fild dword[two]
    faddp                       ;   x + 2
    fld st0
    fmulp                       ;   (x + 2)^2
    fdivp                       ;   1 / ((x + 2)^2)
    fchs                        ;   -1 / ((x + 2)^2)
    
    leave
    ret
    
f1test:
    push ebp
    mov ebp, esp
    finit
    
    ;   x^2
    fld qword[ebp + 8]          ;   x
    fld st0
    fmulp                       ;   x*x
    
    leave
    ret
    
f1testp:
    push ebp
    mov ebp, esp
    finit
    
    ;   2*x
    fld qword[ebp + 8]          ;   x
    fild dword[two]
    fmulp                       ;   2*x
    
    leave
    ret
    
f2test:
    push ebp
    mov ebp, esp
    finit
    
    ;   x + 6
    fld qword[ebp + 8]          ;   x
    fild dword[six]             ;   6
    faddp
    
    leave
    ret
    
f2testp:
    push ebp
    mov ebp, esp
    finit
    
    ;   1
    fld1
    
    leave
    ret
    
f3test:
    push ebp
    mov ebp, esp
    finit
    
    ;   -3*x + 4
    fild dword[three]
    fld qword[ebp + 8]          ;   x
    fmulp                       ;   3*x
    fchs                        ;   -3*x
    fild dword[four]
    faddp                       ;   -3*x + 4
    
    leave
    ret

f3testp:
    push ebp
    mov ebp, esp
    finit
    
    ;   -3
    fild dword[three]
    fchs
    
    leave
    ret
