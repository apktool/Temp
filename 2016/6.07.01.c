//平衡二叉树|Balanced Binary Tree[AVL]
#include<stdio.h>
#include<stdlib.h>

#define MaxSize 20
typedef int ElemType;
typedef struct BiTNode{
	ElemType data;
	struct BiTNode *lchild,*rchild;
	int height;
}BiTNode, *BiTree;

BiTNode* AVL_Create(BiTNode*,ElemType*);
BiTNode* AVL_Insert(BiTNode*,ElemType);
BiTNode* AVL_Delete(BiTNode*,ElemType);
BiTNode* AVL_Search(BiTNode*,ElemType);

void AVL_Judge(BiTNode*);
void PreOrder(BiTNode*);
void InOrder(BiTNode*);

int Max(int,int);
int Height(BiTNode*);

BiTNode* RotateLeftLeft(BiTNode*);
BiTNode* RotateLeftRight(BiTNode*);
BiTNode* RotateRightRight(BiTNode*);
BiTNode* RotateRightLeft(BiTNode*);

int main(int argc,char* argv[]){
	BiTNode* T=NULL;
	ElemType ch[MaxSize]={
		1,2,3,4,5,6,7,8,-1
	};
	T=AVL_Create(T,ch);

	AVL_Judge(T);

	BiTNode* P=T;
	ElemType num;

	printf("Please input the number you will insert: ");
	scanf("%d",&num);
	P=AVL_Insert(T,num);
	//P?printf("Insert Success\n"):printf("illegal Insert\n");

	printf("Please input the number you want to find: ");
	scanf("%d",&num);
	P=AVL_Search(T,num);
	P?printf("Find it\n"):printf("Not Find\n");
	
	printf("Please input the number you want to delete: ");
	scanf("%d",&num);
	P=AVL_Delete(T,num);
	//P?printf("Delete Success\n"):printf("Delete Failed\n");

	AVL_Judge(T);
	return 0;
}

BiTNode* AVL_Create(BiTNode* T,ElemType ch[]){
	int i=0;
	while(ch[i]!=-1){
		T=AVL_Insert(T,ch[i++]);
		if(T==NULL){
			printf("Insert illegal\n");
			break;
		}
	}
	return T;
}

BiTNode* AVL_Insert(BiTNode* T,ElemType ch){
	if(T==NULL){
		T=(BiTNode*)malloc(sizeof(BiTNode));
		T->data=ch;
		T->height=0;
		T->lchild=NULL;
		T->rchild=NULL;
	}
	if(ch<T->data){
		T->lchild=AVL_Insert(T->lchild,ch);
		if(Height(T->lchild)-Height(T->rchild)==2){
			if(ch<T->lchild->data){
				T=RotateLeftLeft(T);
			}else{
				T=RotateLeftRight(T);
			}
		}
	}
	if(ch>T->data){
		T->rchild=AVL_Insert(T->rchild,ch);
		if(Height(T->rchild)-Height(T->lchild)==2){
			if(ch>T->rchild->data){
				T=RotateRightRight(T);
			}else{
				T=RotateRightLeft(T);
			}
		}
	}
	
	T->height=Max(Height(T->lchild),Height(T->rchild))+1;
	return T;
}

BiTNode* AVL_Search(BiTNode* T,ElemType ch){
	if(T==NULL){
		return NULL;
	}
	if(ch<T->data){
		return AVL_Search(T->lchild,ch);
	}else if(ch>T->data){
		return AVL_Search(T->rchild,ch);
	}else{
		return T;
	}
}

BiTNode* AVL_Delete(BiTNode* T,ElemType ch){
	if(T==NULL){
		return NULL;
	}
	if(ch<T->data){
		T->lchild=AVL_Delete(T->lchild,ch);
		if(Height(T->rchild)-Height(T->lchild)==2){
			if(T->rchild->lchild!=NULL&&(Height(T->rchild->lchild)>Height(T->rchild->lchild))){
				T=RotateRightLeft(T);
			}else{
				T=RotateRightRight(T);
			}
		}
	}else if(ch>T->data){
		T->rchild=AVL_Delete(T->rchild,ch);
		if(Height(T->lchild)-Height(T->rchild)==2){
			if(T->lchild->rchild!=NULL&&(Height(T->lchild->rchild)>Height(T->lchild->rchild))){
				T=RotateLeftRight(T);
			}else{
				T=RotateLeftLeft(T);
			}
		}
	}else{
		BiTNode *r=NULL;
		if(T->lchild!=NULL&&T->rchild!=NULL){
			r=T->rchild;
			while(r->lchild!=NULL){
				r=r->lchild;
			}
			T->data=r->data;
			T->rchild=AVL_Delete(T->rchild,r->data);
			if(Height(T->lchild)-Height(T->rchild)==2){
				if(T->lchild->rchild!=NULL&&(Height(T->lchild->rchild)>Height(T->lchild->rchild))){
					T=RotateLeftRight(T);
				}else{
					T=RotateLeftLeft(T);
				}
			}
		}else{
			r=T;
			if(T->lchild==NULL){
				T=T->rchild;
			}else{
				T=T->lchild;
			}
			free(r);
			r=NULL;
		}
	}
	if(T!=NULL){
		T->height=Max(Height(T->lchild),Height(T->rchild))+1;
	}
	return T;
}

BiTNode* RotateLeftLeft(BiTNode* T){
	BiTNode *p=T;
	BiTNode *q=p->lchild;

	q=p->lchild;
	p->lchild=q->rchild;
	q->rchild=p;

	p->height=Max(Height(p->lchild),Height(p->rchild))+1;
	q->height=Max(Height(q->lchild),p->height)+1;
	
	return q;
}

BiTNode* RotateLeftRight(BiTNode* T){
	BiTNode *p=T;
	BiTNode *q=p->lchild;
	BiTNode *r=q->rchild;
	RotateRightRight(q);
	RotateLeftLeft(p);

	return r;
}

BiTNode* RotateRightRight(BiTNode* T){
	BiTNode *p=T;
	BiTNode *q=p->rchild;

	p->rchild=q->lchild;
	q->lchild=p;

	p->height=Max(Height(p->lchild),Height(p->rchild))+1;
	q->height=Max(Height(q->rchild),p->height)+1;

	return q;
}

BiTNode* RotateRightLeft(BiTNode* T){
	BiTNode *p=T;
	BiTNode *q=p->rchild;
	BiTNode *r=q->rchild;
	
	RotateLeftLeft(q);
	RotateRightRight(p);

	return r;
}

int Max(int a,int b){
	return a>b?a:b;
}

int Height(BiTNode* T){
	return T?T->height:-1;
}

void AVL_Judge(BiTNode* T){
	PreOrder(T);printf("\n");
	InOrder(T);printf("\n");
}

void PreOrder(BiTNode* T){
	if(T==NULL){
		return;
	}
	printf("%3d|%d",T->data,T->height);
	PreOrder(T->lchild);
	PreOrder(T->rchild);
}

void InOrder(BiTNode* T){
	if(T==NULL){
		return;
	}
	InOrder(T->lchild);
	printf("%3d|%d",T->data,T->height);
	InOrder(T->rchild);
}
