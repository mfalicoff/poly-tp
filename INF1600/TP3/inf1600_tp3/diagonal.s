.global matrix_diagonal_asm

matrix_diagonal_asm:
        pushl   %ebp
        movl    %esp, %ebp
        subl    $16, %esp               #allocation des varibles locales
        movl    $0, -4(%ebp)            #met 0 dans r
FOR1:
        movl    -4(%ebp), %eax          #On fait ici la comparaison entre r et matorder
        cmpl    16(%ebp), %eax
        jge     FIN                     #On jump si matorder est superieur
        movl    $0, -8(%ebp)            #On met c a 0 pour le for 2
FOR2:
        movl    -8(%ebp), %eax          #On compare ici c a matorder
        cmpl    16(%ebp), %eax
        jge     FINFOR1                 #Si matorder superieur
        movl    -8(%ebp), %eax          #met c dans eax
        cmpl    -4(%ebp), %eax          # compare c et r
        jne     ELSE                    # si not equal, jump to else
        movl    -4(%ebp), %eax          
        imull   16(%ebp), %eax          #multiplication entre r et matorder
        movl    %eax, %edx              
        movl    -8(%ebp), %eax          
        addl    %edx, %eax              #additione c et eax(r*matorder)
        leal    0(,%eax,4), %edx        
        movl    8(%ebp), %eax           #premier elemnt de inmatdata dans eax
        leal    (%edx,%eax), %ecx       #met la valeur a l'adresse dans ecx
        movl    -4(%ebp), %eax          
        imull   16(%ebp), %eax          #r*matorder
        movl    %eax, %edx              
        movl    -8(%ebp), %eax
        addl    %edx, %eax              #c+r*matorder
        leal    0(,%eax,4), %edx
        movl    12(%ebp), %eax          #premier elemnt de outmatdata
        addl    %eax, %edx              #adresse de outmatdata[c+r*matorder]
        movl    (%ecx), %eax            #contenu de cette addr
        movl    %eax, (%edx)            #on fait le =
        jmp     FINFOR2                 
ELSE:
        movl    -4(%ebp), %eax          #On refait les memes etapes que precedament pur avoir la bonne addresse
        imull   16(%ebp), %eax
        movl    %eax, %edx
        movl    -8(%ebp), %eax
        addl    %edx, %eax
        leal    0(,%eax,4), %edx
        movl    12(%ebp), %eax
        addl    %edx, %eax
        movl    $0, (%eax)              #on met 0 dans le tableau
FINFOR2:
        incl    -8(%ebp)                #on incremnet c
        jmp     FOR2                    
FINFOR1:
        incl    -4(%ebp)                #on increment r
        jmp     FOR1
FIN:
        mov   %ebp, %esp     
        pop   %ebp  
        ret

