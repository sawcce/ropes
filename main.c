#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 2
char *string_repeat(int n, const char *s) {
  size_t slen = strlen(s);
  char *dest = malloc(n * slen + 1);

  int i;
  char *p;
  for (i = 0, p = dest; i < n; ++i, p += slen) {
    memcpy(p, s, slen);
  }
  *p = '\0';
  return dest;
}
typedef struct Node {
  int count;
  char *text;
  struct Node *left, *right, *parent;
} Node;

Node *leaf(const char *text) {
  Node *node = malloc(sizeof(Node));

  node->count = strlen(text);
  node->text = malloc(strlen(text));
  node->left = (void *)0;
  node->right = NULL;

  strcpy_s(node->text, sizeof(text), text);

  return node;
}

void say(Node *node);

Node *node(Node *left, Node *right) {
  Node *node = malloc(sizeof(Node));
  if (left->left != NULL && left->right != NULL) {
    node->count = left->left->count + left->right->count;
  } else {
    printf("Left: %s\n", left->text);
    node->count = left->count;
  }

  node->left = left;
  node->right = right;
  return node;
}

void say(Node *node) {
  char *text = "NULL";

  // if (node->text != NULL && strlen(node->text) != 0) {
  //  text = node->text;
  // }

  printf("Node ( text: %s, left: %i, right: %i, count: %d )\n", text,
         node->left != NULL, node->right != NULL, node->count);
}

void make_str(Node *root) {
  if (root->left == NULL && root->right == NULL) {
    printf("%s", root->text);
    return;
  }

  if (root->left != NULL) {
    make_str(root->left);
  }

  if (root->right != NULL) {
    make_str(root->right);
  }
}

Node *makeTree(Node *inputs, int len) {
  int middle = len / 2;
  int rest = len - middle;

  printf("Step: %d, %d!\n", len, middle);
  if (len > 3) {
    Node *left = makeTree(inputs, middle);
    Node *right = makeTree(&inputs[middle], rest);
    Node *res = node(left, right);
    printf("Stepped: %d, %d!\n", len, middle);
    return res;
  } else if (len == 3) {
    Node *left = makeTree(inputs, 2);
    Node *right = makeTree(inputs + 2, 1);
    Node *res = node(left, right);
    return res;
  } else {
    printf("Reached bottom!\n");

    Node *left = NULL;
    Node *right = NULL;

    if (inputs != NULL) {
      left = malloc(sizeof(Node));
      left = leaf(inputs[0].text);
    }

    if (len == 2 && inputs + 1 != NULL) {
      right = malloc(sizeof(Node));
      right = leaf(inputs[1].text);
    }

    return node(left, right);
  }
}

Node *makeBase(char *input) {
  int number_of_it = (int)(strlen(input) / MAX_LEN);

  if (strlen(input) % 2 != 0) {
    number_of_it += 10;
  }

  int len = strlen(input);

  if (len % 2 != 0) {
    len += 3;
  }

  Node *leaves = malloc((number_of_it) * sizeof(Node));
  printf("Num of it %d\n", number_of_it);

  int x = 0;
  for (int i = 0; i < len; i += MAX_LEN) {
    char output[MAX_LEN + 1];
    strncpy(output, input + i, MAX_LEN);
    leaves[x] = *leaf(output);
    x++;
  }

  return leaves;
}

void visTree(Node *node, int tab) {
  printf("%s", string_repeat(tab, " "));
  say(node);

  if (node->left != NULL) {

    visTree(node->left, tab + 2);
  }

  if (node->right != NULL) {
    visTree(node->right, tab + 2);
  }
}

int main() {
  // char *input = "def main:\n  print('Hello world!)";
  char *input = "aaBBccDDeef";

  int number_of_it = (int)(strlen(input) / MAX_LEN);
  Node *base = makeBase(input);

  for (int i = 0; i < number_of_it; i++) {
    say(&base[i]);
  }

  puts("\n \nTREE\n\n");
  printf("%d\n", number_of_it);

  Node *tree = makeTree(base, number_of_it);
  puts("Done building!");
  printf("%d\n", tree->count);
  visTree(tree, 0);

  puts("Result!");
  make_str(tree);

  /*
  puts("Ropes!");
  Node *first_str = leaf("He");
  Node *second_str = leaf("ll");

  Node *third_str = leaf("o!");
  puts("Made leaves!");

  Node *bottom_left = node(first_str, second_str);
  Node *bottom_right = node(third_str, NULL);
  puts("Made bottom nodes!");

  Node *root = node(bottom_left, bottom_right);

  // printf("%d", bottom_left->count);

  make_str(root);*/
  printf("\n\n");
  return 0;
}
