# Synopsis Q1
## DAXPY Operation

- I updated each value of X using a multiplied by X plus Y by dividing the loop across many threads.
- I tested different thread counts and compared how much faster the program ran.
- On my system the speed kept improving until I reached 14 threads because the processor has 14 physical cores.
- After that point the speed dropped because extra threads began sharing cores which added overhead and reduced efficiency.
- I can find these hardware and thread metrics by using the lscpu command in Linux, by checking CPU usage in the system monitor, and by viewing the core count under CPU information.
