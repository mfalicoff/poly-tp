.data
	/* Votre programme assembleur ici... */
	i:
		.int 0

.global func_s

func_s:	
	/* commande a faire : gcc -m32 -gdwarf-2 -o tp2_2 tp2_2.c tp2_2.s */
	boucle:
			mov b, %eax
			add c, %eax
			sub d, %eax
			mov %eax, a
			if:
				mov c, %eax
				add $1000, %eax
				mov e, %ebx
				sub $500, %ebx
				cmp %eax, %ebx
				jge else
				subl $300, e
				if2:
					mov c, %eax
					cmp b, %eax
					jge endif2
					addl $300, c
				endif2:
				jmp endif
			else:
				mov c, %eax
				sub %eax, d
				subl $300, b
			endif:
		continue:
			addl $1, i 
			cmpl $10, i
			jng boucle
		break:
	ret
