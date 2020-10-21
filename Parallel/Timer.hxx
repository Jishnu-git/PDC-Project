#ifndef TIMER_HEADER
#define TIMER_HEADER

#include <chrono>

using namespace std;
using namespace chrono;

class Timer {
    time_point<steady_clock> start;
    bool stopped;
    bool paused;
    double result;
public:
    Timer() {
        Start();
    }

    void Start() {
        start = steady_clock::now();
        stopped = false;
        paused = false;
        result = 0;
    }

    double Stop() {
        if (stopped) {
            return -1;
        } else if (paused) {
            stopped = true;
            return result;
        }
        result += (double) (steady_clock::now() - start).count() / 1000000000;
        stopped = true;
        return result;
    }

    double Pause() {
        if (stopped) {
            return -1;
        } else if (paused) {
            return result;
        }
        result += (double) (steady_clock::now() - start).count() / 1000000000;
        paused = true;
        return result;
    }

    void Resume() {
        if (stopped || !paused) return;
        start = steady_clock::now();
        paused = false;
    }

    double GetTime() {
        return result + ((double) (steady_clock::now() - start).count() / 1000000000);
    }

    void Reset() {
        start = steady_clock::now();
    }
};

#endif