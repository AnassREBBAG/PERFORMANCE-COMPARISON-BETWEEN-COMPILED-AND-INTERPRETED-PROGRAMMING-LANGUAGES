import multiprocessing
import time

def add_vectors(result, vector1, vector2, start_index, end_index):
    for i in range(start_index, end_index):
        result[i] = vector1[i] + vector2[i]

def main():
    N = 10000000
    vector1 = [i for i in range(N)]
    vector2 = [2*i for i in range(N)]

    start_time = time.time()
    
    length = len(vector1)
    result = [0] * length

    num_threads = multiprocessing.cpu_count()  # Number of available CPU threads

    chunk_size = (length + num_threads - 1) // num_threads  # Calculate the chunk size for each thread

    processes = []

    # Create and start the processes
    for i in range(num_threads):
        start_index = i * chunk_size
        end_index = min(start_index + chunk_size, length)

        process = multiprocessing.Process(target=add_vectors, args=(result, vector1, vector2, start_index, end_index))
        processes.append(process)
        process.start()

    # Wait for all processes to complete
    for process in processes:
        process.join()


    # Output the input vectors and the result vector
    #print("Vector1:", vector1)
    #print("Vector2:", vector2)
    #print("Result:", result)

    end_time = time.time()
    elapsed_time = end_time - start_time

    print("Time spent: {:.2f} seconds".format(elapsed_time))
    
if __name__ == '__main__':
    
    main()
