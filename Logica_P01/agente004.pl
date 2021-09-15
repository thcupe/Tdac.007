%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%    Hunt The Wumpus - World Simulator                                          %
%    Copyright (C) 2012 - 2016  Ruben Carlo Benante <rcb at beco dot cc>        %
%                                                                               %
%    This program is free software; you can redistribute it and/or modify       %
%    it under the terms of the GNU General Public License as published by       %
%    the Free Software Foundation; version 2 of the License.                    %
%                                                                               %
%    This program is distributed in the hope that it will be useful,            %
%    but WITHOUT ANY WARRANTY; without even the implied warranty of             %
%    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              %
%    GNU General Public License for more details.                               %
%                                                                               %
%    You should have received a copy of the GNU General Public License along    %
%    with this program; if not, write to the Free Software Foundation, Inc.,    %
%    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.                %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%   Special thanks to:
%     - Gregory Yob
%     - Larry Holder
%     - Walter Nauber
%
% A Prolog implementation of the Wumpus world invented by Gregory Yob (1972)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% To allow an agent to run with the Wumpus Simulator you need to define:
%   init_agent :
%       It will be called only once, at the start. Put here definitions and
%       other start code you need (asserts, retracts, and so on)
%   run_agent :
%       It will be called each turn by the simulator.
%       Input: perceptions from the world.
%       Expected output: an action for the agent to perform.
%   world_setup([Size, Type, Move, Gold, Pit, Bat, [RandS, RandA]]):
%       This is a fact. It will be consulted only once at the beginning,
%       even before init_agent. It will configure the world as you say,
%       or use a default in case of conflicts or mistakes.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Lista de Percepcao: [Stench, Breeze, Glitter, Bump, Scream, Rustle]
% Traducao: [Fedor, Vento, Brilho, Trombada, Grito, Ruido]
% Acoes possiveis (abreviacoes):
% goforward (go)                - andar
% turnright (turn, turnr ou tr) - girar sentido horario
% turnleft (turnl ou tl)        - girar sentido anti-horario
% grab (gr)                     - pegar o ouro
% climb (cl)                    - sair da caverna
% shoot (sh)                    - atirar a flecha
% sit (si)                      - sentar (nao faz nada, passa a vez)
%
% Costs (Custos):
% Actions: -1 (Andar/Girar/Pegar/Sair/Atirar/Sentar)
% Die: -1000 (morrer no buraco, wumpus ou de fadiga)
% Killing the Wumpus: +1000 (matar Wumpus)
% Climbing alive with golds: +500 for each gold (sair com ouro)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% To run the example, start PROLOG with (rode o exemplo iniciando o prolog com):
% swipl -s agenteXXX.pl
% then do the query (faca a consulta):
% ?- start.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% world_setup([Size, Type, Move, Gold, Pit, Bat, Adv])
%
% Size and Type: - fig62, 4
%                - grid, [2-9] (default 4)
%                - dodeca, 20
%       +--------+-----------+
%       |  Type  |    Size   |
%       +--------+-----------+
%       | fig62  | 4 (fixed) |
%       | grid   | 2 ... 9   |
%       | dodeca | 20 (fixed)|
%       +--------+-----------+
%
% Configuration:
%    1.   Size: 0,2..9,20, where: grid is [2-9] or 0 for random, dodeca is 20, fig62 is 4.
%    2.   Type: fig62, grid or dodeca
%    3.   Move: stander, walker, runner (wumpus movement)
%    4.   Gold: Integer is deterministic number, float from 0.0<G<1.0 is probabilistic
%    5.   Pits: Idem, 0 is no pits.
%    6.   Bats: Idem, 0 is no bats.
%    7.   Adv: a list with advanced configuration in the form [RandS, RandA]:
%       - RandS - yes or no, random agent start position
%       - RandA - yes or no, random agent start angle of orientation
%
% examples:
% * default:
%      world_setup([4, grid, stander, 0.1, 0.2, 0.1, [no, no]]).
% * size 5, 1 gold, 3 pits, some bats prob. 0.1, agent randomly positioned
%      world_setup([5, grid, stander, 1, 3, 0.1, [yes]]).
%
%   Types of Wumpus Movement
%       walker    : original: moves when it hears a shoot, or you enter its cave
%       runner    : go forward and turn left or right on bumps, maybe on pits
%       wanderer  : arbitrarily choses an action from [sit,turnleft,turnright,goforward]
%       spinner   : goforward, turnright, repeat.
%       hoarder   : go to one of the golds and sit
%       spelunker : go to a pit and sit
%       stander   : do not move (default)
%       trapper   : goes hunting agent as soon as it leaves [1,1]; goes home otherwise
%       bulldozer : hunt the agent as soon as it smells him
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% agente007.pl:
%
% Strategy: goes only forward, do not turn, do not grab gold, do not come back
%  Performance: it does not go very well as you can imagine
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

