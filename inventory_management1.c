/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inventory_management1.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehejun <jaehejun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 16:43:26 by jaehejun          #+#    #+#             */
/*   Updated: 2023/06/26 21:31:24 by jaehejun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_stock
{
	char	*store;
	char	*size;
	int		count;
}	t_stock;

typedef struct s_product
{
	int					item_number;
	char				*name;
	int					price;
	t_stock				*online_stock;
	t_stock				*Gangnam_stock;
	t_stock				*Samsung_stock;
	t_stock				*Jamsil_stock;
	struct s_product	*left;
	struct s_product	*right;
	int					height;
}	t_product;

// Function to create a new stock entry
t_stock	*create_stock(char *store, char *size, int count)
{
	t_stock	*new_stock = (t_stock *)malloc(sizeof(t_stock));
	new_stock -> store = strdup(store);
	new_stock -> size = strdup(size);
	new_stock -> count = count;
	return (new_stock);
}

// Function to create a new product entry
t_product	*create_product(int item_number, char *name, int price, t_stock *online_stock, t_stock *Gangnam_stock, t_stock *Samsung_stock, t_stock *Jamsil_stock)
{
	t_product	*new_product = (t_product *)malloc(sizeof(t_product));
	new_product -> item_number = item_number;
	new_product -> name = strdup(name);
	new_product -> price = price;
	new_product -> online_stock = online_stock;
	new_product -> Gangnam_stock = Gangnam_stock;
	new_product -> Samsung_stock = Samsung_stock;
	new_product -> Jamsil_stock = Jamsil_stock;
	new_product -> left = NULL;
	new_product -> right = NULL;
	new_product -> height = 1;
	return (new_product);
}

// Function to get the height of a node
int	get_height(t_product *node)
{
	if (node == NULL)
		return (0);
	return (node -> height);
}

// Function to update the height of a node
void	update_height(t_product *node)
{
	if (node == NULL)
		return ;
	int	left_height = get_height(node -> left);
	int	right_height = get_height(node -> right);
	if (left_height > right_height)
		node -> height = left_height + 1;
	else
		node -> height = right_height + 1;
}

// Function to perform a right rotation
t_product	*rotate_right(t_product *y)
{
	t_product	*x = y -> left;
	t_product	*T2 = x -> right;
	x -> right = y;
	y -> left = T2;
	update_height(y);
	update_height(x);
	return (x);
}

//Function to perform a left rotation
t_product	*rotate_left(t_product *x)
{
	t_product	*y = x -> right;
	t_product	*T2 = y -> left;
	y -> left = x;
	x -> right = T2;
	update_height(x);
	update_height(y);
	return (y);
}

// Function to balance the AVL tree
t_product	*balance_tree(t_product *node, int item_number)
{
	update_height(node);
	int	balance_factor = get_height(node -> left) - get_height(node -> right);
	if (balance_factor > 1 && item_number < node -> left -> item_number)
		return (rotate_right(node));
	if (balance_factor < -1 && item_number > node -> right -> item_number)
		return (rotate_left(node));
	if (balance_factor > 1 && item_number > node -> left -> item_number)
	{
		node -> left = rotate_left(node -> left);
		return (rotate_right(node));
	}
	if (balance_factor < -1 && item_number < node -> right -> item_number)
	{
		node -> right = rotate_right(node -> right);
		return (rotate_left(node));
	}
	return (node);
}

// Function to insert a product into the AVL tree
t_product	*insert_product(t_product *node, int item_number, char *name, int price, t_stock *online_stock, t_stock *Gangnam_stock, t_stock *Samsung_stock, t_stock *Jamsil_stock)
{
	if (node == NULL)
		return(create_product(item_number, name, price, online_stock, Gangnam_stock, Samsung_stock, Jamsil_stock));
	if (item_number < node -> item_number)
		node -> left = insert_product(node -> left, item_number, name, price, online_stock, Gangnam_stock, Samsung_stock, Jamsil_stock);
	else if (item_number > node -> item_number)
		node -> right = insert_product(node -> right, item_number, name, price, online_stock, Gangnam_stock, Samsung_stock, Jamsil_stock);
	else
		return (node);
	update_height(node);
	return (balance_tree(node, item_number));
}

// Function to search for a product int the AVL tree
t_product	*search_product(t_product *node, int item_number)
{
	if (node == NULL || node -> item_number == item_number)
		return (node);
	if (item_number < node -> item_number)
		return (search_product(node -> left, item_number));
	return (search_product(node -> right, item_number));
}

// Funtion to check if there is enought stock for a product
void	check_stock_availability(t_product *node, int item_number, char	*size)
{
	if (node == NULL)
	{
		printf("No result for %d\n", item_number);
		return ;
	}
	if (node ->item_number == item_number)
	{
		t_stock	*stock;
		if (strcmp(size, node -> online_stock -> size) == 0)
		{
			stock = node -> online_stock;
			printf("%d\n", stock -> count);
			return ;
		}
		else if (strcmp(size, node -> Gangnam_stock -> size) == 0)
		{
			stock = node -> Gangnam_stock;
			printf("Location: Gangnam, %d\n", stock -> count);
			return ;
		}
		else if (strcmp(size, node -> Samsung_stock -> size) == 0)
		{
			stock = node -> Samsung_stock;
			printf("Location: Samsung, %d\n", stock -> count);
			return ;
		}
		else if (strcmp(size, node -> Jamsil_stock -> size) == 0)
		{
			stock = node -> Jamsil_stock;
			printf("Location: Jamsil, %d\n", stock -> count);
			return ;
		}
		else
		{
			printf("ELSE STATEMENT - No result for %d\n", item_number);
			return ;
		}
	}
	if (item_number < node -> item_number)
		check_stock_availability(node -> left, item_number, size);
	else
		check_stock_availability(node -> right, item_number, size);
}

// Function to free memory allocated for the AVL tree
void	free_tree(t_product *node)
{
	if (node == NULL)
		return ;
	free_tree(node -> left);
	free_tree(node -> right);
	free(node -> name);
	free(node -> online_stock -> store);
	free(node -> online_stock -> size);
	free(node -> online_stock);
	free(node -> Gangnam_stock -> store);
	free(node -> Gangnam_stock -> size);
	free(node -> Gangnam_stock);
	free(node -> Samsung_stock -> store);
	free(node -> Samsung_stock -> size);
	free(node -> Samsung_stock);
	free(node -> Jamsil_stock -> store);
	free(node -> Jamsil_stock -> size);
	free(node -> Jamsil_stock);
	free(node);
}

int	main(void)
{
	t_product	*root = NULL;
	
	// Adding products to the inventory
	t_stock	*online_stock1 = create_stock("Online", "S", 10);
	t_stock	*Gangnam_stock1 = create_stock("Gangnam", "M", 5);
	t_stock	*Samsung_stock1 = create_stock("Samsung", "L", 2);
	t_stock	*Jamsil_stock1 = create_stock("Jamsil", "M", 8);
	root = insert_product(root, 4164416, "POPLIN CARGO PANTS", 10, online_stock1, Gangnam_stock1, Samsung_stock1, Jamsil_stock1);

	t_stock	*online_stock2 = create_stock("Online", "S", 10);
	t_stock	*Gangnam_stock2 = create_stock("Gangnam", "M", 5);
	t_stock	*Samsung_stock2 = create_stock("Samsung", "L", 2);
	t_stock	*Jamsil_stock2 = create_stock("Jamsil", "M", 8);
	root = insert_product(root, 4164417, "PLEATED TECHNICAL TROUSERS", 10, online_stock2, Gangnam_stock2, Samsung_stock2, Jamsil_stock2);
	
	t_stock	*online_stock3 = create_stock("Online", "S", 10);
	t_stock	*Gangnam_stock3 = create_stock("Gangnam", "M", 5);
	t_stock	*Samsung_stock3 = create_stock("Samsung", "L", 2);
	t_stock	*Jamsil_stock3 = create_stock("Jamsil", "M", 8);
	root = insert_product(root, 4164418, "DENIM RUSTIC SHIRT - LIMITED EDITION", 10, online_stock3, Gangnam_stock3, Samsung_stock3, Jamsil_stock3);

	// Searching for a product and checking stock availability
	int	item_number = 4164416;
	char	size[3] = "M";
	t_product	*product = search_product(root, item_number);
	if (product != NULL)
	{
		check_stock_availability(root, item_number, size);
	}
	else
		printf("No result for %d\n", item_number);
	
	// Freeing memory allocated for the AVL tree
	free_tree(root);

	return (0);
}
