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
% 1. goforward (go)                - andar
% 2. turnright (turn, turnr ou tr) - girar sentido horario
% 3. turnleft (turnl ou tl)        - girar sentido anti-horario
% 4. grab (gr)                     - pegar o ouro
% 5. shoot (sh)                    - atirar a flecha
% 6. sit (si)                      - sentar (nao faz nada, passa a vez)
% 7. climb (cl)                    - sair da caverna
% 8. gps                           - pega sua posicao e orientacao
%
% Costs (Custos):
% Actions: -1 (Andar/Girar/Pegar/Sair/Atirar/Sentar/GPS)
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
% Performance: it does not go very well as you can imagine
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

:- use_module(wumpus, [start/0]). % agente usa modulo simulador

% Versao 1.0
% Mundo: 
%    Tamanho (size) 5x5, quadrado (grid)
%    Wumpus nao anda
%    5% de chance de ouro por casa, 4 buracos e 1 morcego
%    agente inicia na casa [1,1], orientado para direita (0 graus)
%    Maximo de acoes antes de morrer de fome: Size^2x4 = 5x5x4 = 100 (media de 4 acoes por casa)
world_setup([4, fig62, stander, 0.05, 4, 1, [no, no]]).

% Versao 2.0
% Mundo: 
%    Tamanho (size) aleatorio, quadrado (grid)
%    Wumpus com andar original: quando escuta flechada ou quando se entra em sua casa
%    10% de chance de ouro por casa, 8% buracos e 6% morcego
%    agente inicia em casa aleatoria, orientado tambem aleatoriamente (use GPS)
%    Maximo de acoes antes de morrer de fome: Size^2x4 = media de 4 acoes por casa
%    ou seja, se mundo 5x5, maximo de acoes eh 5^2x4=100
%
%world_setup([0, grid, walker, 0.1, 0.08, 0.06, [yes, yes]]).

% Versao 3.0
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

init_agent.

run_agent(Percepcao, Acao) :-
  cabeca_dura(Percepcao, Acao).

cabeca_dura(_,goforward).

/* ----------------------------------------------------------------------- */
/* vi: set ai et ts=4 sw=4 tw=0 wm=0 fo=croql : PL config for Vim modeline */
/* Template by Dr. Beco <rcb at beco dot cc>       Version 20150620.224740 */

