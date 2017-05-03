#include "global.h"


struct BreakNode
{
	int layer, pc;
	struct BreakNode* next;
};

struct BreakNode* top = NULL;
int current_layer = 0;

int pop_top(int pop_layer)
{
	if (top == NULL || top->layer != pop_layer) return -1;
	struct BreakNode* nextTop = top->next;
	int nodePc = top->pc;
	delete top;
	top = nextTop;
	return nodePc;
}

void push_top(int pc)
{
	struct BreakNode* nextTop = new BreakNode();
	nextTop->next = top;
	nextTop->pc = pc;
	nextTop->layer = current_layer;
	top = nextTop;
}

