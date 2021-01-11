.global func_s

func_s:
	flds b 		#met b sur la pile a s[0]
	flds e 		#met e sur la pile a s[0] et b va sur la pos [1]
	fmulp 		#e * b (position s[0])
	flds g 		#met g sur la pile a s[0] alors e * b va sur s[1]
	faddp 		#(e * b) + g (position s[0]) 
	flds d 		#met d sur la pile a s[0] et la ligne 8 va sur s[1]
	fdivrp 		#((e * b) + g) / d) (va a la position s[0])
	flds g      #met g sur la pile a s[0] donc, la ligne 10 va sur s[1]
	flds f 		#met f sur la pile a s[0],g va sur s[1] et la ligne 10 va sur s[2]
	fsubrp		#(g-f) sur s[0] et la ligne 10 va sur s[1]
	fmulp		#((e * b) + g) / d)*(g-f) sur s[0]
	flds d 		#met d sur la pile a s[0] et la ligne 16 sur s[1]
	flds e 		#met e sur la pile a s[0], d sur s[1] et la ligne 16 sur s[2]
	faddp 		#(d+e) sur s[0] et la ligne 16 sur s[1]
	fdivrp		#(((e * b) + g) / d)*(g-f))/(d+e) sur s[0]
	fstps a	
	ret
