.globl	_ZNK9Rectangle11DiagonalAsmEv

_ZNK9Rectangle11DiagonalAsmEv:
        push %ebp      /* save old base pointer */
        mov %esp, %ebp /* set ebp to current esp */
        
        #access 
        mov 8(%ebp),%eax

        fld 4(%eax) #we place length_ on s[0]
        fld 4(%eax) #we place length_ on s[0] (ligne 10 = s[1])

        fmulp #(length_ * length_) on s[0]

        fld 8(%eax) #we place width_ on s[0]
        fld 8(%eax) #we place width_ on s[0], ligne 15 on s[1] and ligne 13 on s[2]

        fmulp #(width_ * width_) on s[0] and (length_ * length_) on s[1]

        faddp #s[0]+s[1]

        fsqrt #sqrt(ligne 20)
        
        leave          /* restore ebp and esp */
        ret            /* return to the caller */
