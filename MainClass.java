import java.util.Arrays;

public class MainClass {
    private static final int NUM_THREADS = 12; // Number of threads to use

    public static void main(String[] args) {

        int N = 10000000;

        int[] vector1 = new int[N];
    
        int[] vector2 = new int[N];

        for(int i = 0;i<N;i++){
            vector2[i] = 2*i;
            vector1[i] = i;

        }


        long startTime = System.currentTimeMillis();

        int[] result = addVectors(vector1, vector2);

        long endTime = System.currentTimeMillis();

        //System.out.println("Vector1: " + Arrays.toString(vector1));
        //System.out.println("Vector2: " + Arrays.toString(vector2));
        //System.out.println("Result: " + Arrays.toString(result));

        long elapsedTime = endTime - startTime;
        
        System.out.println("Time spent: " + elapsedTime + " milliseconds");


    }

    private static int[] addVectors(int[] vector1, int[] vector2) {
        int length = vector1.length;
        int[] result = new int[length];

        // Calculate the chunk size for each thread
        int chunkSize = (int) Math.ceil((double) length / NUM_THREADS);

        // Create an array of threads
        Thread[] threads = new Thread[NUM_THREADS];

        // Create and start the threads
        for (int i = 0; i < NUM_THREADS; i++) {
            final int startIndex = i * chunkSize;
            final int endIndex = Math.min(startIndex + chunkSize, length);

            threads[i] = new Thread(() -> {
                for (int j = startIndex; j < endIndex; j++) {
                    result[j] = vector1[j] + vector2[j];
                }
            });

            threads[i].start();
        }

        // Wait for all threads to complete
        try {
            for (Thread thread : threads) {
                thread.join();
            }
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        return result;
    }
}
