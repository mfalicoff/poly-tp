.globl	_ZNK8Cylinder14LateralAreaAsmEv

_ZNK8Cylinder14LateralAreaAsmEv:
        push %ebp      /* save old base pointer */
        mov %esp, %ebp /* set ebp to current esp */
        
        #acces
        mov 8(%ebp), %eax 

        mov 0(%eax), %ecx #ecx contains virtual table pointer

        push %eax #stacking this pointer

        call *12(%ecx) #push parameter to s[0]

        add $4, %esp #clean parameters

        fld 8(%eax) #push height to s[0], s[1]=parameter

	fmulp #(parameter * height)
        
        leave          /* restore ebp and esp */
        ret            /* return to the caller */
