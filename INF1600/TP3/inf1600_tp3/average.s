.global matrix_row_aver_asm

matrix_row_aver_asm:
        pushl   %ebp
        movl    %esp, %ebp


        subl    $16, %esp       #allocation d'espace pour les variables locales
        movl    $0, -4(%ebp)    #on met 0 dans r
FOR1:
        movl    -4(%ebp), %eax  
        cmpl    16(%ebp), %eax  #on compare r avec matorder
        jge     FIN             #Si eax plus grand, jump a la fin
        movl    $0, -12(%ebp)   #mettre 0 dans elemt
        movl    $0, -8(%ebp)    #mettre 0 dans ebp
FOR2:
        movl    -8(%ebp), %eax  # met c dans eax
        cmpl    16(%ebp), %eax  #compare eax avec matorder
        jge     DIV              #Si eax plus grand, sauter fin boucle for
        movl    -4(%ebp), %eax  #On met r dans eax
        imull   16(%ebp), %eax  # multiplication r*matorder
        movl    %eax, %edx      # met resultat dans edx
        movl    -8(%ebp), %eax
        addl    %edx, %eax      #on fait c+edx
        leal    0(,%eax,4), %edx    #on utilise ici leal car cela prend l'adresse de eax et non sa valeur
        movl    8(%ebp), %eax       #On prend l'adresse du premier leemnt du tableau dans eax
        addl    %edx, %eax          #On additione edx et eax pour avoir le bon index de inmatdata[c+r*matorder]
        movl    (%eax), %eax        #On met la valueur de cette adresse dans eax
        addl    %eax, -12(%ebp)     #on fait +=
        incl    -8(%ebp)            #on increment c
        jmp     FOR2                  #on recomemnce la boucle
DIV:
        movl    -4(%ebp), %eax      #met r dans eax
        leal    0(,%eax,4), %edx    #met addr de r dans edx
        movl    12(%ebp), %eax      #outmatdata dans eax
        leal    (%edx,%eax), %ecx   #addr de outmatdata[r] dans ecx
        movl    -12(%ebp), %eax     #elem dans eax
        movl    %eax, %edx          
        sarl    $31, %edx           #met du padding pour la division
        idivl   16(%ebp)            #divise elem par matorder
        movl    %eax, (%ecx)        #met le resulat dans adresse de ecx ce qui equivaut a outmatdata[r]
        incl    -4(%ebp)            #incremente r
        jmp     FOR1                  #jmp boulce for1
FIN:
        mov   %ebp, %esp     
        pop   %ebp                    
        ret