% Declare dynamic predicates to allow modification at runtime
:- dynamic eats/2, not_killed/1.

% Suppress warnings for discontiguous predicates
:- discontiguous eats/2, likes/2.

% Facts:
likes(john, food).
food(apple).
food(vegetable).
food(Y) :- eats(X,Y), alive(X).  % Modified to use eats/2 with two arguments

% Additional Facts:
eats(anil, peanuts).
alive(anil).

% Rules:
eats(john, Y) :- eats(anil, Y).
likes(john, Y) :- food(Y).

% Prove: likes(john, peanuts).
