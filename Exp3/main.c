#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// begin whsu 2020.04.24
#define BLANKCHAR(C) (C==' ' || C=='\t' || C=='\n')
// end whsu 2020.04.24

// meta: modified brakets and whitespaces

int FLAG = 0;  //��ʶ�Ƿ����ɺ���������������

typedef struct Node {
    char data;
    struct Node *lchild, *rchild;
} TreeNode, *BiTree; //�������ڵ�Ľṹ��

// begin whsu 2020.04.24
typedef struct {
    BiTree tree;
    int flag;
} result_t, nodeInfo_t;
// end whsu

// begin whsu 2020.04.24
TreeNode *createTreeNode(char newData) { //����һ���½��
    TreeNode *bt = (TreeNode*)malloc(sizeof(TreeNode));
    bt->data = newData;
    bt->lchild = bt->rchild = NULL;
    return bt;
}
// end whsu

// begin whsu 2020.04.24
BiTree createBiTree() {
    BiTree tree;
    char c;
    while ((c=getchar())=='\n');

    if(c=='#') tree = NULL;
    else {
        tree = createTreeNode(c);
        tree->lchild = createBiTree();
        tree->rchild = createBiTree();
    }

    return tree;
}

BiTree destroyBiTree(BiTree tree) {
    if (tree) {
        destroyBiTree(tree->lchild);
        destroyBiTree(tree->rchild);
        free(tree);
    }

    return NULL;
} 
// end whsu




// begin whsu 2020.04.24: template from shiyan2
typedef struct QueueNode{
    /** ���нڵ� */
    nodeInfo_t data;
    struct QueueNode* next;
    struct QueueNode* prev;
} QueueNode;

QueueNode *newQueueNode(nodeInfo_t new_data, QueueNode *new_prev) {
    QueueNode *newNode = (QueueNode*)malloc(sizeof(QueueNode));
    newNode->data = new_data;
    newNode->next = NULL;
    newNode->prev = new_prev;

    return newNode;
}
// end: whsu 2020.04.10

typedef struct Queue{
    /** ���� */
    QueueNode *head;
    QueueNode *rear;
} LinkQueue;

// begin: whsu 2020.04.10
// comment: let it be more c++!

LinkQueue* InitQueue(){
    /** ��ʼ������ */
    LinkQueue* thisQueue = (LinkQueue*) malloc(sizeof(LinkQueue));

    // begin: whsu 2020.04.10
    // comment: "with head node" style
    nodeInfo_t n;
    n.flag = -1;
    n.tree = NULL;
    thisQueue->head = thisQueue->rear = newQueueNode(n, NULL);
    // end: whsu 2020.04.10

    return thisQueue;
}

int QueueEmpty(LinkQueue* thisQueue){
    /** �ж϶����Ƿ�Ϊ�� */
    return (thisQueue->head == thisQueue->rear);
}

int EnQueue(LinkQueue *thisQueue, nodeInfo_t ele){
    /** ��� */
    QueueNode *newRear = newQueueNode(ele, thisQueue->rear);

    if (!newRear) return 0;  // else

    thisQueue->rear->next = newRear;
    thisQueue->rear = newRear;
    return 1;
}

int DeQueue(LinkQueue *thisQueue){
    if (QueueEmpty(thisQueue)) return 0;  // else

    QueueNode *del = thisQueue->head->next;

    if (del==thisQueue->rear) thisQueue->rear = thisQueue->head;
    else del->next->prev = thisQueue->head;

    thisQueue->head->next = del->next;
    free(del);

    return 1;
}

nodeInfo_t GetFront(LinkQueue *thisQueue){
    return thisQueue->head->next->data;
}

LinkQueue *DestroyQueue(LinkQueue *thisQueue) {
    if (!thisQueue) return NULL;  // else

    while (!QueueEmpty(thisQueue)) DeQueue(thisQueue);
    free(thisQueue->head);
    free(thisQueue);

    return NULL;
}
// end whsu






