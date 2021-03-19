# Description

Minimal task scheduling library for my own projects. Tasks are scheduled to happen every X **ticks**. You decide how long is single tick via configuration.

# Getting Started

```cpp
#include <Scheduler.h>

// <TICK_MICROS, MAX_TASKS>
Scheduler<1000, 2> scheduler; // 1 tick = 1000 microseconds = 1ms

void taskFoo() {
}

void taskBar() {
}

void main() {
    scheduler.addTask(&taskFoo, 200); // call taskFoo() every 200 ticks
    scheduler.addTask(&taskBar, 2000);
    
    while(1) {
        scheduler.update();
    }
}
```
