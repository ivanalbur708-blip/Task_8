#include <iostream>
using namespace std;

bool Contains(const int* array, int size, int value)
{
    for (int i = 0; i < size; i++)
        if (array[i] == value)
            return true;

    return false;
}

void PrintArray(const int* array, int size)
{
    for (int i = 0; i < size; i++)
        cout << array[i] << ' ';
    cout << '\n';
}

int* MergeArrays(const int* A, int M, const int* B, int N)
{
    int* result = new int[M + N];

    for (int i = 0; i < M; i++)
        result[i] = A[i];

    for (int i = 0; i < N; i++)
        result[M + i] = B[i];

    return result;
}


int* CommonElements(const int* A, int M, const int* B, int N,
    int& resultSize)
{
    resultSize = 0;

    for (int i = 0; i < M; i++)
    {
        if (!Contains(B, N, A[i]))
            continue;

        bool seenEarlier = false;
        for (int j = 0; j < i; j++)
            if (A[j] == A[i])
                seenEarlier = true;

        if (!seenEarlier)
            resultSize++;
    }

    int* result = new int[resultSize];
    int index = 0;

    for (int i = 0; i < M; i++)
        if (Contains(B, N, A[i]) && !Contains(result, index, A[i]))
            result[index++] = A[i];

    return result;
}

int* FilterParity(const int* A, int M, bool removeEven, int& resultSize)
{
    resultSize = 0;

    for (int i = 0; i < M; i++)
    {
        bool isEven = A[i] % 2 == 0;
        if (isEven != removeEven)
            resultSize++;
    }

    int* result = new int[resultSize];
    int index = 0;

    for (int i = 0; i < M; i++)
    {
        bool isEven = A[i] % 2 == 0;
        if (isEven != removeEven)
            result[index++] = A[i];
    }

    return result;
}

int main()
{
    int M, N;
    cout << "Enter M and N: ";
    cin >> M >> N;

    if (!cin || M < 0 || N < 0)
    {
        cout << "Invalid sizes\n";
        return 1;
    }

    int* A = new int[M];
    int* B = new int[N];

    cout << "Enter array A: ";
    for (int i = 0; i < M; i++) {
        cin >> A[i];
    }
    cout << "Enter array B: ";
    for (int i = 0; i < N; i++) {
        cin >> B[i];
    }

    // Task 1
    int mergedSize = M + N;
    int* merged = MergeArrays(A, M, B, N);
    cout << "Merged array: ";
    PrintArray(merged, mergedSize);

    // Task 2
    int commonSize;
    int* common = CommonElements(A, M, B, N, commonSize);
    cout << "Common elements: ";
    PrintArray(common, commonSize);

    // Task 3
    int choice;
    cout << "1: remove even, 2: remove odd: ";
    cin >> choice;

    if (choice == 1 || choice == 2)
    {
        int filteredSize;
        int* filtered = FilterParity(A, M, choice == 1, filteredSize);

        delete[] A;
        A = filtered;
        M = filteredSize;

        cout << "Filtered array: ";
        PrintArray(A, M);
    }
    else
    {
        cout << "Invalid choice\n";
    }

    delete[] A;
    delete[] B;
    delete[] merged;
    delete[] common;
    return 0;
}
