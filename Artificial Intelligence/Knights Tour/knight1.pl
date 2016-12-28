knight(MoveCount, _, _, _) :- MoveCount == 64.
 
knight(N, Line, Col, L) :-
	Line >= 0, Col >= 0, Line < 8, Col < 8,
	Position is Line * 8 + Col,	
	NextN is N+1,
	nth0(Position, L, NextN),
	%sets of moves
	LineM1 is Line - 1, LineM2 is Line - 2, LineP1 is Line + 1, LineP2 is Line + 2,
	ColM1 is Col - 1, ColM2 is Col - 2, ColP1 is Col + 1, ColP2 is Col + 2,
	maplist(find_best_move(L),
		[(LineP1, ColM2), (LineP2, ColM1), (LineP2, ColP1),(LineP1, ColP2),
		 (LineM1, ColM2), (LineM2, ColM1), (LineM2, ColP1),(LineM1, ColP2)],
		R),
	sort(R, RS),
	pairs_values(RS, Moves),
	move(NextN, Moves, L).
 
move(NextN, [(Line, Col) | R], L) :-
	knight(NextN, Line, Col, L);
	move(NextN, R, L).
 
find_best_move(_L, (Line, Col), 999-(Line, Col)) :-
	(   Line < 0 ; Col < 0; Line >= 8; Col >= 8), !.
 
find_best_move(L, (Line, Col), 999-(Line, Col)) :-
	Position is Line * 8 + Col,
	nth0(Position, L, V),
	\+var(V), !.

find_best_move(L, (Line, Col), R-(Line, Col)) :-
	LineM1 is Line - 1, LineM2 is Line - 2, LineP1 is Line + 1, LineP2 is Line + 2,
	ColM1 is Col - 1, ColM2 is Col - 2, ColP1 is Col + 1, ColP2 is Col + 2,
	include(possible_move(L),
		[(LineP1, ColM2), (LineP2, ColM1), (LineP2, ColP1),(LineP1, ColP2),
		 (LineM1, ColM2), (LineM2, ColM1), (LineM2, ColP1),(LineM1, ColP2)], Res),
	length(Res, Len),
	R = Len.
 
possible_move(L, (Line, Col)) :-
	Line >= 0, Col >= 0, Line < 8, Col < 8,
	Position is Line * 8 + Col,
	nth0(Position, L, V),
	var(V).
  
printTour(_, _, []).
printTour(N, N, L) :-
	nl, printTour(N, 0, L).
 
printTour(N, M, [H | T]) :-
	writef('%3r', [H]),
	NextM is M + 1,
	printTour(N, NextM, T).
  
test:-
	%run the knight simulation
	%knight(currentmove, currenty, currentx, list)
	knight(0, 0, 0, L),
	printTour(8, 0, L).
