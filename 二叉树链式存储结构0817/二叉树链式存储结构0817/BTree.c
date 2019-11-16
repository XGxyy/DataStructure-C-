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

//�����������
void BinaryTreeDestory(BTNode* root){
	if (root){
		BinaryTreeDestory(root->lchild);
		BinaryTreeDestory(root->rchild);
		free(root);
	}
}

// ����
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

//�ǵݹ������
//����
void BinartTreePrevOrderN(BTNode*root){
	Stack st;
	BTNode* cur = root;

	StackInit(&st, 100);
	while (cur){
		putchar(cur->data);//���ʵ�ǰ�ڵ�
		if (cur->rchild){//������Һ��ӣ���ջ
			StackPush(&st, cur->rchild);
		}

		if (cur->lchild){//��������ӣ�����֮
			cur = cur->lchild;
		}
		else{//û�������ӣ�����ջ��
			cur = StackTop(&st);//ȡ����ʱ����ѭ��
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

	//����������ɣ��Ƚ����ڵ�����

	while (QueueEmpty(&qu)){//����Ϊ������
		cur = QueueTop(&qu);
		putchar(cur->data);//��ӡ�Ӷ������ף�
		if (cur->lchild){
			QueuePush(&qu, cur->lchild);//��������ӣ����
		}
		if (cur->rchild){
			QueuePush(&qu, cur->rchild);//�Һ������
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
		for (; cur; cur = cur->lchild){//����ǰ�ڵ��Լ�������ջ
			StackPush(&st, cur);
		}

		cur = StackTop(&st);
		//ȡջ�� 
		//1.����Һ���Ϊ�գ�forѭ��������ֱ��ȡջ����������������ϵ������
		//2.����Һ��Ӳ�Ϊ�գ���ôֻ��һ��û�����ӵĽڵ㣨������Ϊ�յ������
		putchar(cur->data);
		StackPop(&st);
		cur = cur->rchild;//������Ϊ��ʱ�����ջ�Ƿ�Ϊ��
	}
	StackDestory(&st);
}

void BinaryTreePostOrderN(BTNode* root){
	char tag[64];

	Stack st;
	BTNode* cur = root;

	StackInit(&st, 100);
	do {
		for (; cur; cur = cur->lchild){//����ǰ�ڵ㼰��������ջ
			StackPush(&st, cur);
			tag[st.size - 1] = 0;//�������������ʱ�ǣ�tag��
		}

		while (!StackEmpty(&st) && tag[st.size - 1]){//ֻ����ѭ������ʱ��Ч
			//���������������
			//1.���˴�curΪ��ʱ��forѭ������������������
			//2.��cur��Ϊ�գ�forѭ����������������Ч
			//����⵽��ǰtag����Ϊλ�����1������ӡ��ǰ�ڵ�󣬼����һ�ڵ㣨���ڵ㣩�Ƿ�Ҳ����ӡ
			cur = StackTop(&st);
			putchar(cur->data);
			StackPop(&st);
		}
		if (!StackEmpty(&st)){//������ֻ�����һ������ʱ��Ч
			//1.�����while��֤��������������ϣ����tag��λ
			//2.���û��while��֤��������������
			cur = StackTop(&st);
			tag[st.size - 1] = 1;
			cur = cur->rchild;
			//������������Ϻ󣬷���������
		}
	} while (!StackEmpty(&st));//���ں���������ڵ�������ջ�ģ����Ե�ջΪ��ʱ����
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











