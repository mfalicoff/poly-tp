% Matricules
% Maximiliano Falicoff 2013658
% Julien Savoldelli 2229682

% Exercice 3.7
homme(hugo).
homme(loic).
homme(gabriel).
homme(maxime).
homme(mathieu).
homme(alexis).

femme(catherine).
femme(justine).
femme(lea).
femme(alice).
femme(rose).
femme(emma).

parent(hugo,lea).
parent(hugo,gabriel).
parent(catherine,lea).
parent(catherine,gabriel).

parent(loic,alice).
parent(loic,maxime).
parent(loic,mathieu).
parent(justine,alice).
parent(justine,maxime).
parent(justine,mathieu).

parent(gabriel,alexis).
parent(gabriel,rose).
parent(gabriel,emma).
parent(alice,alexis).
parent(alice,rose).
parent(alice,emma).

enfant(X,Y) :- parent(Y,X).
fille(X,Y) :- femme(X),enfant(X,Y).
fils(X,Y) :- homme(X),enfant(X,Y).
mere(X,Y) :- femme(X),parent(X,Y).
pere(X,Y) :- homme(X),parent(X,Y).
frere(X,Y) :- homme(X), mere(Z,X), mere(Z,Y), X\=Y.
soeur(X,Y) :- femme(X), mere(Z,X), mere(Z,Y), X\=Y.
oncle(X,Y) :- parent(Z,Y), frere(X,Z).
tante(X,Y) :- parent(Z,Y), soeur(X,Z).
grand_parent(X,Y) :- parent(Z,Y), parent(X,Z).
grand_pere(X,Y) :- grand_parent(X,Y), homme(X).
grand_mere(X,Y) :- grand_parent(X,Y), femme(X).
petit_enfants(X,Y) :- grand_parent(Y,X).
petit_fils(X,Y) :-petit_enfants(X,Y), homme(X).
petit_fille(X,Y) :-petit_enfants(X,Y), femme(X).

% Exercice 4.3
sum(X,Y,R) :- R is (X+Y).
max2(X,Y,Z) :- (Z is X, Z>=Y);(Z is Y, Z>=X).
max3(X,Y,Z,M) :- max2(X,Y,N), max2(Z,N,M).

% Exercice 4.5

mot(abalone).
mot(abandon).
mot(enhance).
mot(anagram).
mot(connect).
mot(elegant).

crossword(V1,V2,V3,H1,H2,H3) :- mot(V1),mot(V2),mot(V3),mot(H1),mot(H2),mot(H3),atom_chars(V1, V1S),atom_chars(V2, V2S),atom_chars(V3, V3S),atom_chars(H1, H1S),atom_chars(H2, H2S),atom_chars(H3, H3S),nth0(1, V1S, A1),nth0(1, H1S, A2),nth0(1, V2S, B1),nth0(3, H1S, B2),nth0(1, V3S, C1),nth0(5, H1S, C2),nth0(3, V1S, D1),nth0(1, H2S, D2),nth0(3, V2S, E1),nth0(3, H2S, E2),nth0(3, V3S, F1),nth0(5, H2S, F2),nth0(5, V1S, G1),nth0(1, H3S, G2),nth0(5, V2S, H11),nth0(3, H3S, H22),nth0(5, V3S, I1),nth0(5, H3S, I2),A1==A2,B1==B2,C1==C2,D1==D2,E1==E2,F1==F2,G1==G2,H11==H22,I1==I2.

% Exercice 4.7

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

% Bonus
rend_monnaie(Argent,Prix) :- R is floor((Argent-Prix)*100), rend_piece2(R).

rend_piece2(R) :-  R1 is mod(R,200),D1 is div(R,200), write(D1),write(" piece de 2"),nl,rend_piece1(R1).

rend_piece1(R) :-  R1 is mod(R,100),D1 is div(R,100), write(D1),write(" piece de 1"),nl, rend_piece25(R1), nl.

rend_piece25(R) :- R1 is mod(R,25),D1 is div(R,25), write(D1),write(" piece de 0.25"),nl, rend_piece10(R1).

rend_piece10(R) :- R1 is mod(R,10),D1 is div(R,10), write(D1),write(" piece de 0.1"),nl, rend_piece5(R1).

rend_piece5(R) :- D1 is div(R,5), R1 is mod(R,5), function5(R1,P), A is D1+P, write(A),write(" piece de 0.05").

function5(C,P) :- C==0,P is 0 ; C==1,P is 0; C==2, P is 0;C==3 , P is 1; C== 4, P is 1.

