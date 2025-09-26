# CPU Scheduling Simulator 🖥️⏱️

![C](https://img.shields.io/badge/Language-C-blue)

A simple interactive **CPU Scheduling Simulator** in C supporting multiple algorithms with tables, Gantt charts, and average calculations.

---

## Features

- **Algorithms Supported**:
  - FCFS – First Come First Serve
  - SJF – Shortest Job First (Non-preemptive)
  - SRT – Shortest Remaining Time (Preemptive SJF)
  - PNP – Preemptive Priority
  - PP – Non-preemptive Priority
  - RR – Round Robin (user-defined quantum)

- **Interactive Shell**:
  - `scheduling` – Input process details.
  - `gantt [algorithm]` – Display Gantt chart.
  - `table [algorithm]` – Display process table.
  - `average` – Show average WT and TAT.
  - `quantum x` – Set RR time quantum.
  - `quit` – Exit program.

- Handles idle CPU and dynamic timeline visualization.

---

## Usage

1. **Compile**:

bash
gcc main.c -o scheduler
Run:

bash
Copy code
./scheduler
Sample Commands:

text
Copy code
> scheduling
## Enter process arrival, burst, priority

> gantt all
## Display all Gantt charts

> table fcfs
## Display FCFS table

> quantum 4
## Set RR quantum to 4

> average
## Show average WT/TAT for all algorithms

> quit
## Exit shell
Input Format
Each process: ArrivalTime BurstTime Priority

Example:

Copy code
0 5 2
1 3 1
2 8 3
Priority: Lower number = higher priority.

RR Quantum: Must be positive integer.
