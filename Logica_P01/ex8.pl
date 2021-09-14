%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%         
%                       ex8.pl                         %
%        Dado um numero, retorna o seu fatorial        %
%                                                      %
% Author: Thiago De Azevedo Cavendish                  %
%                                                      %
% Contato: tac@poli.br                                 %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Define que o fatorial de 0 eh 1
f(0,1).

%Calcula o fatorial de um numero, se o numero for > 0   
f(N,R) :-
    N > 0,
    M is N - 1,
    f(M,S),
    R is N * S,
    !.

