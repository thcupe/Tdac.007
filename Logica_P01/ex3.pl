%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                 ex3.pl                    %
%      Soma dos elementos de uma lista      %
%                                           %
% Author: Thiago De Azevedo Cavendish       %
%                                           %
% Contato: tac@poli.br                      %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Obs: [ ] indica que eh uma lista
%Criterio de parada
%A soma de uma lista vazia sempre eh zero
somalista([], 0).

%Soma uma lista nao vazia
%Recebe a lista L e retorna o resultado R

% Obs: H = Head  % T = Tails

somalista([H|T], R) :-
     somalista(T, ST),
     R is H+ST.   % obs: is significa =
         