:- use_module(wumpus, [start/0]). % agente usa modulo simulador

% Versao 1.0
% Mundo:
%    Tamanho (size) 5x5, quadrado (grid)
%    Wumpus nao anda
%    5% de chance de ouro por casa, 4 buracos e 1 morcego
%    agente inicia na casa [1,1], orientado para direita (0 graus)
%    Maximo de acoes antes de morrer de fome: Size^2x4 = 5x5x4 = 100 (media de 4 acoes por casa)
%
world_setup([4, fig62, stander, 0.05, 4, 1, [no, no]]).
%world_setup([Tamanho, Tipo, Move, Ouro, Poço, Morcego, Adv])

% Versao 2.0
% Mundo:
%    Tamanho (size) 20 casas, formato dodecaedro
%    Wumpus anda quando escuta flecha ou quando o agente entra em sua casa
%    5% de chance de ouro por casa, 3 buracos e 1 morcego
%    agente inicia na casa [1,1], orientado para direita (0 graus)
%    Maximo de acoes antes de morrer de fome: 100 (media de 5 acoes por casa)
%
%world_setup([20, dodeca, walker, 0.05, 3, 1, [no, no]]).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% Inicie aqui seu programa.

/* Conjunto dinamico para declarar o predicado */
:- dynamic ([
    arrows_owned/1,
    objective/1,
    visited/1,
    bat_locations/1,
    nobat_locations/1,
    pit_locations/1,
    nopit_locations/1,
    wumpus_locations/1,
    nowumpus_locations/1,
    current_location/1,
    last_location/1,
    orientation/1,
    last_action/1,
    nactions/1,  %numero de acoes
    destination/1,
    route/1,
    wumpusdead/0
  ]).

/*Para poder comecar o programa*/
init_agent :-
    retractall(visited(_)),
    assert(visited([[1,1]])),

    retractall(bat_locations(_)),
    assert(bat_locations([])),
    retractall(nobat_locations(_)),
    assert(nobat_locations([[1,1]])),

    retractall(pit_locations(_)),
    assert(pit_locations([])),
    retractall(nopit_locations(_)),
    assert(nopit_locations([[1,1]])),

    retractall(wumpus_locations(_)),
    assert(wumpus_locations([])),
    retractall(nowumpus_locations(_)),
    assert(nowumpus_locations([[1,1]])),

    retractall(destination(_)),
    assert(destination([1,1])),

    retractall(nactions(_)),
    assert(nactions(0)),
    retractall(arrows_owned(_)),
    assert(arrows_owned(1)),
    retractall(objective(_)),
    retractall(last_action(_)),
    retractall(wumpusdead).

%Funcao para a definicao da posicao
%Quando o GPS for solicitado, sera definida a posicao
%Precisa ser definida imediatamente

%run_agent(Percepcao, Acao)
%run_agent recebe as Percepcoes ([Fedor do wumpus, Vento ou brisa do buraco, Brilho do ouro, Trombada ou batida na parede, Grito da morte do Wumpus, Ruidos do morcego]), [[coordenadas X e Y], orientacao] e retorna uma acao para o simulador

run_agent([F,V,B,T,G,R,[[X,Y],O]],Acao) :-
    retractall(orientation(_)),
    assert(orientation(O)),
    retractall(current_location(_)),
    assert(current_location([X,Y])),
    retractall(last_location(_)),
    assert(last_location([])),

    bat_handler(R),
    pit_handler(V),
    wumpus_handler([F,V,B,T,G,R,[]]), %Para possiveis perigos
    maybeleave,
    runactions([F,V,B,no,G,R,[]],Acao),
    info,
    memory_handler([F,V,B,T,R,[]],Acao).

