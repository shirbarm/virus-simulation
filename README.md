# virus-simulation
virus simulation using STL and Reference Counting support

In this project, an object-oriented world of a virus population is realized, with a virus defined using a string of characters, mainly a unique alphabet: {G, C, T, A}.
It is assumed that when checking the state of the world (at any time pulse), there is a population of a fixed size of viruses, each virus contains a valid string, and that they perform string updates from one point in time to another. With the definition of the world, the initial generation of viruses will be defined; The character strings of this generation are considered to be the "ancestors" of the strings during the simulation. In particular, each virus must remember during the simulation who the "ancestor" of its string of characters is. About this memory be realized through a reference counting mechanism.

attached files:
1. config.dat - components of the world of viruses.
2. first_generation.dat - The initial generation file.

compiled by c++11: 
  g++ -std=c++11 *.h *.cpp -o simVirus
  ./simVirus config.dat first_generation.dat
