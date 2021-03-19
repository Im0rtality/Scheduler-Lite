#pragma once

#include <Arduino.h>

template<uint64_t TICK_MICROS, uint8_t NUM_TASKS>
class Scheduler {
    typedef void (*scheduled_task_p)();

    typedef uint16_t ticks_t;

    struct scheduled_task_t {
        scheduled_task_p task;
        ticks_t interval;
        ticks_t tick;
    };

    scheduled_task_t _schedule[NUM_TASKS];
    uint8_t _nTasks = 0;

    uint64_t _lastTick = 0;
    ticks_t _ticks = 0;

    void tick() {
        _ticks++;
        for (int i = 0; i < _nTasks; ++i) {
            if (_ticks - _schedule[i].tick >= _schedule[i].interval) {
                _schedule[i].task();
                _schedule[i].tick = _ticks;
            }
        }
    }

public:
    void update() {
        if (micros() - _lastTick >= TICK_MICROS) {
            tick();
            _lastTick = micros();
        }
    }

    bool addTask(scheduled_task_p task, ticks_t interval) {
        if (_nTasks < NUM_TASKS) {

            _schedule[_nTasks].task = task;
            _schedule[_nTasks].interval = interval;
            _schedule[_nTasks].tick = -interval;

            _nTasks++;
            return true;
        }
        return false;
    }
};