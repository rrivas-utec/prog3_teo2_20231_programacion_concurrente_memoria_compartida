//
// Created by rrivas on 8/06/2023.
//

#ifndef PROG3_TEO2_20231_PROGRAMACION_CONCURRENTE_MEMORIA_COMPARTIDA_COUNT_FREQUENCE_H
#define PROG3_TEO2_20231_PROGRAMACION_CONCURRENTE_MEMORIA_COMPARTIDA_COUNT_FREQUENCE_H

#include <thread>
#include <iterator>
#include <vector>
#include <map>
using namespace std;

template<typename Iterator, typename T = typename Iterator::value_type>
void frequence(Iterator start, Iterator stop, map<T, int>& result) {
    while (start != stop) {
        result[*start]++;
        ++start;
    }
}
template<typename Iterator>
auto count_frequence(Iterator start, Iterator stop) {
    // Variables auxiliares
    auto nh = thread::hardware_concurrency();
    auto sz = distance(start, stop);
    auto range = sz / nh;
    using T = typename Iterator::value_type;
    map<T, int> result;
    // Vector de hilos
    vector<thread> vh(nh);
    for (int i = 0; i < nh; ++i) {
        // Iteradores del hilos
        auto r_start = next(start, i* range);
        auto r_stop = i <= nh - 1? next(start, (i + 1)*range): stop;
        // Asignar la tarea al hilo
        vh[i] = thread(frequence<Iterator>, r_start, r_stop, ref(result));
    }
    // Unir los hilos
    for (int i = 0; i < nh; ++i) {
        vh[i].join();
    }
    return result;
}

#endif //PROG3_TEO2_20231_PROGRAMACION_CONCURRENTE_MEMORIA_COMPARTIDA_COUNT_FREQUENCE_H
