section .data
    a dq 0.5
    b dq 3.0
    c dq 2.5
    d dq 9.5
    e dq 5.0
    f dq -1.5
    g dq -5.0
    h dq 10.0

section .text
global f1
f1:
    push ebp
    mov ebp, esp
    
    fld qword[a]
    fld qword[ebp + 8]
    fld1
    faddp
    fdivp
    fld1
    faddp
    fld qword[b]
    fmulp
    
    leave
    ret

global f2
f2:
    push ebp
    mov ebp, esp
    
    fld qword[ebp + 8]
    fld qword[c]
    fmulp
    fld qword[d]
    fsubp
    
    leave
    ret

global f3
f3:
    push ebp
    mov ebp, esp
    
    fld qword[e]
    fld qword[ebp + 8]
    fdivp
    
    leave
    ret
  
global df1  
df1:
    push ebp
    mov ebp, esp
    
    fld qword[f]
    fld qword[ebp + 8]
    fld1
    faddp
    fld ST0
    fmulp
    fdivp
    
    leave
    ret

global df2
df2:
    push ebp
    mov ebp, esp
    
    fld qword[c]
    
    leave
    ret

global df3
df3:
    push ebp
    mov ebp, esp
    
    fld qword[g]
    fld qword[ebp + 8]
    fld qword[ebp + 8]
    fmulp
    fdivp
    
    leave
    ret

global ddf1
ddf1:
    push ebp
    mov ebp, esp

    fld qword[b]
    fld qword[ebp + 8]
    fld1
    faddp
    fld ST0
    fld ST0
    fmulp
    fmulp
    fdivp

    leave
    ret

global ddf2
ddf2:
    push ebp
    mov ebp, esp

    fldz

    leave
    ret

global ddf3
ddf3:
    push ebp
    mov ebp, esp

    fld qword[h]
    fld qword[ebp + 8]
    fld ST0
    fld ST0
    fmulp
    fmulp
    fdivp

    leave
    ret