%AGENTE REATIVO
run_agent(Percepcao, Acao) :-
    %sleep(1),
    %mapper,eh necessario que seja chamado antes das acoes
    premapper(Percepcao),
    %Wumpus precisa ser cuidado antes de ir embora
    wumpus_handler(Percepcao),
    maybeleave,
    runactions(Percepcao, Acao),
    info,
    memory_handler(Percepcao, Acao).

maybeleave :-
    nactions(N), %maximo de ações antes da morte
    N > 70,
    writeln('O agente está comecando a sentir fome. Melhor sair.'),
    retractall(objective(_)),
    assert(objective(leave)).
maybeleave.

%Mostra as informações obtidas do mundo para o agente (casas, buracos e Wumpus)
%Para a decisao do objetivo

info :- 
    nl, write('Processamento do Agente:'), nl,
    printobj,
    safe_locations(S),
    write('Casas seguras: '),
    write(S),nl,
    nosafe_locations(NS),
    write('Casas inseguras: '),
    write(NS),nl,
    visited(V),
    write('Casas visitadas: '),
    write(V),nl,
    current_location(C),
    write('Casa atual: '),
    write(C),nl,
    orientation(O),
    write('Orientacao: '),
    write(O),nl,
    bat_locations(B),
    write('Posicoes com Morcego: '),
    write(B),nl,
    nobat_locations(NB),
    write('Posicoes sem Morcego: '),
    write(NB),nl,
    pit_locations(P),
    write('Posicoes com Buraco: '),
    write(P),nl,
    nopit_locations(NP),
    write('Posicoes sem Buraco: '),
    write(NP),nl,
    wumpus_locations(W),
    write('Posicoes do Wumpus: '),
    write(W),nl,
    nowumpus_locations(NW),
    write('Posicoes sem Wumpus: '),
    write(NW),nl,
    nl.

%imprime o objetivo principal do jogo

printobj :-     
    write('Objetivo: '),
    objective(Obj),
    writeln(Obj).

printobj :-
    writeln('Explore all this world and discover its incredible hidden treasures !').

safe_locations(SLoc) :-
    nobat_locations(NBLoc),
    nopit_locations(NPLoc),
    nowumpus_locations(NWLoc),
    intersection(NBLoc,NPLoc,NBPLoc),
    intersection(NBPLoc,NWLoc,SLoc).

nosafe_locations(NLoc) :-
    bat_locations(BLoc),
    pit_locations(PLoc),
    wumpus_locations(WLoc),
    union(BLoc,PLoc,BPLoc),
    union(BPLoc,WLoc,NLoc).

%Predefinição do mapa, cuidando para ele NAO meter a cara na parede

premapper([_,V,_,no,_,R,_]) :-
    %Cuida da exploracao quando ele anda para frente e nao mete a cara na parede
    last_action(goforward),
    retractall(last_action(_)),
    step,
    bat_handler(R),
    pit_handler(V).

premapper(_) :-  %Cuida para que ele nao bata a cara na parede
    %Cuida da batida na parede
    last_action(goforward),
    retractall(last_action(_)).
premapper(_).

%Movimentacao do agente

step :-
    current_location(A),
    getstep(A,B),
    retractall(current_location(_)),
    assert(current_location(B)),

    retractall(last_location(_)),
    assert(last_location(A)),

    visited(Vlist),
    retractall(visited(_)),
    list_to_set([B|Vlist],[B|Visit]),
    assert(visited([B|Visit])).

%Definindo direcoes para os movimentos do agente(para frente, para tras, para a direita e para a esquerda)

getstep([X,Y],[X1,Y]) :-
    orientation(0),
    X1 is X + 1.

getstep([X,Y],[X1,Y]) :-
    orientation(180),
    X1 is X - 1.

getstep([X,Y],[X,Y1]) :-
    orientation(90),
    Y1 is Y + 1.

getstep([X,Y],[X,Y1]) :-
    orientation(270),
    Y1 is Y - 1.

%Movimentacao concluida, falta definir outras interacoes do agente com o Matrix / mundo

