max2(X,Y,Z) :- (Z is X, Z>=Y);(Z is Y, Z>=X).
max([X],X).
max([H|T],S) :- max(T,S1),max2(H,S1,S).


somme([X],X).
somme([H|T],S) :- somme(T,S1),S is S1+H.

nth(0,[H|_],H).
nth(N,[_|T],R) :- N1 is N-1,nth(N1,T,R).

zip([X],[Y],[[X,Y]]).
zip([H1|T1],[H2|T2],R) :- zip(T1,T2,R1),append([[H1,H2]],R1 , R).

enumerate(1,[0]).
enumerate(N,L) :- N1 is N-1, enumerate(N1,L1), append(L1,[N1],L).

rend_monnaie(Argent,Prix) :- R is floor((Argent-Prix)*100), rend_piece2(R).

rend_piece2(R) :-  R1 is mod(R,200),D1 is div(R,200), write(D1),write(" piece de 2"),nl,rend_piece1(R1).

rend_piece1(R) :-  R1 is mod(R,100),D1 is div(R,100), write(D1),write(" piece de 1"),nl, rend_piece25(R1), nl.

rend_piece25(R) :- R1 is mod(R,25),D1 is div(R,25), write(D1),write(" piece de 0.25"),nl, rend_piece10(R1).

rend_piece10(R) :- R1 is mod(R,10),D1 is div(R,10), write(D1),write(" piece de 0.1"),nl, rend_piece5(R1).

rend_piece5(R) :- D1 is div(R,5), R1 is mod(R,5), function5(R1,P), A is D1+P, write(A),write(" piece de 0.05").

function5(C,P) :- C==0,P is 0 ; C==1,P is 0; C==2, P is 0;C==3 , P is 1; C== 4, P is 1.


