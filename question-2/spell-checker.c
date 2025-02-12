#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>  // Ensure this is included

typedef struct BSTNode {
    char word[50];
    struct BSTNode *left, *right;
} BSTNode;

BSTNode* insert(BSTNode *root, char *word) {
    if (!root) {
        BSTNode *newNode = (BSTNode*)malloc(sizeof(BSTNode));
        strcpy(newNode->word, word);
        newNode->left = newNode->right = NULL;
        return newNode;
    }
    int cmp = strcmp(word, root->word);
    if (cmp < 0) root->left = insert(root->left, word);
    else if (cmp > 0) root->right = insert(root->right, word);
    return root;
}

int search(BSTNode *root, char *word) {
    if (!root) return 0;
    int cmp = strcmp(word, root->word);
    if (cmp == 0) return 1;
    return cmp < 0 ? search(root->left, word) : search(root->right, word);
}

// Compute Levenshtein Distance
int levenshtein(char *s1, char *s2) {
    int len1 = strlen(s1), len2 = strlen(s2);
    int dp[len1 + 1][len2 + 1];

    for (int i = 0; i <= len1; i++)
        for (int j = 0; j <= len2; j++)
            dp[i][j] = (i == 0) ? j : (j == 0 ? i : 0);

    for (int i = 1; i <= len1; i++)
        for (int j = 1; j <= len2; j++)
            dp[i][j] = (s1[i - 1] == s2[j - 1]) ? dp[i - 1][j - 1]
                        : 1 + fmin(dp[i - 1][j], fmin(dp[i][j - 1], dp[i - 1][j - 1])); // FIXED!

    return dp[len1][len2];
}

// Find the closest word in BST
void suggest(BSTNode *root, char *word, char *bestMatch, int *minDist) {
    if (!root) return;
    int dist = levenshtein(word, root->word);
    if (dist < *minDist) {
        *minDist = dist;
        strcpy(bestMatch, root->word);
    }
    suggest(root->left, word, bestMatch, minDist);
    suggest(root->right, word, bestMatch, minDist);
}

int main() {
    BSTNode *root = NULL;
    FILE *dictFile = fopen("dictionary.txt", "r");
    if (!dictFile) {
        printf("Error: Dictionary file not found!\n");
        return 1;
    }

    char word[50];
    while (fscanf(dictFile, "%s", word) != EOF)
        root = insert(root, word);
    fclose(dictFile);

    printf("Enter a word: ");
    scanf("%s", word);

    if (search(root, word)) printf("Correct!\n");
    else {
        char bestMatch[50] = "";
        int minDist = 3;
        suggest(root, word, bestMatch, &minDist);
        if (minDist < 3) printf("Did you mean: %s?\n", bestMatch);
        else printf("No suggestions.\n");
    }
    return 0;
}
