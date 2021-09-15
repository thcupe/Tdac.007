# Exercise: Wumpus World
## Wumpus Assignment for Students

Create an intelligent agent to deal with the Wumpus world.

# Version 1.0

* World setup:
    - `world_setup([5, grid, stander, 0.05, 4, 1, [no, no]]).`
* Size: 5x5
* Type: grid
* Wumpus do not move
* 5% chance of gold in each square
* 4 pits
* 1 bat
* Agent starts at [1,1], facing right (0 degrees)
* Starve after 100 moves

# Version 2.0

* World setup:
    - `world_setup([0, grid, walker, 0.1, 0.08, 0.06, [yes, yes]]).`
* Size: random
* Type: grid
* Wumpus original walk: when hear shoot, or you enter its cave
* 10% chance of gold in each square
* 8% pits
* 6% bat
* Agent starts at a random square, facing a random angle
* Starve after Size^2x4 moves

# Version 3.0

* World setup:
    - `world_setup([20, dodeca, walker, 0.05, 3, 1, [no, no]]).`
* Size: 20 squares
* Type: dodecahedron
* Wumpus move when hear shoot or when agent enters its square
* 5% chance of gold in each square
* 3 pits
* 1 bat
* Agent starts at [1,1], facing right (0 degrees)

## Coordinator

Prof. Dr. Ruben Carlo Benante <rcb@upe.br>

## License

GNU GPL v.2

