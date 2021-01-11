.globl	_ZNK8Cylinder9VolumeAsmEv

_ZNK8Cylinder9VolumeAsmEv:
        push %ebp      /* save old base pointer */
        mov %esp, %ebp /* set ebp to current esp */
        
        #acces
        mov 8(%ebp), %eax 

        mov 0(%eax), %ecx #ecx contains virtual table pointer

        push %eax #stacking this pointer

        call *20(%ecx) #push base area to s[0]

        add $4, %esp #clean parameters

        fld 8(%eax) #push height to s[0], s[1]=base area 

	fmulp #(base area * height)
        
        leave          /* restore ebp and esp */
        ret            /* return to the caller */
