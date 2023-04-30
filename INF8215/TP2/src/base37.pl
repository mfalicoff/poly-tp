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