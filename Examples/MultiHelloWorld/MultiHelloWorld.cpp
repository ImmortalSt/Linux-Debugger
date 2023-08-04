#include <iostream>
#include <thread>

// Функция для вывода "Hello, World!" из первого потока
void printHelloFromThread1() {
    while (1)
        std::cout << "Hello, World! - Thread 1" << std::endl;
}

// Функция для вывода "Hello, World!" из второго потока
void printHelloFromThread2() {
    while(1)
        std::cout << "Hello, World! - Thread 2" << std::endl;
}

int main() {
    // Создаем и запускаем два потока
    
    std::thread thread1(printHelloFromThread1);
	
    std::thread thread2(printHelloFromThread2);

    // Дожидаемся завершения потоков
    thread1.join(); 
    thread2.join();

    return 0;
}
