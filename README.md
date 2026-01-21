
# GRS_PA01 – Processes and Threads

**Course:** Graduate Systems (CSE638)
**Assignment:** PA01 – Processes and Threads
**Roll Number:** MT25010
**Name:** Abhinay Prakash
**GitHub Repository:** [https://github.com/IIITD-Abhinay/GRS_PA01](https://github.com/IIITD-Abhinay/GRS_PA01)

---

## Overview

This repository contains the implementation and experimental evaluation for **PA01: Processes and Threads**.
The assignment studies the behavior of **process-based** and **thread-based** concurrency under different workload types:

* CPU-intensive
* Memory-intensive
* I/O-intensive

System performance is evaluated using standard Linux monitoring tools, and experiments are fully automated using bash scripts.

---

## Repository Contents

* **Program A (Processes)**
  `MT25010_Part_A_Program_A.c`
  Creates multiple child processes using `fork()`.

* **Program B (Threads)**
  `MT25010_Part_A_Program_B.c`
  Creates multiple threads using POSIX `pthread`.

* **Worker Functions**

  * `MT25010_Part_B_cpu.c` – CPU-intensive workload
  * `MT25010_Part_B_mem.c` – Memory-intensive workload
  * `MT25010_Part_B_io.c` – I/O-intensive workload

* **Automation Scripts**

  * `MT25010_Part_C_shell.sh` – Automation for Part C experiments
  * `MT25010_Part_D_shell.sh` – Automation for Part D scaling experiments

* **Measurement Data**

  * `MT25010_Part_C_CSV.csv`
  * `MT25010_Part_D_CSV.csv`

* **Build System**

  * `Makefile`

* **Plots and Analysis**

  * CPU and execution time plots (PNG/PDF)
  * Final report PDF

---

## Build Instructions

Compile both programs using:

```bash
make
```

This generates:

* `programA` (process-based)
* `programB` (thread-based)

---

## Running Experiments

### Part C – Fixed Concurrency Experiments

```bash
./MT25010_Part_C_shell.sh
```

This script:

* Runs all program + workload combinations
* Collects CPU, I/O, and execution time data
* Stores results in `MT25010_Part_C_CSV.csv`

---

### Part D – Scaling Experiments

```bash
./MT25010_Part_D_shell.sh
```

This script:

* Varies the number of processes (2–5) and threads (2–8)
* Automates execution and measurement
* Stores results in `MT25010_Part_D_CSV.csv`

---

## Cleaning Build Artifacts

Executable files are **not committed** to the repository.
To remove generated binaries:

```bash
make clean
```

---

## Experimental Environment

* Operating System: Linux (Ubuntu-based)
* Tools used:

  * `fork`, `pthread`
  * `taskset`
  * `top`
  * `iostat`
  * `time`
* All experiments are CPU-pinned to reduce scheduling variability.
* Measurements are fully automated and reproducible.

---

## AI Usage Declaration

AI tools (ChatGPT) were used for guidance in understanding system concepts, debugging code, and structuring automation scripts.
All code, experiments, and results were reviewed, understood, and validated by the author.

---

## Notes

* No compiled binaries are included in the repository, as per assignment instructions.
* File naming conventions strictly follow the assignment guidelines.
* A single PDF report is provided separately, containing plots, screenshots, and analysis.

---

## References

1. Silberschatz, Galvin, and Gagne, *Operating System Concepts*
2. Linux manual pages: `fork(2)`, `pthread_create(3)`, `top(1)`, `iostat(1)`

---
