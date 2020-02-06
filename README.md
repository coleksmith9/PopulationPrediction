# PopulationPrediction
Given initial populations, this program can predict the stable population sizes using Lotka–Volterra differential equation.

### Building
To compile the program use the following command. The current directory must be the top level project folder.

`g++ *.hpp *.cpp -I./include -o main.exe -L./lib -lsfml-graphics -lsfml-window -lsfml-system`

To execute the program use the following command.

`./main`

### Todo:
1. Draft a UI, each person does as part of there "Looks Like" project
1. Draft program (UML, define what it needs to do)
1. Create UI framework
    1. Base Widgets: frame, button, textbox, etc.
    1. Other Widgets: graph, etc.
1. Create UI
