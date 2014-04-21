
Life - By Coleman Jackson

"The Game of Life" is a very simple but interesting model of life, devised by John
Conway in the 1970's. It is not really a game", because there are no players; it is probably more accurate
to call it a \simulation". For this project, you will write some C++ programs to simulate GoL.
In GoL, the terrain is a two{dimensional grid of square cells, as shown in Figure 1. In this document,
cells will be indexed using x and y integer coordinates. Theoretically, the terrain is innitely large in all
directions. At any point in time, each cell in the grid may be in one of two possible states: alive or dead.
Time is also discretized, and everything evolves together in \steps" or \generations". The state of a cell
evolves over time according to the states of its eight neighbors (see Figure 2), according to the following
rules"

-Professor Miner's Description of the game of life

. If a cell is alive in generation i, then:
 (a) if there are fewer than two alive neighbors in generation i, then the cell will be dead in generation i + 1 (from loneliness).
 (b) if there are two or three alive neighbors in generation i, then the cell will be alive in generation i+1.
 (c) if there are more than three alive neighbors in generation i, then the cell will be dead in generation i + 1 (from over-population).
 
 In addition to the life files, the life executable will also parse the following files:
 
WireWorld: http://en.wikipedia.org/wiki/WireWorld


Cellular Automata: http://en.wikipedi.org/wiki/elementary_cellular_automaton


Life, the program, simulates these file types. The controls for life are listed using ./life -h


Life is comprised of two major data structures, the InfoParser class (InfoParser.cc and InfoParser.h), and the InfoHolder class (InfoHolder.cc and InfoHolder.h), as well as a main program file containing several supporting functions designed for FileParser and Info. InfoParser acts as the parser to the .life file, and InfoHolder acts to store the information parsed by InfoParser. This has been extended to include both WireWorld Files, and Elementary cellular automata. Each one of these has their own infoparser and infoholder, aptly named as you will see below.


The stages of the program are listed below, along with the header files that oversee them:

1: open the file, strip it of whitespace, and parse it for editing: ParserUtil.h
2: parse the files into their respective information holders: InfoParser.h WireWorldParser.h CellParser.h InfoHolder.h ( <- this name is a relic of the previous build) CellInfo.h WireInfo.h
3: generate the initial terrain and update the board based on the number of generations: GenerationHelperMethods.h
4: Display the board based on the switch passed in: DisplayHelperMethods.h






Life GUI

Not made. Too far behind. -200.