#include <iostream>
#include <cstring>
#include <pthread.h>
#include "ThreadCounter.h"

ThreadCounter::ThreadCounter(const char* output, const ThreadAttribute& attr, int iterations, bool* finished) : Thread(attr) {
    mp_finished = finished;
    m_counter = 0;
    m_iterations = iterations;
    strcpy(m_output, output);
} // ThreadCounter Constructor

void ThreadCounter::run() {
    Thread::wait(2);
    count();
} // run

void ThreadCounter::count() {
    if (mp_finished) *mp_finished = false;
    for (m_counter; m_counter < m_iterations; m_counter++) {
        Thread::wait(1);
        std::cout << m_output << std::flush;
        pthread_testcancel();
    }
    if (mp_finished) *mp_finished = true;
} // count