void preOrderTraverse(BiTree p) {  //�������ܣ�ǰ�����
    // begin whsu 2020.04.24
    if (!p) return;

    printf("%c", p->data);
    preOrderTraverse(p->lchild);
    preOrderTraverse(p->rchild);
    // end whsu
}

void inOrderTraverse(BiTree p) {  //�������ܣ��������
    // begin whsu 2020.04.24
    if (!p) return;

    inOrderTraverse(p->lchild);
    printf("%c", p->data);
    inOrderTraverse(p->rchild);
    // end whsu
}

void postOrderTraverse(BiTree p) {  //�������ܣ��������
    // begin whsu 2020.04.24
    if (!p) return;

    postOrderTraverse(p->lchild);
    postOrderTraverse(p->rchild);
    printf("%c", p->data);
    // end whsu
}

result_t PostInCreate(char post[],int s1,int e1,char in[],int s2,int e2) {
//�������ܣ����ݺ������������й���������������ظ��ڵ�
//����˵����post[]Ϊ�������У�s1,e1Ϊ����ĵ�һ�����һ���ڵ��±꣬in[]Ϊ�������У�s2,e2Ϊ����ĵ�һ�����һ���ڵ��±ꡣ
    // begin whsu 2020.04.24
    result_t r;
    r.flag = 0, r.tree = NULL;
    char thisRoot = post[e1];

    if (s1<e1) {
        int *trials = (int*)malloc(sizeof(int)*(e1-s1+1));
        memset(trials, -1, sizeof(int)*(e1-s1+1));

        int i=0, success_flag=0;
        for (int j=e2 ; j>=s2 ; j--) if (in[j]==thisRoot) trials[i++] = j;

        i=0;
        while (trials[i]!=-1) {
            result_t res_l, res_r;
            memset (&res_l.flag, 0, sizeof(int)), memset (&res_r.flag, 0, sizeof(int));

            if (trials[i]==e2) res_r.flag = 1, res_r.tree = NULL;
            else res_r = PostInCreate(post, e1-e2+trials[i], e1-1, in, trials[i]+1, e2);

            if (trials[i]==s2) res_l.flag = 1, res_l.tree = NULL;
            else res_l = PostInCreate(post, s1, e1-e2+trials[i]-1, in, s2, trials[i]-1);

            if (res_r.flag&&res_l.flag) {
                if (success_flag) {  // detected two Bitree
                    destroyBiTree(res_l.tree);
                    destroyBiTree(res_r.tree);
                    destroyBiTree(r.tree);
                    r.flag = 0;
                    r.tree = NULL;

                    success_flag = 0;
                    break;
                } else {
                    success_flag = 1;
                }

                r.flag = 1;
                r.tree = createTreeNode(thisRoot);
                r.tree->lchild = res_l.tree;
                r.tree->rchild = res_r.tree;
            } else {
                if (res_l.flag) destroyBiTree(res_l.tree);
                if (res_r.flag) destroyBiTree(res_r.tree);
            }
            
            i++;
        }
        free(trials);
    } else if (s1==e1) {
        if (post[s1]==in[s2]) {
            r.flag = 1;
            r.tree = createTreeNode(post[s1]);
        } 
    }
    
    return r;
    // end whsu
}

// begin whsu 2020.04.25
void countLeafWidth(int *leafNum, int *width, BiTree tree) {
    *leafNum = *width = 0;
    if (!tree) return;

    LinkQueue *q = InitQueue();
    nodeInfo_t tmp;
    tmp.tree = tree, tmp.flag = 1;

    EnQueue(q, tmp);
    int now_depth = 0, now_width = 0, max_width = 0;
    while (!QueueEmpty(q)) {
        nodeInfo_t now = GetFront(q);
        DeQueue(q);

        // leaf
        if (!now.tree->lchild && !now.tree->rchild) (*leafNum)++;

        // width
        if (now.flag==now_depth) {
            now_width++;
        } else {
            now_depth = now.flag;
            now_width = 1;
        }

        max_width = max_width<now_width ? now_width : max_width;

        tmp.flag = now.flag+1;
        tmp.tree = now.tree->lchild;
        if (tmp.tree) EnQueue(q, tmp);
        tmp.tree = now.tree->rchild;
        if (tmp.tree) EnQueue(q, tmp);
    }

    *width = max_width;

    DestroyQueue(q);
}
// end whsu

