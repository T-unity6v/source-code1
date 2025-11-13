#include <stdio.h>
#include <stdbool.h>

// 配列の中身を出力する関数
void Print(int A[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", A[i]);
    }
    printf("\n");
}

// 与えられた値をswapする関数
void swap(int *x, int *y)
{
    int a = *x;
    *x = *y;
    *y = a;
}

// バブルソート（通常版）
void bubbleSort_basic(int A[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - 1 - i; j++)
        {
            if (A[j] > A[j + 1])
            {
                swap(&A[j], &A[j + 1]);
            }
        }
    }
}

// バブルソート（改良版）
void bubbleSort_optimized(int A[], int n)
{
    // 交換が行われたかを判別する変数
    bool flag = false;

    for (int i = 0; i < n - 1; i++)
    {
        flag = false;
        for (int j = 0; j < n - 1; j++)
        {
            if (A[j] > A[j + 1])
            {
                swap(&A[j], &A[j + 1]);
                flag = true;
            }
        }
        // もし一度も交換が行わなければ終了
        if (!flag)
        {
            return;
        }
    }
}

// 選択ソート
void selectionSort(int A[], int n)
{
    // 最小値をメモする変数
    int MIN = 0;
    // 最小値が格納されている配列番号をメモする変数
    int num = 0;
    for (int i = 0; i < n - 1; i++)
    {
        MIN = A[i];
        num = i;
        for (int j = i + 1; j < n; j++)
        {
            if (MIN > A[j])
            {
                MIN = A[j];
                num = j;
            }
        }
        A[num] = A[i];
        A[i] = MIN;
    }
}

// 挿入ソート
void insertionSort(int A[], int n)
{
    for (int i = 1; i < n; i++)
    {
        for (int j = i; j > 0; j--)
        {
            if (A[j - 1] > A[j])
            {
                swap(&A[j], &A[j - 1]);
            }
        }
    }
}

// 分割された部分列をソートする関数
void merge(int A[], int left, int mid, int right)
{
    // 左右の配列のサイズを表す変数
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // 配列をコピー
    int L[n1], R[n2];
    for (int i = 0; i < n1; i++)
        L[i] = A[left + i];
    for (int i = 0; i < n2; i++)
        R[i] = A[mid + 1 + i];

    // 2つの配列をソートしながら結合
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            A[k] = L[i];
            i++;
        }
        else
        {
            A[k] = R[j];
            j++;
        }
        k++;
    }

    // Aの配列に移す
    while (i < n1)
    {
        A[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        A[k] = R[j];
        j++;
        k++;
    }
}

// マージソート
void mergeSort(int A[], int left, int right)
{
    // 要素数が1になるとreturn
    if (left >= right)
        return;

    int mid;
    mid = (left + right) / 2;

    mergeSort(A, left, mid);
    mergeSort(A, mid + 1, right);

    // 結合する
    merge(A, left, mid, right);
}

// 基準との大小関係で2分割する関数
int partition(int A[], int left, int right)
{
    // ピボットを右端に仮置き
    int k = (left + right) / 2;
    swap(&A[k], &A[right]);

    int i = left;
    int j = right - 1;

    // 左側がピボット以下、右側がピボット以上になるように分割
    while (i <= j)
    {
        while (A[i] < A[right])
            i++;
        while ((A[j] >= A[right]) && (j >= i))
            j--;
        if (i < j)
            swap(&A[i], &A[j]);
    }

    // ピボットを適切な位置に配置
    swap(&A[i], &A[right]);
    return i;
}

// クイックソート
void quickSort(int A[], int left, int right)
{
    if (left < right)
    {
        int pivot_index = partition(A, left, right);

        quickSort(A, left, pivot_index - 1);
        quickSort(A, pivot_index + 1, right);
    }
}

// 最大ヒープ構造に変換する関数
void heapify(int A[], int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && A[left] > A[largest])
        largest = left;

    if (right < n && A[right] > A[largest])
        largest = right;

    if (largest != i)
    {
        swap(&A[i], &A[largest]);
        heapify(A, n, largest);
    }
}

// heapifyを繰り返す関数
void buildHeap(int A[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heapify(A, n, i);
    }
}

// ヒープソート
void heapSort(int A[], int n)
{
    buildHeap(A, n);

    for (int i = n - 1; i > 0; i--)
    {
        swap(&A[0], &A[i]);
        heapify(A, i, 0);
    }
}

int main(void)
{
    int n = 10;
    int x[10] = {9, 2, 5, 1, 8, 4, 6, 0, 7, 3};
    int y[10];

    printf("---ソート前の配列---\n");
    Print(x, n);

    for (int i = 0; i < n; i++)
        y[i] = x[i];
    bubbleSort_basic(y, n);
    printf("---バブルソート（通常版）結果---\n");
    Print(y, n);

    for (int i = 0; i < n; i++)
        y[i] = x[i];
    bubbleSort_optimized(y, n);
    printf("---バブルソート（改良版）結果---\n");
    Print(y, n);

    for (int i = 0; i < n; i++)
        y[i] = x[i];
    selectionSort(y, n);
    printf("---選択ソート結果---\n");
    Print(y, n);

    for (int i = 0; i < n; i++)
        y[i] = x[i];
    insertionSort(y, n);
    printf("---挿入ソート結果---\n");
    Print(y, n);

    for (int i = 0; i < n; i++)
        y[i] = x[i];
    mergeSort(y, 0, n - 1);
    printf("---マージソート結果---\n");
    Print(y, n);

    for (int i = 0; i < n; i++)
        y[i] = x[i];
    quickSort(y, 0, n - 1);
    printf("---クイックソート結果---\n");
    Print(y, n);

    for (int i = 0; i < n; i++)
        y[i] = x[i];
    heapSort(y, n);
    printf("---ヒープソート結果---\n");
    Print(y, n);
}
