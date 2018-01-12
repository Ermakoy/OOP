#pragma once

#include <queue>
#include "Exception.h"
#include "Factorisator.h"

template<class T>
class Reader {
public:
    Reader() : isPaused(false), isExit(false), isInputEmpty(false) {};

    void
    threadedFactorise(const std::string &inputFile, const std::string &outputFile, std::string (*executionFunction)(T),
                      int threadsCount = 1){
        inputStream.open(inputFile, std::fstream::in);
        if (!inputStream.good()) throw IOException(inputFile);

        this->outputFile = outputFile;
        outputStream.open(this->outputFile, std::fstream::out);

        function = executionFunction;

        std::thread readerThread([this] { read(); });
        std::thread inputThread([this] { input(); });

        for (int i = 0; i < threadsCount; ++i) {
            threads.emplace_back([this] { execute(); });
        }
        readerThread.join();
        inputThread.join();
        for (auto &i: threads) {
            i.join();
        }
        outputStream.close();
    };


private:
    bool isExit, isPaused, isInputEmpty;

    std::ifstream inputStream;
    std::ofstream outputStream;

    std::string (*function)(T);

    std::string outputFile;

    std::queue<T> queue;
    std::mutex readLock;
    std::mutex writeLock;
    std::mutex pauseLock;

    std::condition_variable cv;

    std::vector<std::thread> threads;

    void input() {
        std::string in;

        while (!isExit && !(queue.empty() && isInputEmpty)) {

            std::cin >> in;

            if (in == "exit") {
                std::cout << "[Exit]" << std::endl;
                isExit = true;
            }

            if (in == "pause") {
                std::cout << "[Paused]" << std::endl;
                isPaused = true;
            }

            if (in == "resume") {
                std::cout << "[Resumed]" << std::endl;
                isPaused = false;
                cv.notify_all();
            }

        }
    };

    void write(const std::string &string) {
        writeLock.lock();
        if (!outputStream.is_open()) {
            // Open to append
            outputStream.open(outputFile, std::fstream::app);
        }
        outputStream << string << std::endl;
        writeLock.unlock();
    }

    void execute() {
        while (true) {
            readLock.lock();
            if (queue.empty()) {
                readLock.unlock();
                if (isInputEmpty) {
                    break;
                } else {
                    continue;
                }
            }
            T number = queue.front();
            queue.pop();
            readLock.unlock();
            std::string result = function(number);
            write(result);
            if (isExit) {
                break;
            }

            if (isPaused) {
                std::unique_lock<std::mutex> locker(pauseLock);
                cv.wait(locker);
                outputStream.close();
            }
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }

    void read() {
        while (inputStream.good()) {
            T number;

            readLock.lock();
            inputStream >> number;
            queue.push(number);
            readLock.unlock();
        }
        isInputEmpty = true;
        inputStream.close();
    };
};