bat_handler(yes) :-
    bat_locations(BLoc),
    nobat_locations(NoBLoc),
    adjacent(Adj),

    union(BLoc,Adj,MidBLoc),
    subtract(MidBLoc,NoBLoc,NewBLoc),
    retractall(bat_locations(_)),
    assert(bat_locations(NewBLoc)).

bat_handler(no) :-
    nobat_locations(NoBLoc),
    adjacent(Adj),
    union(NoBLoc,Adj,NewNoBLoc),
    retractall(nobat_locations(_)),
    assert(nobat_locations(NewNoBLoc)),
    trysubb.

trysubb :-
    bat_locations(BLoc),
    not(BLoc = []),
    nobat_locations(NoBLoc),
    subtract(BLoc,NoBLoc,NewBLoc),
    retractall(bat_locations(_)),
    assert(bat_locations(NewBLoc)).
trysubb.

%Wumpus handler = cuida do Wumpus

pit_handler(yes):-
    pit_locations(PLoc),
    nopit_locations(NoPLoc),
    adjacent(Adj),

    union(PLoc,Adj,MidPLoc),
    subtract(MidPLoc,NoPLoc,NewPLoc),
    retractall(pit_locations(_)),
    assert(pit_locations(NewPLoc)).

pit_handler(no) :-
    nopit_locations(NoPLoc),
    adjacent(Adj),
    union(NoPLoc,Adj,NewNoPLoc),
    retractall(nopit_locations(_)),
    assert(nopit_locations(NewNoPLoc)),
    trysubp.

trysubp :-
    pit_locations(PLoc),
    not(PLoc=[]),
    nopit_locations(NoPLoc),
    subtract(PLoc,NoPLoc,NewPLoc),
    retractall(pit_locations(_)),
    assert(pit_locations(NewPLoc)).
trysubp.

wumpus_handler([_,_,_,_,yes,_,_]) :-
    retractall(objective(_)),
    %assert(objective(leave)),
    assert(wumpusdead),
    wumpus_locations(WLoc),
    retractall(wumpus_locations(_)),
    assert(wumpus_locations([])),

    nowumpus_locations(NWLoc),
    union(WLoc,NWLoc,NewNWLoc),
    retractall(nowumpus_locations(_)),
    assert(nowumpus_locations(NewNWLoc)),

    nl,writeln('O Wumpus morreu!').

%Se o Wumpus Nao estiver morto, Nao tente sair

wumpus_handler([yes|_]) :-
    %Parte do codigo com o primeiro encontro com o Wumpus
    not(wumpusdead),
    wumpus_locations([]),
    adjacent(Adj),
    nowumpus_locations(Nlist),
    subtract(Adj,Nlist,Wlist),
    retractall(wumpus_locations(_)),
    assert(wumpus_locations(Wlist)),
    maybekill(Wlist).

%Detonar com o Wumpus
wumpus_handler([yes|_]) :-
    not(wumpusdead),
    wumpus_locations(Wlist),
    adjacent(Adj),
    intersection(Wlist,Adj,NewW),
    nowumpus_locations(Nlist),
    subtract(NewW,Nlist,SubW),
    retractall(wumpus_locations(_)),
    assert(wumpus_locations(SubW)),
    maybekill(SubW).

wumpus_handler(_) :-
    adjacent(Adj),
    nowumpus_locations(Nlist),
    union(Nlist,Adj,NewN),
    retractall(nowumpus_locations(_)),
    assert(nowumpus_locations(NewN)),
    trysubw.

wumpus_handler(_).
 %Retira o nowumpus_locations de wumpus_locations 
 %Se ele NAO estiver vazio 

trysubw :-
    wumpus_locations(Wlist),
    not(Wlist=[]),
    nowumpus_locations(NotW),
    subtract(Wlist,NotW,SubW),
    retractall(wumpus_locations(_)),
    assert(wumpus_locations(SubW)),
    maybekill(SubW).
trysubw.

%Cuidador da memoria
memory_handler(_,goforward) :-
    assert(last_action(goforward)),
    fail.
memory_handler(_,turnleft) :-
    change_orient(left),
    fail.
memory_handler(_,turnright) :-
    change_orient(right),
    fail.
memory_handler(_,_) :-
    nactions(N),
    N1 is N + 1,
    retractall(nactions(_)),
    assert(nactions(N1)), !.

