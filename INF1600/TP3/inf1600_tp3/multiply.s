.globl matrix_multiply_asm

matrix_multiply_asm:
        pushl   %ebp
        movl    %esp, %ebp
        subl    $16, %esp               #allocation des varibles locales
        movl    $0, -4(%ebp)            #met 0 dans r
FOR1:
        movl    -4(%ebp), %eax          #On fait ici la comparaison entre r et matorder
        cmpl    20(%ebp), %eax
        jge     FIN                     #On jump si matorder est superieur
        movl    $0, -8(%ebp)            #On met c a 0 pour le for 2
FOR2:
        movl    -8(%ebp), %eax          
        cmpl    20(%ebp), %eax           #comparaison de matorder avec c
        jge     FINFOR1
        movl    $0, -16(%ebp)            #met 0 dans elem
        movl    $0, -12(%ebp)            # met 0 dans i
FOR3:
        movl    -12(%ebp), %eax                 
        cmpl    20(%ebp), %eax           #compare matorder avec i
        jge     EGAL
        movl    -4(%ebp), %eax          #met r dans eax
        imull   20(%ebp), %eax          #multiplie r*matorder
        movl    %eax, %edx
        movl    -12(%ebp), %eax         #met i dans eax
        addl    %edx, %eax              #addition c+r*matorder
        leal    0(,%eax,4), %edx        
        movl    8(%ebp), %eax           #met inmatdata1 dans eax
        addl    %edx, %eax              #On ajoute les deux addr pour avoir l'addresse de inmatdata1[i+r*matorder] 
        movl    (%eax), %edx            #On extrait la velur de cette addr
        movl    -12(%ebp), %eax         #On repete pour l'autre tableau
        imull   20(%ebp), %eax
        movl    %eax, %ecx
        movl    -8(%ebp), %eax
        addl    %ecx, %eax
        leal    0(,%eax,4), %ecx
        movl    12(%ebp), %eax
        addl    %ecx, %eax
        movl    (%eax), %eax
        imull   %edx, %eax              #multiplication entre les deux tableaux
        addl    %eax, -16(%ebp)         #met la valur de la multiplication dans elem
        incl    -12(%ebp)               #incremente i
        jmp     FOR3
EGAL:
        movl    -4(%ebp), %eax          #comme dans for2, on cherche l'adresse de outmatdata[c+r*matorder]
        imull   20(%ebp), %eax
        movl    %eax, %edx
        movl    -8(%ebp), %eax
        addl    %edx, %eax
        leal    0(,%eax,4), %edx
        movl    16(%ebp), %eax          
        addl    %eax, %edx
        movl    -16(%ebp), %eax         #on met elem dans eax
        movl    %eax, (%edx)            #on met elem a l'addr de outmatdata[c + r * matorder]
        incl    -8(%ebp)                #increment c
        jmp     FOR2
FINFOR1:
        incl    -4(%ebp)                #increment r
        jmp     FOR1
FIN:
        mov   %ebp, %esp     
        pop   %ebp  
        ret