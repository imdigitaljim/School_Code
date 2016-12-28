% This is obtained from depth1 by modifying the moves predicate to include a
% variable Depth which can be used to define a bound.  This is done with the
% line "Depth < ?" where ? is a numeric bound. 

%2 8 3
%1 6 4
%7   5

test :-
	go([2,8,3,1,6,4,7,0,5], [1,2,3,8,0,4,7,6,5]).

:- [adts].

move([A,B,C,D,E,F,G,H,I],[B,A,C,D,E,F,G,H,I]) :- A == 0.
move([A,C,D,B,E,F,G,H,I],[B,C,D,A,E,F,G,H,I]) :- A == 0.
move([B,A,C,D,E,F,G,H,I],[A,B,C,D,E,F,G,H,I]) :- A == 0.
move([C,A,B,D,E,F,G,H,I],[C,B,A,D,E,F,G,H,I]) :- A == 0.
move([C,A,D,E,B,F,G,H,I],[C,B,D,E,A,F,G,H,I]) :- A == 0.
move([C,B,A,D,E,F,G,H,I],[C,A,B,D,E,F,G,H,I]) :- A == 0.
move([C,D,A,E,F,B,G,H,I],[C,D,B,E,F,A,G,H,I]) :- A == 0.
move([B,C,D,A,E,F,G,H,I],[A,C,D,B,E,F,G,H,I]) :- A == 0.
move([C,D,E,A,B,F,G,H,I],[C,D,E,B,A,F,G,H,I]) :- A == 0.
move([C,D,E,A,F,G,B,H,I],[C,D,E,B,F,G,A,H,I]) :- A == 0.
move([C,B,D,E,A,F,G,H,I],[C,A,D,E,B,F,G,H,I]) :- A == 0.
move([C,D,E,B,A,F,G,H,I],[C,D,E,A,B,F,G,H,I]) :- A == 0.
move([C,D,E,F,A,B,G,H,I],[C,D,E,F,B,A,G,H,I]) :- A == 0.
move([C,D,E,F,A,G,H,B,I],[C,D,E,F,B,G,H,A,I]) :- A == 0.
move([C,D,B,E,F,A,G,H,I],[C,D,A,E,F,B,G,H,I]) :- A == 0.
move([C,D,E,F,B,A,G,H,I],[C,D,E,F,A,B,G,H,I]) :- A == 0.
move([C,D,E,F,G,A,H,I,B],[C,D,E,F,G,B,H,I,A]) :- A == 0.
move([C,D,E,B,F,G,A,H,I],[C,D,E,A,F,G,B,H,I]) :- A == 0.
move([C,D,E,F,G,H,A,B,I],[C,D,E,F,G,H,B,A,I]) :- A == 0.
move([C,D,E,F,G,H,B,A,I],[C,D,E,F,G,H,A,B,I]) :- A == 0.
move([C,D,E,F,G,H,I,A,B],[C,D,E,F,G,H,I,B,A]) :- A == 0.
move([C,D,E,F,B,G,H,A,I],[C,D,E,F,A,G,H,B,I]) :- A == 0.
move([C,D,E,F,G,B,H,I,A],[C,D,E,F,G,A,H,I,B]) :- A == 0.
move([C,D,E,F,G,H,I,B,A],[C,D,E,F,G,H,I,A,B]) :- A == 0.
%unsafe(0).

%%%%% Depth first path "shell" algorithm modified to do bounded search %%%%%%%

go(Start, Goal) :-
	empty_stack(Empty_open),
	stack([Start,nil, 0], Empty_open, Open_stack),
        empty_stack(Closed_set),
	path(Open_stack, Closed_set, Goal).
	
path(Open_stack,_,_) :-
	empty_stack(Open_stack),
        write('No solution found with these rules').
	
path(Open_stack, Closed_set, Goal) :-
        stack([State, Parent, Depth], _, Open_stack), State = Goal,
        write('A Solution is Found!'), nl,
        printsolution([State, Parent, Depth], Closed_set).

path(Open_stack, Closed_set, Goal) :-
        stack([State, Parent, Depth], Rest_open_stack, Open_stack), 
        get_children(State, Depth, Rest_open_stack, Closed_set, Children),
        add_list_to_stack(Children, Rest_open_stack, New_open_stack),
        union([[State,Parent, Depth]], Closed_set, New_closed_set),
        path(New_open_stack, New_closed_set, Goal), !.

get_children(State, Depth, Rest_open_stack, Closed_set, Children):-
        bagof(Child, moves(State, Depth, Rest_open_stack, 
            Closed_set, Child), Children);
	empty_set(Children).

moves(State, Depth, Rest_open_stack, Closed_set, [Next, State, New_Depth]):-
        Depth < 5,
        move(State, Next),
%        not(unsafe(Next)),
        not(member_stack([Next, _, _], Rest_open_stack)),
        not(member_set([Next, _, _], Closed_set)),
        New_Depth is Depth + 1.

printsolution([State, nil, Depth], _) :-
        write(State), write(' '), write(Depth), nl.

printsolution([State, Parent, Depth], Closed_set) :-
        member_set([Parent, Grandparent, Next_Depth], Closed_set),
        printsolution([Parent, Grandparent, Next_Depth], Closed_set),
        write(State), write(' '), write(Depth), nl.
