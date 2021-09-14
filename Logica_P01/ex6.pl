%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%         
%                 ex6.pl                     %
% Faz a uniao de duas listas com o predicado %
% uniao(L1, L2, LUNIAO).                     %
%                                            %
% Author: Thiago De Azevedo Cavendish        %
%                                            %
% Contato: tac@poli.br                       %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Faz a uniao de duas listas

uniao(L1, L2, LUNIAO) :-
     union(L1, L2, LUNIAO).

