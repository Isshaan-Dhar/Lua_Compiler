#include "../include/compiler.h"

int main(int argc, char *argv[]) {
    // 1. Check for input file argument
    if (argc < 2) {
        printf("Usage: %s <source_file>\n", argv[0]);
        return 1;
    }

    // 2. Attempt to open the source file
    source = fopen(argv[1], "r");
    if (!source) {
        perror("ERROR: Could not open source file");
        return 1;
    }

    printf("--- Compiling: %s ---\n", argv[1]);
    printf("Forensic Compiler Phase: Single-Pass Parsing & Optimization\n");
    printf("-----------------------------------\n");
    fflush(stdout); // Ensure text is sent to the terminal immediately

    // 3. Start Benchmark Timer
    // We use clock() for cross-platform compatibility on Windows/MSYS2
    clock_t start_time = clock();

    // 4. Trigger the Parser (The core compiler logic)
    parse(); 

    // 5. End Benchmark Timer
    clock_t end_time = clock();

    // 6. Calculate Results
    double time_ms = ((double)(end_time - start_time) / CLOCKS_PER_SEC) * 1000.0;

    // 7. Output Final Benchmark Data
    printf("-----------------------------------\n");
    printf("STATUS: Compilation Successful\n");
    printf("BENCHMARK - Execution Time: %.4f ms\n", time_ms);
    printf("BENCHMARK - Constraint: Simulated Embedded Memory (Fixed Stack)\n");
    printf("-----------------------------------\n");

    fclose(source);
    return 0;
}