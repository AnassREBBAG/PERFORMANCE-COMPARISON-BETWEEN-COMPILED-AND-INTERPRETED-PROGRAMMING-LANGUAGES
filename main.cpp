#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

void addVectors(std::vector<int>& result, const std::vector<int>& vector1, const std::vector<int>& vector2, int startIndex, int endIndex) {
    for (int i = startIndex; i < endIndex; i++) {
        result[i] = vector1[i] + vector2[i];
    }
}

int main() {

    
    int N = 10000000;
    std::vector<int> vector1(N);
    std::vector<int> vector2(N);

    for(int i=0; i < N; i++)
    {
        vector1[i] = i;
        vector2[i] = 2 * i;
    }

    auto startTime = std::chrono::high_resolution_clock::now();

    int length = vector1.size();
    std::vector<int> result(length);

    int numThreads = std::thread::hardware_concurrency(); // Number of hardware threads

    int chunkSize = (length + numThreads - 1) / numThreads; // Calculate the chunk size for each thread

    std::vector<std::thread> threads;

    // Create and start the threads
    for (int i = 0; i < numThreads; i++) {
        int startIndex = i * chunkSize;
        int endIndex = std::min(startIndex + chunkSize, length);

        threads.emplace_back(addVectors, std::ref(result), std::cref(vector1), std::cref(vector2), startIndex, endIndex);
    }

    // Wait for all threads to complete
    for (auto& thread : threads) {
        thread.join();
    }

    // Output the input vectors and the result vector
/*    std::cout << "Vector1: ";
    for (const auto& element : vector1) {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    std::cout << "Vector2: ";
    for (const auto& element : vector2) {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    std::cout << "Result: ";
    for (const auto& element : result) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
*/
    auto endTime = std::chrono::high_resolution_clock::now();
    auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
    std::cout << "Time spent: " << elapsedTime.count() << " milliseconds" << std::endl;


    return 0;
}