maybekill(Wlist) :-
    not(wumpusdead),
    not(arrows_owned(0)),
    length(Wlist,1),
    retractall(objective(_)),
    assert(objective(kill)).

maybekill(_).
%Regula a orientacao para eliminar o Wumpus

change_orient(right) :-
    orientation(0),!,
    retractall(orientation(_)),
    assert(orientation(270)).
change_orient(right) :-
    orientation(90),!,
    retractall(orientation(_)),
    assert(orientation(0)).
change_orient(right) :-
    orientation(180),!,
    retractall(orientation(_)),
    assert(orientation(90)).
change_orient(right) :-
    orientation(270),!,
    retractall(orientation(_)),
    assert(orientation(180)).
change_orient(left) :-
    orientation(270),!,
    retractall(orientation(_)),
    assert(orientation(0)).
change_orient(left) :-
    orientation(180),!,
    retractall(orientation(_)),
    assert(orientation(270)).
change_orient(left) :-
    orientation(90),!,
    retractall(orientation(_)),
    assert(orientation(180)).
change_orient(left) :-
    orientation(0),!,
    retractall(orientation(_)),
    assert(orientation(90)).

%Ele chama as acoes do reactive agent

runactions(Percepcao, Acao) :-
    reactive(Percepcao, Acao).

runactions(_,Acao) :-
    %Isso so eh chamado se adjacente ao Wumpus, at least for now muhahahaha…
    objective(kill),
    killit(Acao).

%runactions roda apenas no mapping
runactions(_,Acao) :-
walker(Acao).

/*Chama as acoes do Random agent */
%runactions(Percepcao, Acao) :-
%madman(Percepcao, Acao).

%Traduz o goforward de aim_cell para o  que realmente queremos
killit(shoot) :-
    writeln('Kill it!'),
    current_location(Loc),
    wumpus_locations([WLoc]),
    not(intersection(Loc,WLoc,[])),
    aim_cell((Loc,WLoc),goforward).
killit(Acao) :-
    current_location(Loc),
    wumpus_locations([WLoc]),
    not(intersection(Loc,WLoc,[])),
    aim_cell((Loc,WLoc),Acao).

killit(Acao) :-
    writeln('Processamento Trajetória Killit:'),
    current_location([X,Y]),
    wumpus_locations([[N,M]]),
    not(X=N),
    not(Y=M),
    set_destination([X,M]),
    destination(Dest),
    write('Destino: '),
    writeln(Dest),
    first_step(Dest,[X,Y]),
    route([Aim|Route]),
    write('Rota: '),
    writeln(Route),
    aim_cell(([X,Y],Aim),Acao),
    write('Acao Aim_cell: '),
    writeln(Acao).

killit(Acao) :-
    current_location([X,Y]),
    wumpus_locations([[N,M]]),
    not(X=N),
    not(Y=M),
    set_destination([N,Y]),
    destination(Dest),
    write('Destino: '),
    writeln(Dest),
    first_step(Dest,[X,Y]),
    route([Aim|Route]),
    write('Rota: '),
    writeln(Route),
    aim_cell(([X,Y],Aim),Acao),
    write('Acao Aim_cell: '),
    writeln(Acao).

     %killit finalizado

reactive([_,_,_,yes,_,_,_],gps).

/* Ideia para reagir ao fedor*/
%reactive([yes,_,_,_,_,_,_],shoot):-
%    arrows_owned(A),
%    not(A =:= 0),
%    retractall(arrows_owned(_)),
%    A1 is A - 1,
%    assert(arrows_owned(A1)).

/* Reagir ao brilho */
reactive([_,_,yes,_,_,_,_], grab).

%Ideia pra fazer o agente sobreviver um pouco mais
reactive([yes|_],shoot) :-
    arrows_owned(A),
    not(A<1),
    wumpus_locations([[2,1],[1,2]]),
    A1 is A - 1,
    retractall(arrows_owned(_)),
    assert(arrows_owned(A1)).

/* Reagir ao vento*/
%reactive([_, yes, _, _, _, _], turnleft).
%reactive([_, yes, _, _, _, _], turnright).
%reactive([_, yes, _, _, _, _], goforward).