int isEquivalent(BiTree bt1,BiTree bt2) {
    //�������ܣ��ж������Ƿ�ȼ�
    //����˵����bt1:��һ����������bt2:�ڶ���������

    // begin whsu 2020.04.24
    if ((!bt1 && !bt2)) return 1;
    else if ((bt1&&bt2) && (bt1->data==bt2->data)) if (isEquivalent(bt1->lchild, bt2->lchild) && isEquivalent(bt1->rchild, bt2->rchild)) return 1;

    return 0;
    // end whsu
}

void task1(BiTree bt) {
    //����1��ʵ�ֶ������������򡢺������
    printf("start task (1) Create Tree in PreOrder\n");
    printf("preOrderTraverse\n");
    preOrderTraverse(bt);
    printf("\n");
    printf("inOrderTraverse\n");
    inOrderTraverse(bt);
    printf("\n");
    printf("postOrderTraverse\n");
    postOrderTraverse(bt);
    printf("\n");
}

void task2(BiTree *bt) {
    //����2��������PostInCreate�������ݺ������������й��������
    //ʹ�ú�����PostInCreate
    printf("start task (2) Input the postOrder and inOrder Sequence ,Then build the tree\n");
    char post[20];  //��������
    char in[20];    //��������
    int postlen;    //�������г���
    int inlen;      //�������г���
    printf("please input the postorder sequence\n");
    scanf("%s",post);
    printf("please input the inorder sequence\n");
    scanf("%s",in);
    //�����ƺ���

    postlen = strlen(post);
    inlen = strlen(in);

    result_t res = PostInCreate(post, 0, postlen-1, in, 0, inlen-1);
    *bt = res.tree;

    if (res.flag) {
        printf("preOrderTraverse:\n");
        preOrderTraverse(*bt);
        printf("\n");
    } else {
        printf("Unable to build a binary tree.\n");
    }
}

void task3(BiTree bt) {
    //����3�������������Ҷ�ڵ�����Ϳ��ȡ���ע�������������ĺ����ǳ���������ƣ��������и��õİ취�õ����ȣ��Լ������ɡ���
    //ʹ�ú�����countLeafWidth
    printf("start task (3) ------------------------------\n");
    int height;     //���ĸ߶�
    int leafNum = -1, width = -1;     //���Ŀ��ȣ�Ԥ��Ϊ-1�������ȣ�������ÿһ��ڵ��������ֵ��

    countLeafWidth(&leafNum, &width, bt);

    printf("The number of leaf nodes of the tree is:\n");
    printf("%d\n", leafNum);
    //�����ƺ���

    printf("The widht of the tree is:\n");
    printf("%d\n", width);
}


void task4(BiTree bt1,BiTree bt2){
    //����4���ж������������Ƿ�ȼ�
    //ʹ�ú�����isEquivalent
    printf("start task (4) Are two Bitrees equivalent?\n");
    printf("%d\n",isEquivalent(bt1,bt2));

}
int main() {
    // freopen("D:\\123.txt", "r", stdin);

    BiTree bt1,bt2;
    printf("Create Tree1 in PreOrder\n");
    bt1=createBiTree();

    task1(bt1);
    task2(&bt2);
    task3(bt2);
    task4(bt1,bt2);
    bt1=destroyBiTree(bt1), bt2=destroyBiTree(bt2);
    while(getchar()!='\n');

    return 0;
}
