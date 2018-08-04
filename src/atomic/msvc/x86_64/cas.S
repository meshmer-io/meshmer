        .global         _mmi_atomic_cas_64
        .global         _mmi_atomic_dcas

        .text
        .code64
_mmi_atomic_cas_64:
        movq            (%r8),          %r8
        movq            (%rdx),         %rax
        lock cmpxchg    %r8,            (%rcx)
        jz              1f

        movq            %rax,           (%rdx)
        xorq            %rax,           %rax
        ret

1:      movq            $0x01,          %rax
        ret

_mmi_atomic_dcas:
        movq            %rbx,           %r9
        movq            %rdx,           %r10
        
        movq            (%rdx),         %rax
        movq            8(%rdx),        %rdx
        xchg            %rcx,           %r8
        movq            (%rcx),         %rbx
        movq            8(%rcx),        %rcx
        lock cmpxchg16b (%r8)
        jz              1f

        movq            %rdx,           8(%r10)
        movq            %rax,           (%r10)
        xorq            %rax,           %rax
        jmp             2f
        
1:      movq            $0x01,          %rax
2:      movq            %r9,            %rbx
        ret
