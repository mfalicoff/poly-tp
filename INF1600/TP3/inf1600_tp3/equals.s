.globl matrix_equals_asm

matrix_equals_asm:
        pushl   %ebp            #Save old base pointer
        movl    %esp, %ebp      #Set ebp to current esp

        #Allouer l'espace pour r et c
        subl    $16, %esp

        #On assigne r = 0 dans ebp
        movl    $0, -4(%ebp)
Boucle1:
        #On place r dans eax 
        movl    -4(%ebp), %eax

        #On compare matorder avec r
        cmpl    16(%ebp), %eax

        #Si matorder >= r on saute au Break1
        jge     Break1

        #Si la condition de la boucle est respecter on continue
        #On assigne c = 0 dans ebp
        movl    $0, -8(%ebp)
Boucle2:
        #On place c dans eax
        movl    -8(%ebp), %eax

        #On compare matorder avec c
        cmpl    16(%ebp), %eax

        #Si matorder >= c on saute au Break2
        jge     Break2

        #Si la condition de la boucle est respecter on continue
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

        #On place l'adresse de eax dans edx
        leal    0(,%eax,4), %edx

        #On place inmatdata1 dans eax
        movl    8(%ebp), %eax

        #On ajoute la valeur a l'adresse a eax
        addl    %edx, %eax

        #On place l'adresse de eax dans edx
        movl    (%eax), %edx

        #On place r dans eax
        movl    -4(%ebp), %eax

        #On multiplie r et matorder 
        imull   16(%ebp), %eax

        #On place (r*matorder) dans ecx
        movl    %eax, %ecx

        #On place c dans eax
        movl    -8(%ebp), %eax

        #On additionne c et (r*matorder)
        addl    %ecx, %eax

        #On place l'adresse de eax dans ecx
        leal    0(,%eax,4), %ecx

        #On place inmatdata2 dans eax
        movl    12(%ebp), %eax
        
        #On ajoute la valeur a l'adresse a eax
        addl    %ecx, %eax

        #On place l'adresse de eax dans eax
        movl    (%eax), %eax
        
        #On compare inmatdata1 et inmatdata2
        cmpl    %eax, %edx

        #Si inmatdata1 == inmatdata2 on saute a Egale
        je      Egale

        #Si la comparaison n'est pas égale on retourne 0
        #On place 0 dans eax
        movl    $0, %eax
        #On saute a la fin du code car il est fini
        jmp     END
Egale:
        #On sort de Boucle2 donc on incrémente c
        incl    -8(%ebp)

        #On recommence la Boucle2
        jmp     Boucle2
Break2:
        #On sort de Boucle1 donc on incrémente r
        incl    -4(%ebp)

        #On recommence la Boucle2
        jmp     Boucle1
Break1:
        #On retourne un 1 (on place 1 dans eax)
        movl    $1, %eax
END :
        #restore ebp and esp
        leave  
        #return to the caller 
        ret