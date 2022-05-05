#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <memory.h>

#define MAX_WORD_SIZE 100
#define MAX_MEANING_SIZE 200

typedef struct {
	char word[MAX_WORD_SIZE];
	char meaning[MAX_MEANING_SIZE];
} element;

typedef struct TreeNode {
	element key;
	struct TreeNode* left, * right;
} TreeNode;

int compare(element e1, element e2) {
	return strcmp(e1.word, e2.word);
}

void display(TreeNode* p) {
	if (p != NULL) {
		printf("(");
		display(p->left);
		printf("%s:%s", p->key.word, p->key.meaning);
		display(p->right);
		printf(")");
	}
}

TreeNode* search(TreeNode* root, element key) {
	TreeNode* p = root;
	while (p != NULL) {
		if (compare(key, p->key) == 0) return p;
		else if (compare(key, p->key) < 0) p = p->left;
		else if (compare(key, p->key) > 0) p = p->right;
	}
	return p;
}

TreeNode* new_node(element item) {
	TreeNode* p = (TreeNode*)malloc(sizeof(TreeNode));
	p->key = item;
	p->left = p->right = NULL;
	return p;
}

TreeNode* ins_node(TreeNode* node, element key) {
	if (node == NULL) return new_node(key);
	if (compare(key, node->key) < 0) node->left = ins_node(node->left, key);
	else if (compare(key, node->key) > 0) node->right = ins_node(node->right, key);
	return node;
}

TreeNode* min_value_node(TreeNode* node) {
	TreeNode* curr = node;
	while (curr->left != NULL) { curr = curr->left; }
	return curr;
}

TreeNode* del_node(TreeNode* node, element key) {
	if (node == NULL) return node;
	if (compare(key, node->key) < 0) node->left = del_node(node->left, key);
	if (compare(key, node->key) > 0) node->right = del_node(node->right, key);

	else {
		if (node->left == NULL) {
			TreeNode* p = node->right;
			free(node);
			return p;
		}
		else if (node->right == NULL) {
			TreeNode* p = node->left;
			free(node);
			return p;
		}
		TreeNode* p = min_value_node(node->right);
		node->key = p->key;
		node->right = del_node(node->right, p->key);
	}
	return node;
}

void help() {
	printf("\n**** i: 입력, d: 삭제, s: 탐색, p: 출력, q: 종료 ****: ");
}

int main() {
	char command;
	element e;
	TreeNode* root = NULL;
	TreeNode* tmp;

	do {
		help();
		command = getchar();
		getchar();
		switch (command) {
		case 'i':
			printf("단어: ");
			gets_s(e.word, MAX_WORD_SIZE);
			printf("의미: ");
			gets_s(e.meaning, MAX_MEANING_SIZE);
			root = ins_node(root, e);
			break;
		case 'd':
			printf("단어: ");
			gets_s(e.word, MAX_WORD_SIZE);
			root = del_node(root, e);
			break;
		case 'p':
			display(root);
			printf("\n");
			break;
		case 's':
			printf("단어: ");
			gets_s(e.word, MAX_WORD_SIZE);
			tmp = search(root, e);
			if (tmp != NULL) printf("의미: %s\n", tmp->key.meaning);
			else printf("%s is not found!\n", e.word);
			break;
		}
	} while (command != 'q');
	return 0;
}