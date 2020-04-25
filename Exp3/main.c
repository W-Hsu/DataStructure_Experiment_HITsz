#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// begin whsu 2020.04.24
#define BLANKCHAR(C) (C==' ' || C=='\t' || C=='\n')
// end whsu 2020.04.24

// meta: modified brakets and whitespaces

int FLAG = 0;  //标识是否能由后序中序建立二叉树

typedef struct Node {
    char data;
    struct Node *lchild, *rchild;
} TreeNode, *BiTree; //定义树节点的结构体

// begin whsu 2020.04.24
typedef struct {
    BiTree tree;
    int flag;
} result_t, nodeInfo_t;
// end whsu

// begin whsu 2020.04.24
TreeNode *createTreeNode(char newData) { //建立一个新结点
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
// end whsu




// begin whsu 2020.04.24: template from shiyan2
typedef struct QueueNode{
    /** 队列节点 */
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
    /** 队列 */
    QueueNode *head;
    QueueNode *rear;
} LinkQueue;

// begin: whsu 2020.04.10
// comment: let it be more c++!

LinkQueue* InitQueue(){
    /** 初始化队列 */
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
    /** 判断队列是否为空 */
    return (thisQueue->head == thisQueue->rear);
}

int EnQueue(LinkQueue *thisQueue, nodeInfo_t ele){
    /** 入队 */
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

LinkQueue *DestroyQueue(LinkQueue *thisQueue) {
    if (!thisQueue) return NULL;  // else

    while (!QueueEmpty(thisQueue)) DeQueue(thisQueue);
    free(thisQueue->head);
    free(thisQueue);

    return NULL;
}
// end whsu






void preOrderTraverse(BiTree p) {  //函数功能：前序遍历
    // begin whsu 2020.04.24
    if (!p) return;

    printf("%c", p->data);
    preOrderTraverse(p->lchild);
    preOrderTraverse(p->rchild);
    // end whsu
}

void inOrderTraverse(BiTree p) {  //函数功能：中序遍历
    // begin whsu 2020.04.24
    if (!p) return;

    inOrderTraverse(p->lchild);
    printf("%c", p->data);
    inOrderTraverse(p->rchild);
    // end whsu
}

void postOrderTraverse(BiTree p) {  //函数功能：后序遍历
    // begin whsu 2020.04.24
    if (!p) return;

    postOrderTraverse(p->lchild);
    postOrderTraverse(p->rchild);
    printf("%c", p->data);
    // end whsu
}

result_t PostInCreate(char post[],int s1,int e1,char in[],int s2,int e2) {
//函数功能：根据后序与中序序列构造二叉树，并返回根节点
//参数说明：post[]为后序序列，s1,e1为后序的第一和最后一个节点下标，in[]为中序序列，s2,e2为中序的第一和最后一个节点下标。
    // begin whsu 2020.04.24
    // todo: modify memory management in failed attempts
    result_t r;
    r.flag = 0, r.tree = NULL;
    char thisRoot = post[e1];

    if (s1<e1) {
        int *trials = malloc(sizeof(int)*(e1-s1+1));
        memset(trials, -1, sizeof(int)*(e1-s1+1));

        int i=0;
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
                r.flag = 1;
                r.tree = createTreeNode(thisRoot);
                r.tree->lchild = res_l.tree;
                r.tree->rchild = res_r.tree;

                free(trials);
                break;
            }

            i++;
        }
    } else if (s1==e1) {
        if (post[s1]==in[s2]) {
            r.flag = 1;
            r.tree = createTreeNode(post[s1]);
        }
    }
    return r;
    // end whsu
}

// begin whsu 2020.04.24
void countLeafWidth(int *leafNum, int *width, BiTree tree) {
    LinkQueue *q = InitQueue();
    nodeInfo_t tmp = {1, tree};

    EnQueue(q, tmp);


    DestroyQueue(q);
}
// end whsu

int isEquivalent(BiTree bt1,BiTree bt2) {
    //函数功能：判断两树是否等价
    //参数说明：bt1:第一个二叉树，bt2:第二个二叉树

    // begin whsu 2020.04.24
    if ((!bt1 && !bt2)) return 1;
    else if ((bt1&&bt2) && (bt1->data==bt2->data)) if (isEquivalent(bt1->lchild, bt2->lchild) && isEquivalent(bt1->rchild, bt2->rchild)) return 1;

    return 0;
    // end whsu
}

void task1(BiTree bt) {
    //任务1：实现二叉树先序、中序、后序遍历
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
    //任务2：请利用PostInCreate函数根据后序与中序序列构造二叉树
    //使用函数：PostInCreate
    printf("start task (2) Input the postOrder and inOrder Sequence ,Then build the tree\n");
    char post[20];  //后序序列
    char in[20];    //中序序列
    int postlen;    //后序序列长度
    int inlen;      //中序序列长度
    printf("please input the postorder sequence\n");
    scanf("%s",post);
    printf("please input the inorder sequence\n");
    scanf("%s",in);
    //请完善函数

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

void task3(BiTree bt){
    //任务3：计算二叉树的叶节点个数和宽度。（注：计算宽度所需的函数是出题者所设计，若你能有更好的办法得到宽度，自己设计亦可。）
    //使用函数：countLeafWidth
    printf("start task (3) ------------------------------\n");
    int height;     //树的高度
    int leafNum = -1, width = -1;     //树的宽度，预设为-1。（宽度：二叉树每一层节点数的最大值）

    countLeafWidth(&leafNum, &width, bt);

    printf("The number of leaf nodes of the tree is:\n");
    printf("%d\n", leafNum);
    //请完善函数

    printf("The width of the tree is:\n");
    printf("%d\n", width);
}


void task4(BiTree bt1,BiTree bt2){
    //任务4：判断两个二叉树是否等价
    //使用函数：isEquivalent
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
    // task3(bt2);
    task4(bt1,bt2);

    return 0;
}

