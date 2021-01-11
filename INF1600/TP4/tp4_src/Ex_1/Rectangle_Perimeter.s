.globl	_ZNK9Rectangle12PerimeterAsmEv

factor: .float 2.0 /* use this to mult by two */

_ZNK9Rectangle12PerimeterAsmEv:
        push %ebp      /* save old base pointer */
        mov %esp, %ebp /* set ebp to current esp */
        
        
        #access 
        mov 8(%ebp),%eax

        fld 4(%eax) #we place length_ on s[0]

        fld 8(%eax) #we place width_ on s[0] (length_ = s[1])

        faddp #s[0]+s[1]

        fld factor #we push 2.0f

        fmulp #2.0f * (length_ + width_)

        
        
        leave          /* restore ebp and esp */
        ret            /* return to the caller */
