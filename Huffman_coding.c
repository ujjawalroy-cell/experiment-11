
#include <stdio.h>                         //Ujjawal roy       
#include <stdlib.h>                        // 25/DA/061    
#include <string.h>
                                                
#define MAX 100

struct Node {
    char ch;
    int freq;
    struct Node *left, *right;
};

struct Node* createNode(char ch, int freq) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));

    node->ch = ch;
    node->freq = freq;
    node->left = node->right = NULL;

    return node;
}

void swap(struct Node** a, struct Node** b) {
    struct Node* temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(struct Node* heap[], int n, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && heap[left]->freq < heap[smallest]->freq)
        smallest = left;

    if (right < n && heap[right]->freq < heap[smallest]->freq)
        smallest = right;

    if (smallest != i) {
        swap(&heap[i], &heap[smallest]);
        minHeapify(heap, n, smallest);
    }
}

void buildMinHeap(struct Node* heap[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        minHeapify(heap, n, i);
}

struct Node* extractMin(struct Node* heap[], int *n) {
    struct Node* min = heap[0];
    heap[0] = heap[*n - 1];
    (*n)--;

    if (*n > 0)
        minHeapify(heap, *n, 0);

    return min;
}

void insertHeap(struct Node* heap[], int *n, struct Node* node) {
    int i = (*n)++;
    heap[i] = node;

    while (i > 0 && heap[(i - 1) / 2]->freq > heap[i]->freq) {
        swap(&heap[i], &heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void printCodes(struct Node* root, int code[], int top) {
    if (root->left) {
        code[top] = 0;
        printCodes(root->left, code, top + 1);
    }

    if (root->right) {
        code[top] = 1;
        printCodes(root->right, code, top + 1);
    }

    if (!root->left && !root->right) {
        printf("%c\t", root->ch);

        for (int i = 0; i < top; i++)
            printf("%d", code[i]);

        if (top == 0)
            printf("0");

        printf("\n");
    }
}

struct Node* buildHuffmanTree(char chars[], int freq[], int n) {
    struct Node* heap[MAX];

    for (int i = 0; i < n; i++)
        heap[i] = createNode(chars[i], freq[i]);

    buildMinHeap(heap, n);

    while (n > 1) {
        struct Node* left = extractMin(heap, &n);
        struct Node* right = extractMin(heap, &n);

        struct Node* parent = createNode('$',
                                         left->freq + right->freq);

        parent->left = left;
        parent->right = right;

        insertHeap(heap, &n, parent);
    }

    return heap[0];
}

int main() {
    int n;
    char chars[MAX];
    int freq[MAX];
    int code[MAX];

    printf("Enter number of characters: ");
    scanf("%d", &n);

    if (n < 1 || n > MAX) {
        printf("Invalid number of characters.\n");
        return 1;
    }

    printf("Enter characters:\n");
    for (int i = 0; i < n; i++)
        scanf(" %c", &chars[i]);

    printf("Enter frequencies:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &freq[i]);

        if (freq[i] <= 0) {
            printf("Frequencies must be positive.\n");
            return 1;
        }
    }

    struct Node* root = buildHuffmanTree(chars, freq, n);

    printf("\nCharacter\tHuffman Code\n");
    printCodes(root, code, 0);

    return 0;
}
