#include <iostream>
#include <fstream>
#include <thread>
#include <vector>

using namespace std;

//1 ���������� ������ ������ ��� ������ � ���� (512 ����).
const int BUFFER_SIZE = 512;

//2 ������� ������� `writeToFile`, ������� ��������� ��� �������� �����, ��� ��������� �����, ������ ������ � ����� ���������� �������.
void writeToFile(const string& inputFileName, const string& outputFileName, int threadIndex, int numThreads) {
    //3 ������ ������� ��������� ������� ���� 
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
    //���������� ��������� �� ������ ������� (������ ������ * ������ ������ * ����� ���������� �������) � ��������� �� �������� ����� 512 ���� � �����.
    inputFile.seekg(threadIndex * BUFFER_SIZE * numThreads);

    char buffer[BUFFER_SIZE];
    int bytesRead = 0;

    while (bytesRead < BUFFER_SIZE) {
        inputFile.read(buffer + bytesRead, BUFFER_SIZE - bytesRead);
        bytesRead += inputFile.gcount();
    }
    // �������� � ����� �������� ����
    outputFile.write(buffer, BUFFER_SIZE);
    

// ��������� ��� �����.
    inputFile.close();
    outputFile.close();
}
//�  ������ `main` ���������� ����� �������� � ��������� ������, � ����� ���������� ������� (������ ���������� ���� ����������).
int main() {
    const string inputFileName = "C:\\Users\\������\\Desktop\\c++\\input.txt";
    const string outputFileName = "C:\\Users\\������\\Desktop\\output.bin";
    const int numThreads = thread::hardware_concurrency();

    // ������� ������ ������� � ��������� ������� `writeToFile` ��� ������� ������, ����� ��������� ���������� ���� �������.
    
    vector<thread> threads(numThreads);
    //��� ������ �����������
    for (int i = 0; i < numThreads; ++i) {
        threads[i] = thread(writeToFile, inputFileName, outputFileName, i, numThreads);
    }

    for (auto& thread : threads) {
        thread.join();
    }
    // ���������� 0
    return 0;
}


//�������� ���������:

//1. ���������� ������ ������ ��� ������ � ���� (512 ����).
//2. ������� ������� `writeToFile`, ������� ��������� ��� �������� �����, ��� ��������� �����, ������ ������ � ����� ���������� �������.
//3. ������ ������� ��������� ������� ���� � ���������� ��������� �� ������ ������� (������ ������ * ������ ������ * ����� ���������� �������).
//4. ��������� �� �������� ����� 512 ���� � �����.
//5. ���������� ����� � �������� ����.