/*Escalar quando voltar para a posicao (1,1) / Maneira de sair */
reactive(_, climb):-
    not(objective(kill)),
    safe_locations(L),
    visited(V),
    not(L=[[1,1]]),
    permutation(L,V),
    current_location([1,1]).
reactive(_,climb):-
    current_location([1,1]),
    objective(leave).

%Agente com cuidador de memoria

adjacent(Adj) :-
    current_location(C),
    adjleft(C,L),
    adjright(C,R),
    adjdown(C,D),
    adjup(C,U),
    delete([L,R,D,U],[],Adj),!.

adjleft([1,_],[]).
adjleft([X,Y],[X1,Y]) :-
    X1 is X - 1.

adjright([4,_],[]).
adjright([X,Y],[X1,Y]) :-
    X1 is X + 1.

adjdown([_,1],[]).
adjdown([X,Y],[X,Y1]) :-
    Y1 is Y - 1.

adjup([_,4],[]).
adjup([X,Y],[X,Y1]) :-
    Y1 is Y + 1.

%Agora falta o predicado Randomico
% madman(_, A):-
% random_member(A, [goforward, turnleft, turnright]).

walker(Acao) :-
    write('Processamento Walker:'), nl,
    init_search,
    destination(Dest),
    write('Destino: '),
    write(Dest),nl,
    current_location(Curr),
    first_step(Dest,Curr),
    route([Aim|Rlist]),
    write('Rota: '),
    delete([Aim|Rlist],Dest,Route),
    write(Route),nl,
    aim_cell((Curr,Aim),Acao),
    write('Acao aim_cell: '),
    write(Acao), nl.

