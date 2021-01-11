.globl	_ZNK9Rectangle7AreaAsmEv

_ZNK9Rectangle7AreaAsmEv:
        push %ebp      /* save old base pointer */
        mov %esp, %ebp /* set ebp to current esp */
        
        #access 
        mov 8(%ebp),%eax

        fld 4(%eax) #we place length_ on s[0]

        fld 8(%eax) #we place width_ on s[0] (length_ = s[1])

        fmulp #s[0]+s[1]

        leave          /* restore ebp and esp */
        ret            /* return to the caller */
