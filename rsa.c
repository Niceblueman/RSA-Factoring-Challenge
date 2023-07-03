#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_prime(int num) {
    if (num < 2)
        return 0;

    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0)
            return 0;
    }

    return 1;
}

int factor(int num) {
    if (num < 2)
        return num;

    for (int i = 2; i <= num; i++) {
        if (num % i == 0 && is_prime(i))
            return i;
    }

    return num;
}

void print_factors(int* numbers, int size) {
    for (int i = 0; i < size; i++) {
        int number = numbers[i];
        int prime_factor = factor(number);

        printf("%d=%d*%d\n", number, number / prime_factor, prime_factor);
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2)
        exit(1);

    FILE* file = fopen(argv[1], "r");
    if (file == NULL)
        exit(1);

    int capacity = 10;
    int* numbers = malloc(capacity * sizeof(int));
    int count = 0;

    char line[100];
    while (fgets(line, sizeof(line), file)) {
        int number = atoi(line);

        if (count == capacity) {
            capacity *= 2;
            numbers = realloc(numbers, capacity * sizeof(int));
        }

        numbers[count++] = number;
    }

    fclose(file);

    print_factors(numbers, count);

    free(numbers);

    return 0;
}
