#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26
#define NAME_SIZE 50
#define TRUE 1

typedef struct s_trienode
{
	struct s_trienode	*child[ALPHABET_SIZE];
	char				string[NAME_SIZE];
}	trienode;

typedef struct s_trietree
{
	trienode	*root;
}	trietree;

trienode	*create_node(void)
{
	trienode	*node = (trienode *)malloc(sizeof(trienode));
	node->string[0] = '\0';
	for (int i = 0; i < ALPHABET_SIZE; i++)
		node->child[i] = NULL;
	return (node);
}

int	char_to_index(char c)
{
	return (c - 'a');
}

void	insert(trienode *root, const char *key)
{
	trienode	*current;
	int			index;

	current = root;
	for (int i = 0; i < (int)strlen(key); i++)
	{
		index = char_to_index(key[i]);
		if (current->child[index] == NULL)
			current->child[index] = create_node();
		current = current->child[index];
	}
	for (int i = 0; i <= (int)strlen(key); i++)
		current->string[i] = key[i];
	printf("Inserting done: '%s'\n", key);
}

trienode	*search(trienode *root, const char *key)
{
	trienode	*current;
	int			index;

	current = root;
	for (int i = 0; i < (int)strlen(key); i++)
	{
		index = char_to_index(key[i]);
		if (current->child[index] != NULL)
			current = current->child[index];
		else
		{
			printf("OOPS.. there is no word started with '%s'\n", key);
			return (NULL);
		}
	}
	if (current->string[0] != '\0')
		return (current);
	for (int i = 0; i < ALPHABET_SIZE; i++)
	{
		if (current->child[i] != NULL)
		{
			current = current->child[i];
			if (current->string[0] != '\0')
				return (current);
			i = 0;
		}
	}
	return (NULL);
}

void	delete(trienode *node, trietree *tree)
{
	if (node == NULL)
		return ;
	for (int i = 0; i < ALPHABET_SIZE; i++)
		delete(node->child[i], tree);
	if (node != tree->root)
		free(node);
}

void	init_tiretree(trietree *tree)
{
	tree->root = create_node();
	return ;
}

int	select_number(void)
{
	int	value;
	printf("1. Insert string\n");
	printf("2. Search string\n");
	printf("3. Clean data\n");
	printf("4. EXIT\n\n");
	printf("Select number: ");
	scanf("%d", &value);
	return (value);
}

void	insert_string(trienode *root)
{
	char	input[NAME_SIZE];
	printf("insert string: ");
	scanf("%s", input);
	insert(root, input);
	return ;
}

void	search_string(trienode *root)
{
	char		input[NAME_SIZE];
	trienode	*search_result;
	printf("insert string: ");
	scanf("%s", input);
	search_result = search(root, input);
	if (search_result == NULL)
		printf("There is no word start with '%s'\n", input);
	else
		printf("I think you want this: %s\n", search_result->string);
	return ;
}

void	clean_data(trienode *root, trietree *tree)
{
	delete(root, tree);
	printf("Clean done\n");
}

void 	quit_program(trienode *root, trietree *tree)
{
	clean_data(root, tree);
	printf("EXIT DONE...\n");
	exit(0);
}

int	main(void)
{
	int			input;
	trietree	tree;

	init_tiretree(&tree);
	printf("TRIE STARTED..\n");
	while (TRUE)
	{
		input = select_number();
		if (input == 1)
			insert_string(tree.root);
		else if (input == 2)
			search_string(tree.root);
		else if (input == 3)
			clean_data(tree.root, &tree);
		else if (input == 4)
			quit_program(tree.root, &tree);
		printf("=== === === === === === ===\n\n");
	}
	return (0);
}