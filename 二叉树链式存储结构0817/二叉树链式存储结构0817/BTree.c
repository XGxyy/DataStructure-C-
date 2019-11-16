#include "BTree.h"
#include "Queue.h"
#include "stack.h"

BTNode* BinaryTreeCreate(BTDataType* src){
	static int s_n = 0;
	if (src[s_n] == '#'){
		s_n++;
		return NULL;
	}
	BTNode* cur = (BTNode*)malloc(sizeof(BTNode));
	cur->data = src[s_n];
	s_n++;

	cur->lchild = BinaryTreeCreate(src);
	cur->rchild = BinaryTreeCreate(src);
	
	return cur;
}

//后序遍历销毁
void BinaryTreeDestory(BTNode* root){
	if (root){
		BinaryTreeDestory(root->lchild);
		BinaryTreeDestory(root->rchild);
		free(root);
	}
}

// 遍历
void BinaryTreePrevOrder(BTNode* root){
	if(root){
		putchar(root->data);
		BinaryTreePrevOrder(root->lchild);
		BinaryTreePrevOrder(root->rchild);
	}
}
void BinaryTreeInOrder(BTNode* root){
	if (root){
		BinaryTreeInOrder(root->lchild);
		putchar(root->data);
		BinaryTreeInOrder(root->rchild);
	}
}
void BinaryTreePostOrder(BTNode* root){
	if (root){
		BinaryTreePostOrder(root->lchild);
		BinaryTreePostOrder(root->rchild);
		putchar(root->data);
	}
}

//非递归遍历树
//先序
void BinartTreePrevOrderN(BTNode*root){
	Stack st;
	BTNode* cur = root;

	StackInit(&st, 100);
	while (cur){
		putchar(cur->data);//访问当前节点
		if (cur->rchild){//如果有右孩子，入栈
			StackPush(&st, cur->rchild);
		}

		if (cur->lchild){//如果有左孩子，访问之
			cur = cur->lchild;
		}
		else{//没有做孩子，访问栈顶
			cur = StackTop(&st);//取到空时跳出循环
			StackPop(&st);
		}
	}
	StackDestory(&st);
}

void BinaryTreeLevelOrder(BTNode* root){
	Queue qu;
	BTNode* cur;
	QueueInit(&qu);
	QueuePush(&qu, root);

	//借助队列完成，先将根节点入列

	while (QueueEmpty(&qu)){//队列为空跳出
		cur = QueueTop(&qu);
		putchar(cur->data);//打印队顶（队首）
		if (cur->lchild){
			QueuePush(&qu, cur->lchild);//如果有左孩子，入队
		}
		if (cur->rchild){
			QueuePush(&qu, cur->rchild);//右孩子入队
		}
		QueuePop(&qu);
	}

	QueueDestory(&qu);
}

int BinaryTreeSize(BTNode* root){
	Stack st;
	BTNode* cur = root;
	int size = 0;

	StackInit(&st, 100);
	while (cur){
		putchar(cur->data);
		size++;
		if (cur->rchild){
			StackPush(&st, cur->rchild);
		}

		if (cur->lchild){
			cur = cur->lchild;
		}
		else{
			cur = StackTop(&st);
			StackPop(&st);
		}
	}
	StackDestory(&st);
	return size;
}

void BinaryTreeInOrderN(BTNode* root){
	Stack st;
	BTNode* cur = root;

	StackInit(&st, 100);
	while (cur || !StackEmpty(&st)){
		for (; cur; cur = cur->lchild){//将当前节点以及左孩子入栈
			StackPush(&st, cur);
		}

		cur = StackTop(&st);
		//取栈顶 
		//1.如果右孩子为空，for循环不进，直接取栈顶（左子树访问完毕的情况）
		//2.如果右孩子不为空，那么只是一个没有左孩子的节点（左子树为空的情况）
		putchar(cur->data);
		StackPop(&st);
		cur = cur->rchild;//右子树为空时，检查栈是否为空
	}
	StackDestory(&st);
}

void BinaryTreePostOrderN(BTNode* root){
	char tag[64];

	Stack st;
	BTNode* cur = root;

	StackInit(&st, 100);
	do {
		for (; cur; cur = cur->lchild){//将当前节点及其左孩子入栈
			StackPush(&st, cur);
			tag[st.size - 1] = 0;//重置左子树访问标记（tag）
		}

		while (!StackEmpty(&st) && tag[st.size - 1]){//只有在循环跳出时生效
			//后面有两种情况：
			//1.当此次cur为空时，for循环不进，此条件成立
			//2.当cur不为空，for循环进，此条件不生效
			//若检测到当前tag被置为位（情况1），打印当前节点后，检查上一节点（父节点）是否也被打印
			cur = StackTop(&st);
			putchar(cur->data);
			StackPop(&st);
		}
		if (!StackEmpty(&st)){//此条件只在最后一次跳出时生效
			//1.如果进while，证明左子树访问完毕，则给tag置位
			//2.如果没进while，证明左子树不存在
			cur = StackTop(&st);
			tag[st.size - 1] = 1;
			cur = cur->rchild;
			//左子树访问完毕后，访问右子树
		}
	} while (!StackEmpty(&st));//由于后序遍历根节点是左后出栈的，所以当栈为空时跳出
	StackDestory(&st);
}

int BinaryTreeLeafSize(BTNode* root);

int BinaryTreeLevelKSize(BTNode* root, int k);

int BinaryTreeComplete(BTNode* root){
	Queue qu;
	BTNode* cur;
	QueueInit(&qu);
	QueuePush(&qu, root);

	while (QueueEmpty(&qu)){
		cur = QueueTop(&qu);
		putchar(cur->data);//test where return;
		int tag = 0;

		if (cur->rchild && !cur->lchild){
			return 0;
		}

		if (tag && (cur->rchild || cur->lchild)){
			return 0;
		}

		if (cur->lchild){
			QueuePush(&qu, cur->lchild);
		}

		if (cur->rchild){
			QueuePush(&qu, cur->rchild);
		}
		else{
			tag = 1;
		}
		QueuePop(&qu);
	}

	QueueDestory(&qu);
	return 1;
}