%Procura por um lugar nao visitado e uma localizacao segura comecando da primeira posicao
%A busca acontece da esquerda para a direita e de baixo pra cima
init_search :-
    %current_location(Curr),
    %destination(Dest),
    %Curr = Dest,
    set_destination([1,1]). %Starts the search from pos[1,1

%init_search. %A busca por um novo destino so acontecera quando o agente chegar ao seu destino atual 

search([X,Y]) :-
    X < 4,
    NewX is X + 1,
    set_destination([NewX,Y]).

search([X,Y]) :-
    X = 4,
    Y < 4,
    NewY is Y + 1,
    set_destination([1,NewY]).

%Se o agente não encontrar um novo destino, ele será definido como pos [1,1] // Sair
search([X,Y]) :-
    X = 4,
    Y = 4,
    retractall(objective(_)),
    assert(objective(leave)),
    set_destination([1,1]).

set_destination([1,1]) :-
    objective(leave),
    retractall(destination(_)),
    assert(destination([1,1])).

set_destination(_) :-
    current_location([1,1]),
    nactions(N),
    N < 2,
    retractall(destination(_)),
    assert(destination([2,1])).

set_destination([X,Y]) :-
    safe_locations(SafeLoc),
    member([X,Y],SafeLoc),
    visited(Visi),
    not(member([X,Y],Visi)),
    retractall(destination(_)),
    assert(destination([X,Y])).

set_destination(P) :-
    search(P).

%Falta fazer um caminho de forma direta para o destino

%X e Y sao as coordenadas do destino / N e M sao as coordenadas iniciais
first_step(Dest,[1,1]) :-
    nactions(N),
    N < 2,
    retractall(route(_)),
    assert(route([Dest])).

first_step(A,A).

first_step(Dest,Curr) :-
    closestadj(Dest,Curr,Fstep),
    nosafe_locations(NSList),
    not(member(Fstep,NSList)),
    retractall(route(_)),
    assert(route([Fstep])),
    set_route(Dest,Fstep).

set_route(A,A).

set_route(A,B) :-
    closestadj(A,B,C),
    nosafe_locations(NSList),
    not(member(C,NSList)),

    current_location(Loc), %Localizacao atual
    %Acelera a pesquisa e evita duplicatas
    route(Rlist),
    not(member(Loc,Rlist)),
    not(member(C,Rlist)),
    retractall(route(_)),
    append(Rlist,[C],Nlist),
    assert(route(Nlist)),
    set_route(A,C).

%Falta continuar o caminho ate o destino

closestadj([X,Y],[N,Y],[N1,Y]) :-
    X > N,
    N < 4,
    N1 is N + 1.

closestadj([X,Y],[N,Y],[N1,Y]) :-
    X < N,
    N > 1,
    N1 is N - 1.

closestadj([X,Y],[X,M],[X,M1]) :-
    Y > M,
    M < 4,
    M1 is M + 1.

closestadj([X,Y],[X,M],[X,M1]) :-
    Y < M,
    M > 1,
    M1 is M - 1.
%Considera as diagonais
closestadj([X,Y],[N,M],C) :-
    %abs(X-N) < abs(Y-M),
    diagx([X,Y],[N,M],C).

closestadj([X,Y],[N,M],C) :-
    diagy([X,Y],[N,M],C).

closestadj(A,B,C) :-
    tryperpendicular(A,B,C).

%Falta considerar quando nao tem caminho pequeno
closestadj(A,B,C) :-
    longpath(A,B,C).

longpath([X,Y],[N,Y],[N1,Y]) :-
    X > N,
    N > 1,
    N1 is N - 1.

longpath([X,Y],[N,Y],[N1,Y]) :-
    X < N,
    N < 4,
    N1 is N + 1.

longpath([X,Y],[X,M],[X,M1]) :-
    Y > M,
    M > 1,
    M1 is M - 1.

longpath([X,Y],[X,M],[X,M1]) :-
    Y < M,
    M < 4,
    M1 is M + 1.

diagx([X,_],[N,M],[N1,M]) :-
    X > N,
    N < 4,
    N1 is N + 1.

diagx([X,_],[N,M],[N1,M]) :-
    X < N,
    N > 1,
    N1 is N - 1.

diagy([_,Y],[N,M],[N,M1]) :-
    Y > M,
    M < 4,
    M1 is M + 1.

diagy([_,Y],[N,M],[N,M1]) :-
    Y < M,
    M > 1,
    M1 is M - 1.

tryperpendicular([_,Y],[N,Y],[N,Y1]) :-
    Y < 4,
    Y1 is Y + 1.

tryperpendicular([_,Y],[N,Y],[N,Y1]) :-
    Y > 1,
    Y1 is Y - 1.

tryperpendicular([X,_],[X,M],[X1,M]) :-
    X < 4,
    X1 is X + 1.

tryperpendicular([X,_],[X,M],[X1,M]) :-
    X > 1,
    X1 is X - 1.

%Visando os predicados, da primeira para a segunda posicao
%Segunda posicao a direita
aim_cell(([X1,Y],[X2,Y]),goforward) :-
    X2 > X1,
    orientation(0).

aim_cell(([X1,Y],[X2,Y]), turnright) :-
    X2 > X1,
    orientation(90).

aim_cell(([X1,Y],[X2,Y]), turnleft) :-
    X2 > X1,
    orientation(N),
    N > 90.

%Segunda posicao a esquerda
aim_cell(([X1,Y],[X2,Y]),goforward) :-
    X1 > X2,
    orientation(180).

aim_cell(([X1,Y],[X2,Y]),turnright) :-
    X1 > X2,
    orientation(270).

aim_cell(([X1,Y],[X2,Y]), turnleft) :-
    X1 > X2,
    orientation(N),
    N < 180.

%segunda posicao, cima
aim_cell(([X,Y1],[X,Y2]),goforward) :-
    Y2 > Y1,
    orientation(90).

aim_cell(([X,Y1],[X,Y2]), turnleft) :-
    Y2 > Y1,
    orientation(0).

aim_cell(([X,Y1],[X,Y2]), turnright) :-
    Y2 > Y1,
    orientation(N),
    N > 90.

%segunda posicao abaixo
aim_cell(([X,Y1],[X,Y2]),goforward) :-
    Y2 < Y1,
    orientation(270).

aim_cell(([X,Y1],[X,Y2]), turnleft) :-
    Y2 < Y1,
    orientation(180).

aim_cell(([X,Y1],[X,Y2]), turnright) :-
    Y2 < Y1,
    orientation(N),
    N < 180.

/* ----------------------------------------------------------------------- */
/* vi: set ai et ts=4 sw=4 tw=0 wm=0 fo=croql : PL config for Vim modeline */
/* Template by Dr. Beco <rcb at beco dot cc>       Version 20150620.224740 */

