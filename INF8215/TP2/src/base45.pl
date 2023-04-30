mot(abalone).
mot(abandon).
mot(enhance).
mot(anagram).
mot(connect).
mot(elegant).

crossword(V1,V2,V3,H1,H2,H3) :- mot(V1),mot(V2),mot(V3),mot(H1),mot(H2),mot(H3),atom_chars(V1, V1S),atom_chars(V2, V2S),atom_chars(V3, V3S),atom_chars(H1, H1S),atom_chars(H2, H2S),atom_chars(H3, H3S),nth0(1, V1S, A1),nth0(1, H1S, A2),nth0(1, V2S, B1),nth0(3, H1S, B2),nth0(1, V3S, C1),nth0(5, H1S, C2),nth0(3, V1S, D1),nth0(1, H2S, D2),nth0(3, V2S, E1),nth0(3, H2S, E2),nth0(3, V3S, F1),nth0(5, H2S, F2),nth0(5, V1S, G1),nth0(1, H3S, G2),nth0(5, V2S, H11),nth0(3, H3S, H22),nth0(5, V3S, I1),nth0(5, H3S, I2),A1==A2,B1==B2,C1==C2,D1==D2,E1==E2,F1==F2,G1==G2,H11==H22,I1==I2.
%test(Word,List,Terme) :- atom_chars(word, List), nth0(3, List, Terme).
