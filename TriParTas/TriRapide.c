#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void printArrayTriRapide(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void writeCSV(const char *filename, const int sizes[], const double times[], int numTests)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("Error opening file %s\n", filename);
        return;
    }

    fprintf(file, "Size,Sort Time (s)\n");
    for (int i = 0; i < numTests; i++)
    {
        fprintf(file, "%d,%.6f\n", sizes[i], times[i]);
    }
    fclose(file);
}

void executeQuickSort(int size)
{
    int *arr = (int *)malloc(size * sizeof(int));
    if (arr == NULL)
    {
        printf("Memory allocation failed\n");
        return;
    }

    srand(time(0));
    for (int i = 0; i < size; i++)
    {
        arr[i] = rand() % 100;
    }

    printf("Initial array: \n");
    printArrayTriRapide(arr, size);

    quickSort(arr, 0, size - 1);

    printf("Sorted array: \n");
    printArrayTriRapide(arr, size);

    free(arr);
}

void testQuickSortAndGenerateCSV()
{
    int sizes[] = {1000, 5000, 10000, 50000, 100000};
    int numTests = sizeof(sizes) / sizeof(sizes[0]);
    double times[numTests];

    for (int i = 0; i < numTests; i++)
    {
        int size = sizes[i];
        int *arr = (int *)malloc(size * sizeof(int));
        if (arr == NULL)
        {
            printf("Memory allocation failed\n");
            return;
        }

        srand(time(0));
        for (int j = 0; j < size; j++)
        {
            arr[j] = rand() % 10000;
        }

        clock_t start = clock();
        quickSort(arr, 0, size - 1);
        clock_t end = clock();
        times[i] = ((double)(end - start)) / CLOCKS_PER_SEC;

        free(arr);
    }

    writeCSV("quick_sort_results.csv", sizes, times, numTests);
}

int displayMenuTriRapide()
{
    int choice;
    printf("Menu:\n");
    printf("1. Execute quick sort with a specified array size\n");
    printf("2. Test quick sort with different array sizes and generate CSV file\n");
    printf("3. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    return choice;
}

void TriRapide()
{
    int choice;
    while (choice != 3)
    {
        choice = displayMenuTriRapide();
        switch (choice)
        {
        case 1:
        {
            int size;
            printf("Enter the size of the array: ");
            scanf("%d", &size);
            executeQuickSort(size);
            break;
        }
        case 2:
            testQuickSortAndGenerateCSV();
            break;
        case 3:
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }
}