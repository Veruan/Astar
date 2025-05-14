# A* Algorithm Visualisation Program

The current executable in the repo is compiled for **Windows**.

To run the project, compile the source files with the **SDL2 library**, the **SDL2_ttf extension**, and include the following files:
- `SDL2.dll`
- `SDL2_ttf.dll`
- Font files  `*.ttf`

---

## OVERVIEW

<ul>

<li><b>1. Menu</b><br><br>
This is the main menu of the application.
<br><br>
<img src="./assets/menu.png" alt="Menu" width="1000">
</li>

<li><b>2. Simulation</b>
<ul>

<li><b>2.1 Main View</b><br><br>
You can draw the labyrinth as you like, then press <kbd>Enter</kbd> to run the simulation.
<br><br>
<img src="./assets/simulation.png" alt="Simulation Main View" width="1000">
</li>

<li><b>2.2 Visited & Priority Queue</b><br><br>
The light-brown colored grid elements are those added to the **priority queue** for evaluation.  
The dark-red colored grid elements are those **already evaluated and visited** by the algorithm.
<br><br>
<img src="./assets/visited.png" alt="Visited Nodes" width="1000">
</li>

<li><b>2.3 Final Path</b><br><br>
At the end, the <strong>shortest path</strong> between the start and end points is marked in <strong>blue</strong>.
<br><br>
<img src="./assets/path.png" alt="Final Path" width="1000">
</li>

</ul>
</li>

</ul>
