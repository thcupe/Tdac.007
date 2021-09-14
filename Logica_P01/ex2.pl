
% Arvore genealógica

%Fatos

%Homens
homem(thiago).
homem(gabriel).
homem(lucas).
homem(pedro).
homem(vitor).
homem(matheus).
homem(jake).
homem(brian).

homem(paulo).
homem(sergio).
homem(miguel).
homem(dirceu_jr).
homem(andre_c).
homem(willson).
homem(andre_l).
homem(fabio).
homem(joe).
homem(thomas).

homem(ivan).
homem(dirceu).

%Mulheres
mulher(amanda).
mulher(marina).
mulher(jeniffer).

mulher(claudia).
mulher(sapeca_iv).
mulher(janaina).
mulher(adriana).
mulher(nataly).
mulher(lucia_h).

mulher(ione).
mulher(lucia).

%conhecimento
gera(paulo, thiago).
gera(claudia, thiago).
gera(andre_l, gabriel).
gera(claudia, gabriel).

gera(sergio, lucas).
gera(sergio, pedro).
gera(janaina, lucas).
gera(janaina, pedro).

gera(adriana, vitor).
gera(willson, vitor).
gera(adriana, amanda).
gera(willson, amanda).

gera(miguel, marina).
gera(nataly, marina).
gera(nataly, matheus).

gera(lucia_h, jake).
gera(joe, jake).
gera(lucia_h, jeniffer).
gera(lucia_h, brian).
gera(thomas, jeniffer).
gera(thomas, brian).

gera(ivan, claudia).
gera(ivan, sapeca_iv).
gera(ivan, miguel).
gera(ivan, fabio).

gera(ione, claudia).
gera(ione, miguel).
gera(ione, fabio).

gera(dirceu, paulo).
gera(dirceu, sergio).
gera(dirceu, adriana).
gera(dirceu, dirceu_jr).
gera(dirceu, andre_c).
gera(dirceu, lucia_h).
gera(lucia, paulo).
gera(lucia, sergio).
gera(lucia, adriana).
gera(lucia, dirceu_jr).
gera(lucia, andre_c).
gera(lucia, lucia_h).

%regras

pai(X, Y) :- homem(X), gera(X, Y).
mae(X, Y) :- mulher(X), gera(X, Y).
pais(X, Y) :- gera(X, Y).

filhos(X, Y) :- gera(Y, X). %sao filhos de Y todos os que sao gerados por ele
filho(X, Y) :- homem(X), gera(Y, X).
filha(X, Y) :- mulher(X), gera(Y, X).

irmaos_completos(X, Xo) :-
                 pai(P, X), pai(P, Xo),
                 mae(M, X), mae(M, Xo),
                 X\=Xo.

meios_irmaos(X,Xo):-
             pais(Y, X), pais(Y, Xo),
             pais(Yo, X), not(pais(Yo, Xo)), not(Y=Yo), not(X=Xo).

irmaos(X, Xo) :-
       irmaos_completos(X, Xo) ; meios_irmaos(X,Xo).
       % esta complicação foi feita para
       % evitar ter os mesmos resultados mostrados duas vezes.
       % e também permitir que você verifique irmãos com maior precisão.

irmao(X, Xo) :-
      homem(X),
      irmaos(X, Xo).

irma(X, Xo) :-
     mulher(X),
     irmaos(X, Xo).

meio_irmao(X,Xo):-
           homem(X),
           meios_irmaos(X,Xo).

meia_irma(X,Xo):-
          mulher(X),
          meios_irmaos(X,Xo).

irmao_completo(X, Xo) :-
               homem(X),
               irmaos_completos(X, Xo).

irma_completa(X, Xo) :-
              mulher(X),
              irmaos_completos(X, Xo).

% Z = neto
avoo(X, Z) :-
     homem(X),
     gera(X, Y),
     gera(Y, Z).

avoa(X, Z) :-
     mulher(X),
     gera(X, Y),
     gera(Y, Z).

avos(X, Z) :- avoo(X, Z) ; avoa(X, Z).

netos(Z, X) :- avoo(X, Z) ; avoa(X, Z).

neto(Z, X) :-
     homem(Z),
     netos(Z, X).

neta(Z, X) :-
     mulher(Z),
     netos(Z, X).

tio(T, Y) :-
    homem(T),
    irmaos(T, X), gera(X, Y).

tia(T, Y) :-
    mulher(T),
    irmaos(T, X), gera(X, Y).

tios(T, Y) :- irmaos(T, X), gera(X, Y).

primes(Y, Yo) :-
       gera(X, Y),
       gera(Xo, Yo),
       irmaos(X, Xo).

primo(Y, Yo) :-
      homem(Y),
      primes(Y, Yo).

prima(Y, Yo) :-
      mulher(Y),
      primes(Y, Yo).

sobrinhe(X, Y) :-
         filhos(X, Yo),
         irmaos(Y, Yo).

sobrinho(X, Y) :-
         homem(X),
         sobrinhe(X, Y).

sobrinha(X, Y) :-
         mulher(X),
         sobrinhe(X, Y).

