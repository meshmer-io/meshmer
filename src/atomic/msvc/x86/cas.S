        .global         __mmi_atomic_cas_64@12
        .global         __mmi_atomic_dcas@12

        .text
        .code32
__mmi_atomic_cas_64@12:
__mmi_atomic_dcas@12:
        pushl           %ebx

        movl            12(%esp),       %eax
        movl            4(%eax),        %edx
        movl            (%eax),         %eax
        movl            16(%esp),       %ebx
        movl            4(%ebx),        %ecx
        movl            (%ebx),         %ebx
        lock cmpxchg8b  8(%esp)
        jz              1f

        movl            12(%esp),       %ebx
        movl            %edx,           4(%ebx)
        movl            %eax,           (%ebx)
        xorl            %eax,           %eax
        jmp             2f

1:      movl            $0x01,          %eax
2:      popl            %ebx
        ret             $0x0c
