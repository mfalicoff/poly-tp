.globl matrix_transpose_asm

matrix_transpose_asm:
        pushl   %ebp            #Save old base pointer
        movl    %esp, %ebp      #Set ebp to current esp

        ##Allouer l'espace pour r et c
        subl    $16, %esp

        #On assigne r = 0 dans ebp
        movl    $0, -4(%ebp)
Boucle1:
        #On place r dans eax
        movl    -4(%ebp), %eax

        #On compare matorder avec r
        cmpl    16(%ebp), %eax

        #Si matorder >= r on saute au Break
        jge     END

        #Si la condition de la boucle est respecter on continue
        #On assigne c = 0 dans ebp
        movl    $0, -8(%ebp)
Boucle2:
        #On place c dans eax
        movl    -8(%ebp), %eax

        #On compare matorder avec c
        cmpl    16(%ebp), %eax

        #Si matorder >= c on saute au Break
        jge     Break

        #Si la condition de la boucle est respecter on continue
        #On place c dans eax
        movl    -8(%ebp), %eax

        #On multiplie c et matorder 
        imull   16(%ebp), %eax

        #On place (c*matorder) dans edx
        movl    %eax, %edx

        #On place r dans eax
        movl    -4(%ebp), %eax

        #On additionne r et (c*matorder)
        addl    %edx, %eax

        #On place l'adresse de eax dans edx
        leal    0(,%eax,4), %edx

        #On place inmatdata dans eax
        movl    8(%ebp), %eax
        
        #On place l'adresse de (eax+edx) dans ecx
        leal    (%edx,%eax), %ecx

        #On place r dans eax
        movl    -4(%ebp), %eax

        #On multiplie r et matorder
        imull   16(%ebp), %eax

        #On place (r*matorder) dans edx
        movl    %eax, %edx

        #On place c dans eax
        movl    -8(%ebp), %eax

        #On additionne c et (r*matorder)
        addl    %edx, %eax

        #On place l'adresse de eax dans ecx
        leal    0(,%eax,4), %edx

        #On place outmatdata dans eax
        movl    12(%ebp), %eax

        #On ajoute la valeur a l'adresse a eax
        addl    %eax, %edx

        #On place l'adresse de ecx dans eax
        movl    (%ecx), %eax

        #On place eax dans l'adresse de edx
        movl    %eax, (%edx)

        #On sort de Boucle1 donc on incrémente c
        incl    -8(%ebp)
        jmp     Boucle2
Break:
        #On sort de Boucle2 donc on incrémente r
        incl    -4(%ebp)
        jmp     Boucle1
END:
        #restore ebp and esp
        leave  
        #return to the caller 
        ret
