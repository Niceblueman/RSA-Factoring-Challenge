#include <stdio.h>
#include <stdlib.h>

int is_prime(int num) {
    if (num < 2)
        return 0;
    
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0)
            return 0;
    }
    
    return 1;
}

int* factors(int num, int* size) {
    int capacity = 10;
    int* factors_list = malloc(capacity * sizeof(int));
    int count = 0;
    
    for (int i = 2; i <= num; i++) {
        if (num % i == 0 && is_prime(i)) {
            factors_list[count++] = i;
            
            if (count == capacity) {
                capacity *= 2;
                factors_list = realloc(factors_list, capacity * sizeof(int));
            }
        }
    }
    
    *size = count;
    return factors_list;
}

int main(int argc, char* argv[]) {
    if (argc != 2)
        exit(1);
    
    FILE* file = fopen(argv[1], "r");
    if (file == NULL)
        exit(1);
    
    int* lpi = NULL;
    int lpi_size = 0;
    char line[100];
    
    while (fgets(line, sizeof(line), file)) {
        int num = atoi(line);
        lpi = realloc(lpi, (lpi_size + 1) * sizeof(int));
        lpi[lpi_size++] = num;
    }
    
    fclose(file);
    
    for (int i = 0; i < lpi_size; i++) {
        int* factors_list;
        int factors_size;
        
        factors_list = factors(lpi[i], &factors_size);
        
        if (factors_size > 0) {
            printf("%d=%d*%d\n", lpi[i], lpi[i] / factors_list[0], factors_list[0]);
        }
        
        free(factors_list);
    }
    
    free(lpi);
    
    return 0;
}
