#include "binary_trees.h"
#include <stdlib.h>

/**
 * swap - Swap the values of two nodes
 * @a: First node
 * @b: Second node
 */
void swap(heap_t *a, heap_t *b)
{
	int temp = a->n;
	a->n = b->n;
	b->n = temp;
}

/**
 * heapify_down - Heapify down to maintain max heap property
 * @node: Pointer to the root node of the heap
 */
void heapify_down(heap_t *node)
{
	heap_t *largest = node;
	heap_t *left = node->left;
	heap_t *right = node->right;

	if (left && left->n > largest->n)
		largest = left;
	if (right && right->n > largest->n)
		largest = right;

	if (largest != node)
	{
		swap(node, largest);
		heapify_down(largest);
	}
}

/**
 * get_last_node - Gets the last node in level order traversal
 * @root: Pointer to the root node of the heap
 *
 * Return: Pointer to the last node
 */
heap_t *get_last_node(heap_t *root)
{
	if (!root)
		return (NULL);

	size_t height = 0, i;
	heap_t *queue[1024];
	size_t front = 0, back = 0;

	queue[back++] = root;

	while (front < back)
	{
		heap_t *node = queue[front++];

		if (node->left)
			queue[back++] = node->left;
		if (node->right)
			queue[back++] = node->right;

		height++;
	}

	return (queue[height - 1]);
}

/**
 * heap_extract - Extract the root node of a Max Binary Heap
 * @root: Double pointer to the root node of the heap
 *
 * Return: The value stored in the root node
 */
int heap_extract(heap_t **root)
{
	if (!root || !*root)
		return (0);

	heap_t *last_node = get_last_node(*root);
	int value = (*root)->n;

	if (*root == last_node)
	{
		free(*root);
		*root = NULL;
		return (value);
	}

	(*root)->n = last_node->n;

	if (last_node->parent->left == last_node)
		last_node->parent->left = NULL;
	else
		last_node->parent->right = NULL;

	free(last_node);
	heapify_down(*root);

	return (value);
}
