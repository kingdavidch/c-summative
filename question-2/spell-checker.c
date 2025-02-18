#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TreeNode {
    char word[100];
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// Function to create a new tree node
TreeNode* createTreeNode(const char* word) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    strcpy(newNode->word, word);
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to insert a word into the BST
TreeNode* insertWord(TreeNode* root, const char* word) {
    if (root == NULL) {
        return createTreeNode(word);
    }
    if (strcmp(word, root->word) < 0) {
        root->left = insertWord(root->left, word);
    } else if (strcmp(word, root->word) > 0) {
        root->right = insertWord(root->right, word);
    }
    return root;
}

// Function to search for a word in the BST
TreeNode* searchWord(TreeNode* root, const char* word) {
    if (root == NULL || strcmp(root->word, word) == 0) {
        return root;
    }
    if (strcmp(word, root->word) < 0) {
        return searchWord(root->left, word);
    } else {
        return searchWord(root->right, word);
    }
}

// Function to suggest similar words (basic implementation)
void suggestSimilarWords(TreeNode* root, const char* word) {
    if (root == NULL) return;
    if (strstr(root->word, word) != NULL) {
        printf("%s ", root->word);
    }
    suggestSimilarWords(root->left, word);
    suggestSimilarWords(root->right, word);
}

int main() {
    TreeNode* root = NULL;

    // Load dictionary (example words)
    char dictionary[][100] = {"apple", "banana", "cherry", "grape", "orange"};
    for (int i = 0; i < 5; i++) {
        root = insertWord(root, dictionary[i]);
    }

    char input[100];
    printf("Enter a word to check: ");
    scanf("%s", input);

    TreeNode* result = searchWord(root, input);
    if (result != NULL) {
        printf("Word found: %s\n", result->word);
    } else {
        printf("Word not found. Suggestions: ");
        suggestSimilarWords(root, input);
        printf("\n");
    }

    return 0;
}
