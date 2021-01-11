.globl	_ZNK8Cylinder12PerimeterAsmEv

factor: .float 2.0 /* use this to mult by two */

_ZNK8Cylinder12PerimeterAsmEv:
        push %ebp      /* save old base pointer */
        mov %esp, %ebp /* set ebp to current esp */
        
        #access 
        mov 8(%ebp), %eax 

        fld 4(%eax) #push the radius s[0]

        fldpi #push pi s[0], radius s[1]

	fld factor #push 2.0f s[0], pi s[1] and radius s[2]

	fmulp #2.0f * pi

	fmulp #2.0f * pi * radius
        
        leave          /* restore ebp and esp */
        ret            /* return to the caller */
