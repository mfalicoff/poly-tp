.globl	_ZNK8Cylinder7AreaAsmEv

_ZNK8Cylinder7AreaAsmEv:
        push %ebp      /* save old base pointer */
        mov %esp, %ebp /* set ebp to current esp */
        
        #acces
        mov 8(%ebp), %eax 

        mov 0(%eax), %ecx #ecx contains virtual table pointer
        push %eax #stacking this pointer
        call *20(%ecx) #push base areas to s[0]

        mov 0(%eax), %ecx #ecx contains virtual table pointer
        push %eax #stacking this pointer
        call *28(%ecx) #push lateral areas to s[0], s[1]=base areas

        faddp #(base areas + lateral areas)
        
        leave          /* restore ebp and esp */
        ret            /* return to the caller */
