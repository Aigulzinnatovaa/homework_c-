#include <iostream>
#include <fstream>
#include <thread>
#include <vector>

using namespace std;

//1 Определяем размер буфера для записи в файл (512 байт).
const int BUFFER_SIZE = 512;

//2 Создаем функцию `writeToFile`, которая принимает имя входного файла, имя выходного файла, индекс потока и общее количество потоков.
void writeToFile(const string& inputFileName, const string& outputFileName, int threadIndex, int numThreads) {
    //3 Внутри функции открываем входной файл 
    ifstream inputFile(inputFileName, ios::binary);
    if (!inputFile.is_open()) {
        cerr << "Failed to open input file." << endl;
        return;
    }

    ofstream outputFile(outputFileName, ios::binary | ios::app);
    if (!outputFile.is_open()) {
        cerr << "Failed to open output file." << endl;
        inputFile.close();
        return;
    }
    //перемещаем указатель на нужную позицию (индекс потока * размер буфера * общее количество потоков) и считывала из входного файла 512 байт в буфер.
    inputFile.seekg(threadIndex * BUFFER_SIZE * numThreads);

    char buffer[BUFFER_SIZE];
    int bytesRead = 0;

    while (bytesRead < BUFFER_SIZE) {
        inputFile.read(buffer + bytesRead, BUFFER_SIZE - bytesRead);
        bytesRead += inputFile.gcount();
    }
    // записала в буфер выходной файл
    outputFile.write(buffer, BUFFER_SIZE);
    

// Закрываем оба файла.
    inputFile.close();
    outputFile.close();
}
//В  методе `main` определяем имена входного и выходного файлов, а также количество потоков (равное количеству ядер процессора).
int main() {
    const string inputFileName = "C:\\Users\\Айгуль\\Desktop\\c++\\input.txt";
    const string outputFileName = "C:\\Users\\Айгуль\\Desktop\\output.bin";
    const int numThreads = thread::hardware_concurrency();

    // Создаем вектор потоков и запускаем функцию `writeToFile` для каждого потока, затем дожидаюсь завершения всех потоков.
    
    vector<thread> threads(numThreads);
    //сам прцесс записывания
    for (int i = 0; i < numThreads; ++i) {
        threads[i] = thread(writeToFile, inputFileName, outputFileName, i, numThreads);
    }

    for (auto& thread : threads) {
        thread.join();
    }
    // Возвращаем 0
    return 0;
}


//Описание программы:

//1. Определяем размер буфера для записи в файл (512 байт).
//2. Создаем функцию `writeToFile`, которая принимает имя входного файла, имя выходного файла, индекс потока и общее количество потоков.
//3. Внутри функции открываем входной файл и перемещаем указатель на нужную позицию (индекс потока * размер буфера * общее количество потоков).
//4. Считываем из входного файла 512 байт в буфер.
//5. Записываем буфер в выходной файл.

