# Projeto ProgramAuto: sub-título

## Introdução

* Colocar uma explicação de cada algoritmo escolhido
* Colocar aqui uma breve explicação do programa
* Explicar o processamento


## Casos e Usos

* Colocar aqui alguns exemplos
* Casos de uso

## Arquivos

* Explicar a produção 

## Repositório

### Arquivos no repositório

No repositório devem constar apenas e tão somente os arquivos:

* AUTHORS
* LICENSE
* README.md (este arquivo)
* VERSION
* biblio.bib: arquivo com bibliografia
* makefile
* pext-matdiscreta-benante-sobrenome1-sobrenome2.pdf
* pext-matdiscreta-benante-sobrenome1-sobrenome2.tex
* Imagens usadas que foram incluídas no artigo .tex, na subpasta imagens/

### Comandos para criar repositório no Hydra

Apenas um aluno do grupo, o responsável por criar, faz essa sequencia:

Exemplo para grupo 2021s1/pext01. Mude os números conforme o semestre e o seu grupo. Entre na pasta rascunhos e digite:

```
$ cd ~/programa2/rascunhos
$ git clone git@hydra:repos/pextXX.git
$ cd pextXX
$ cat README.md # leia este arquivo
```

E continue após ler o arquivo, seguindo as instruções:

```
$ cd ~/programa2/rascunhos
$ mv pextXX pext01
$ cd pext01
$ ssh git@hydra newrepo pext01.git
$ git remote remove origin
$ git remote add origin git@hydra:repos/2021s1/pext01.git
$ git pull origin master --allow-unrelated-histories -s recursive -X ours --no-edit
$ cp ~/grupos/programa2/pext/AUTHORS1 AUTHORS
$ git cm "adicionado AUTHORS"
$ git push -u origin master
```

E a partir de agora seu repositorio esta remoto, e os outros alunos do grupo poderao trabalhar em grupo após clonarem.


### Comandos para clonar o repositório remoto no Hydra

Os outros alunos do grupo irão clonar o repositório com:

```
$ cd ~/programa2/rascunhos
$ git clone git@hydra:repos/2021s1/pext01.git
```

Confira com:

```
$ cd pext01
$ ls
$ git st
```

Talvez confira também um "commit" e "push" da sua parte, seguido de um "pull" de outro aluno, para ter certeza que estão colaborando no mesmo repositório.


### Entrega na pasta trabalhos

Antes do final do prazo, basta clonar com:

```
$ cd ~/programa2/trabalhos
$ git clone git@hydra:repos/2021s1/pext01.git
```


## Copyright

* Date: 2021-06-14
* License: GNU/GPL v2.0

## Authors

* Author: Prof. Dr. Ruben Carlo Benante
* Email: rcb@upe.br

* Author: Nome do aluno 1
* Email:

* Author: Nome do aluno 2
* Email:

