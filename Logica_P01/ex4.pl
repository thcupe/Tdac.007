%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%         
%                  ex4.pl                    %
%       Dadas duas listas, retorna a soma    %
% , 2 a 2, em uma lista resposta             %
%                                            %
% Author: Thiago De Azevedo Cavendish        %
%                                            %
% Contato: tac@poli.br                       %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% obs: [ ] indica que eh uma lista

list_sum([], [], [] ) .
list_sum([H1|T1], [H2|T2], [X|L3]) :-
     list_sum(T1, T2, L3), 
     X is H1+H2 .  % obs: is significa =

