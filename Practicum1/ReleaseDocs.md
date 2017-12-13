# Praktikum I

## Aufgabe 1
### Quellcodeverzeichnis
| Teilaufgabe | Verzeichnis        | Quellcode       | Compile command | Execute command                |
|-------------|--------------------|-----------------|-----------------|--------------------------------|
| A           | `Exercise1/TaskA/` | `task-a.c`      | `make`          | `./taska <amount> <chunksize>` |
| B           | `Exercise1/TaskB/` | `task-b.c`      | `make`          | `./taskb <amount> <chunksize>` |
| C           | `Exercise1/TaskB/` | `task-b.c`      | `make`          | `./run-tests.sh`               |
| D           | `Exercise1/TaskD/` | `task-d.c`      | `make`          | `./taskd <amount> <chunksize>` |

### Weiterführende Erklärungen
#### Teilaufgabe C
![Diagramm 1C](Practicum1/time_measurements/Task1-C.png)

Zunächst einmal ist festzustellen, dass die gemessenen Laufzeiten unabhängig der Chunksizes bei threads=4 konsistent am kürzesten waren, was mit der Anzahl der genutzten CPU-Cores zusammenhängt. Bei 4 Threads/Cores wird im Optimalfall jedem Core ein Thread zugewiesen, sodass unnötiger Overhead bei etwaigem Threadwechsel entfällt. Die mit nur 2 Threads durchgeführten Berechnungen waren stets am langsamsten, da die hier nicht alle Cores parallel genutzt werden können. Die mit 8 bzw. 16 Threads erzielten Ergebnisse ordnen sich zwischen diesen beiden Extremen ein, was mit zuvor genanntem Overhead erklärbar ist.

[TODO Erklärungen für chunk sizes]

#### Teilaufgabe D
![Diagramm 1D](Practicum1/time_measurements/Task1-D.png)

[TODO Erklärungen für dynamic]


## Aufgabe 2
### Quellcodeverzeichnis
| Teilaufgabe | Verzeichnis        | Quellcode       | Compile command | Execute command                |
|-------------|--------------------|-----------------|-----------------|--------------------------------|
| A           | `Exercise2/TaskA/` | `task_a.c`      | `make`          | `./task_a <array_length>`      |
| B           | `Exercise2/TaskB/` | `task_b.c`      | `make`          | `./task_b <array_length>`      |
| C           | `Exercise2/TaskC/` | `task_c.c`      | `make`          | `./run-tests.sh`               |

### Weiterführende Erklärungen
#### Teilaufgabe C
![Diagramm 2C](Practicum1/time_measurements/Task2-C.png)

[TODO Erklärungen für final clause]


## Aufgabe 3
[TODO TBC]


## Aufgabe 4
[TODO TBC]


## Aufgabe 5
### Quellcodeverzeichnis
| Teilaufgabe | Verzeichnis        | Quellcode       | Compile command | Execute command                                     |
|-------------|--------------------|-----------------|-----------------|-----------------------------------------------------|
| A + B       | `Exercise5/TaskB/` | `task-b.cpp`    | `make`          | `./taskb <xmin> <xmax> <ymin> <ymax> <maxIter>`     |
| C           | `Exercise5/TaskC/` | `task-c.cpp`    | `make`          | `./run-tests.sh`                                    |

### Weiterführende Erklärungen
#### Teilaufgabe C
![Diagramm 5C](Practicum1/time_measurements/Task5-C.png)
