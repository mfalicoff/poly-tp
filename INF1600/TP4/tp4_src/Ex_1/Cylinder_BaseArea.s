.globl	_ZNK8Cylinder11BaseAreaAsmEv

_ZNK8Cylinder11BaseAreaAsmEv:
        push %ebp      /* save old base pointer */
        mov %esp, %ebp /* set ebp to current esp */
        
        #acces
        mov 8(%ebp), %eax 

        fld 4(%eax) #push radius to s[0]

	fld 4(%eax) #push radius to s[0], s[1] = radius ligne 10

        fldpi #push pi on s[0], s[1]=radius and s[2]=radius

	fmulp #pi*radius

        fmulp #pi*radius*radius
        
        leave          /* restore ebp and esp */
        ret            /* return to the caller */
