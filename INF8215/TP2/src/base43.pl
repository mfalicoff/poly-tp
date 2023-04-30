sum(X,Y,R) :- R is (X+Y).
max2(X,Y,Z) :- (Z is X, Z>=Y);(Z is Y, Z>=X).
max3(X,Y,Z,M) :- max2(X,Y,N), max2(Z,N,M).