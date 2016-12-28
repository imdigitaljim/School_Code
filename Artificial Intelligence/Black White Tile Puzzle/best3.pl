% This is identical to best1, except a nontrivial definition is given for
% the heuristic predicate.

:- [adts].
test :-
	go(["black","black","black","B","white","white","white"], ["white","white","white","B","black","black","black"]).

%initial conditions	
move([X,A,B,C,D,E,F], [A,X,B,C,D,E,F]) :- X == "B".
move([X,A,B,C,D,E,F], [B,A,X,C,D,E,F]) :- X == "B".

move([A,X,B,C,D,E,F], [X,A,B,C,D,E,F]) :- X == "B".
move([A,X,B,C,D,E,F], [A,B,X,C,D,E,F]) :- X == "B".
move([A,X,B,C,D,E,F], [A,C,B,X,D,E,F]) :- X == "B".

move([A,B,X,C,D,E,F], [A,X,B,C,D,E,F]) :- X == "B".
move([A,B,X,C,D,E,F], [X,B,A,C,D,E,F]) :- X == "B".
move([A,B,X,C,D,E,F], [A,B,C,X,D,E,F]) :- X == "B".
move([A,B,X,C,D,E,F], [A,B,D,C,X,E,F]) :- X == "B".

move([A,B,C,X,D,E,F], [A,B,X,C,D,E,F]) :- X == "B".
move([A,B,C,X,D,E,F], [A,X,C,B,D,E,F]) :- X == "B".
move([A,B,C,X,D,E,F], [A,B,C,D,X,E,F]) :- X == "B".
move([A,B,C,X,D,E,F], [A,B,C,E,D,X,F]) :- X == "B".

move([A,B,C,D,X,E,F], [A,B,C,D,E,X,F]) :- X == "B".
move([A,B,C,D,X,E,F], [A,B,C,D,F,E,X]) :- X == "B".
move([A,B,C,D,X,E,F], [A,B,C,X,D,E,F]) :- X == "B".
move([A,B,C,D,X,E,F], [A,B,X,D,C,E,F]) :- X == "B".

move([A,B,C,D,E,X,F], [A,B,C,D,X,E,F]) :- X == "B".
move([A,B,C,D,E,X,F], [A,B,C,X,E,D,F]) :- X == "B".
move([A,B,C,D,E,X,F], [A,B,C,D,E,F,X]) :- X == "B".

move([A,B,C,D,E,F,X], [A,B,C,D,E,X,F]) :- X == "B".
move([A,B,C,D,E,F,X], [A,B,C,D,X,F,E]) :- X == "B".

%unsafe(0).

% In predicate heuristic(State,Goal,Value), Value is to be calculated as the
% estimated distance from the State to the Goal, e.g., in the 8-puzzle this
% might be the number of tiles out of place in State compared with Goal.  

heuristic(X,Y,V):- count_outofplace(X,Y,0,V).
count_outofplace([H1|T1], [H2|T2], C, V) :- H1 \= H2, NextC is C + 1, count_outofplace(T1, T2, NextC, V).
count_outofplace([H1|T1], [H2|T2], C, V) :- H1 == H2, count_outofplace(T1, T2, C, V). 
count_outofplace([], _, Count, Count).


% The precedes predicate is needed for the priorty-queue code in the atds
% file.  The positions between the [ and ] represent State, Parent (of State),
% Depth (from of State from root), Heuristic (value for State),
% Depth+Heurstic (the value of the evaluation function f(n)=g(n)+h(n)).

precedes([_,_,_,_,F1], [_,_,_,_,F2]) :- F1 =< F2.

%%%%%%% Best first search algorithm%%%%%%%%%

	% go initializes Open and CLosed and calls path	

go(Start, Goal) :- 
	empty_set(Closed_set),
	empty_pq(Open),
	heuristic(Start, Goal, H),

	insert_pq([Start, nil, 0, H, H], Open, Open_pq),
	path(Open_pq, Closed_set, Goal).


	% Path performs a best first search,
	% maintaining Open as a priority queue, and Closed as
	% a set.
	
	% Open is empty; no solution found

path(Open_pq, _, _) :- 
	empty_pq(Open_pq),
	write('graph searched, no solution found').

	% The next record is a goal
	% Print out the list of visited states

path(Open_pq, Closed_set, Goal) :- 
	dequeue_pq([State, Parent, _, _, _], Open_pq, _),
	State = Goal,
	write('Solution path is: '), nl,
	printsolution([State, Parent, _, _, _], Closed_set).
	
	% The next record is not equal to the goal
	% Generate its children, add to open and continue

path(Open_pq, Closed_set, Goal) :- 
	dequeue_pq([State, Parent, D, H, S], Open_pq, Rest_of_open_pq),
        get_children([State, Parent, D, H, S], Rest_of_open_pq, Closed_set,
             Children, Goal),
	insert_list_pq(Children, Rest_of_open_pq, New_open_pq),
	union([[State, Parent, D, H, S]], Closed_set, New_closed_set),
	path(New_open_pq, New_closed_set, Goal),!.

get_children([State, _, D, _, _], Rest_of_open_pq, Closed_set, Children, 
             Goal) :-
        bagof(Child, moves([State, _, D, _, _], Rest_of_open_pq,
             Closed_set, Child, Goal), Children);
        empty_set(Children).

	% moves generates all children of a state that are not already on
	% open or closed.  For each child, it adds 1 to the current depth D
	% calculates the heuristic H for the child, as well as the sum S of
	% these two values (i.e., calculation of f(n)=g(n)+h(n)).

	% Also, unsafe is commented out as we don't need it here.

moves([State, _, Depth, _, _], Rest_of_open_pq, Closed_set, 
             [Next, State, New_D, H, S], Goal) :-
	move(State, Next),
%	not(unsafe(Next)),
	not(member_pq([Next, _, _, _, _], Rest_of_open_pq)),
	not(member_set([Next, _, _, _, _], Closed_set)),
	New_D is Depth + 1,
	heuristic(Next, Goal, H),
	write('out of place count: '),
	write(H), nl,
	S is New_D + H.

	% Printsolution prints out the solution path by tracing
	% back through the states on closed using parent links.

printsolution([State, nil, _, _, _], _):-  
	write(State), nl.
printsolution([State, Parent, _, _, _], Closed_set) :-
	member_set([Parent, Grandparent, _, _, _], Closed_set),
	printsolution([Parent, Grandparent, _, _, _], Closed_set),
	write(State), nl.
