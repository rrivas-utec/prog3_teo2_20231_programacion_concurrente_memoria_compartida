#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <mutex> // Incluir la libreria
using namespace std;

mutex mtx; // Variable Global Cerrojo de una puerta

class guardia {
    mutex& _mtx;
public:
    guardia(mutex& mtx): _mtx(mtx) {
        _mtx.lock();
    }
    ~guardia() {
        _mtx.unlock();
    }
};

void incrementar(int& value) {
    this_thread::sleep_for(std::chrono::milliseconds (10));
//    lock_guard lg(mtx);
    unique_lock ul(mtx);
//    guardia g(mtx);
//    mtx.lock();
    value++;
    ul.unlock();
    ul.lock();
    value++;
//    mtx.unlock();
}
void calcular_total_variable_compartida() {
    int nh = 130;
    int nr= 100;
    for (int i = 0; i < nr; ++i) {
        int x = 0;
        // Creando los hilos
        vector<thread> vh(nh);
        // Asignarle la tarea a los hilos
        for (auto& h: vh)
            h = thread(incrementar, ref(x));
        // Unir los hilos
        for (auto& h: vh)
            h.join();
        cout << x << " ";
    }
}

int main() {
    calcular_total_variable_compartida();
    return 0;
}
