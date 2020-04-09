#include <stdlib.h>
#include <stdio.h>
typedef struct node{
    int ClassID;
    int StuID;
    int Grade;
    struct node *next;
}StudentLinkedListNode;


void printLinkedListNode(StudentLinkedListNode * node){
    printf("{class:%d, ID:%d, Grade:%d}",node->ClassID, node->StuID, node->Grade);
    if(node->next!=NULL){
        printf("->");
    }else
    {
        printf("\n");
    }

}

void outputStudentLinkedList(StudentLinkedListNode* head){
    // (begin whsu, 2020.04.03)
    if (!head || !head->next) return;
    StudentLinkedListNode *iter = head->next;
    while (iter) {
        printLinkedListNode(iter);
        iter = iter->next;
    }
    // (end whsu, 2020.04.03)
}


StudentLinkedListNode* studentLinkedListCreate( int class_id,int student_id,int grade) {
    // (begin whsu, 2020.04.03)
    StudentLinkedListNode *tmp = (StudentLinkedListNode*)malloc(sizeof(StudentLinkedListNode));
    if (tmp) {
        tmp->ClassID = class_id;
        tmp->StuID = student_id;
        tmp->Grade = grade;
        tmp->next = NULL;
    }
    return tmp;
    // (end whsu, 2020.04.03)
}

StudentLinkedListNode* studentLinkedListCopy(StudentLinkedListNode* src){
    StudentLinkedListNode* tempNode = studentLinkedListCreate(src->ClassID,src->StuID,src->Grade);
    return tempNode;
}



StudentLinkedListNode* studentLinkedListAdd(StudentLinkedListNode* head, StudentLinkedListNode* node) {
    // (begin whsu, 2020.04.03)

    // the head only stores ClassID, both StuID and Grade will be set to -1
    if (head==NULL) head = studentLinkedListCreate(node->ClassID, -1, -1);
    StudentLinkedListNode *iter = head;
    while (iter->next) {
        if (iter->next->Grade<node->Grade) break;
        else iter = iter->next;
    }

    // insertion
    // iter -> nextnode
    //      ^ insert here
    StudentLinkedListNode *nxt = iter->next;
    iter->next = node;
    node->next = nxt;

    return head;
    // (end whsu, 2020.04.03)
}

void searchByID(StudentLinkedListNode*head ,int id){
//TODO
    // (begin whsu, 2020.04.03)
    if (head && head->next) {  // uses short circuit to avoid empty head
        StudentLinkedListNode *iter = head->next;
        while (iter) {
            if (iter->StuID==id) {
                printLinkedListNode(iter);

                // (modify whsu, 2020.04.04) prettify
                if (iter->next!=NULL) printf("\b\b  \n");  // remove "->" and start newline in the back
                // (end whsu, 2020.04.04)

                return;  // return if found, avoid showing the error message
            } else {
                iter = iter->next;
            }
        }
    }

    // fixed duplicated whitespace
    printf("this class has no such student as id=%d\n",id);

    // (end whsu, 2020.04.03)
}

StudentLinkedListNode* deleteByID(StudentLinkedListNode* head,int id){
    // (begin whsu, 2020.04.03)
    if (head && head->next) {  // uses short circuit to avoid empty head
        StudentLinkedListNode *iter = head;
        while (iter->next) {
            if (iter->next->StuID==id) {
                StudentLinkedListNode *del = iter->next;
                iter->next = del->next;
                free(del);

                return head;  // return if found, avoid showing the error message
            } else {
                iter = iter->next;
            }
        }
    }

    // fixed duplicated whitespace
    printf("this class has no such student as id=%d",id);

    return head;
    // (end whsu, 2020.04.03)
}


StudentLinkedListNode* mergeLinkedList(StudentLinkedListNode* heads[]){
    // (begin whsu, 2020.04.03)
    StudentLinkedListNode *merged = studentLinkedListCreate(-1, -1, -1);
    StudentLinkedListNode *iter0 = heads[0], *iter1 = heads[1], *merged_iter = merged;

    if (iter0) iter0 = iter0->next;
    if (iter1) iter1 = iter1->next;

    while (iter0 && iter1) {
        if (iter0->Grade < iter1->Grade) {
            merged_iter->next = studentLinkedListCopy(iter1);
            iter1 = iter1->next;
        }
        else {
            merged_iter->next = studentLinkedListCopy(iter0);
            iter0 = iter0->next;
        }

        merged_iter = merged_iter->next;
    }

    while (iter0) {
        merged_iter->next = studentLinkedListCopy(iter0);
        merged_iter = merged_iter->next, iter0 = iter0->next;
    }
    while (iter1) {
        merged_iter->next = studentLinkedListCopy(iter1);
        merged_iter = merged_iter->next, iter1 = iter1->next;
    }

    return merged;
    // (end whsu, 2020.04.03)
}

StudentLinkedListNode* reverseLinkedList(StudentLinkedListNode*head){
    // (begin whsu, 2020.04.03)

    StudentLinkedListNode *reversed = studentLinkedListCreate(-1, -1, -1);
    StudentLinkedListNode *original_iter = head;

    if (original_iter) original_iter = original_iter->next;

    while (original_iter) {
        StudentLinkedListNode *nxt = reversed->next;
        reversed->next = studentLinkedListCopy(original_iter);
        reversed->next->next = nxt;

        original_iter = original_iter->next;
    }

    return reversed;
    // (end whsu, 2020.04.03)
}

// Why there's a lack of concern about SERCURITY ???
// Why there's a lack of concern about SERCURITY ???
// Why there's a lack of concern about SERCURITY ???
StudentLinkedListNode *FreeLinkNode(StudentLinkedListNode *head) {
     while (head) {
        StudentLinkedListNode *del = head;
        head = head->next;
        free(del);
    }
    return NULL;
}

int main(){
        StudentLinkedListNode* Class[2]={NULL};
        StudentLinkedListNode* All=NULL;  // merged list
		StudentLinkedListNode* reAll=NULL;  // reversed
        printf("1.insert 2.search by StuID 3.delete by StuID  4.merge 5.reverse 6.output  \n");

        int op;
        int i;

        /* temporary inputs */
        int tempClass;
        int tempStuId;
        int tempGrade;
        char name[10];
        StudentLinkedListNode *tempNode;

        // (modify whsu, 2020.04.04) robust
        int cmd_success = 0;
        while ((cmd_success=scanf("%d", &op)) != EOF) {
            if (!cmd_success) op = -1;
        // (end whsu, 2020.04.04)

            switch (op) {
                case 1:
                    printf("How many rows of data do you need to input?\n");

                    // (modify whsu, 2020.04.03) robust
                    while(!scanf("%d",&i)) while(getchar()!='\n');
                    // (end whsu, 2020.04.03)

                    printf("input the i row data format as:class_id,student_id,grade\n");
                    // (modified whsu, 2020.04.04) robust
                    while (i>0){  // original condition is (i!=0), what if user enters a negative number?
                    // (end whsu, 2020.04.04)

                        // (modify whsu, 2020.04.03) robust
                        while (scanf("%d,%d,%d", &tempClass, &tempStuId, &tempGrade)!=3) {
                            printf("BAD FORMAT!\n");
                            printf("RE-input the data formatted as:class_id,student_id,grade\n");
                            while (getchar()!='\n');
                        }
                        while (tempClass<0 || 1<tempClass) {
                            printf("Bad class_id, input class_id again\n");
                            scanf("%d", &tempClass);
                        }
                        // (end whsu, 2020.04.03)  will fix remaining robust problem in the next updates

                        tempNode = studentLinkedListCreate(tempClass, tempStuId, tempGrade);
                        Class[tempClass]=studentLinkedListAdd(Class[tempClass], tempNode);
                        i--;
                    }
                    break;
                case 2:
                    printf("input the data format as: ClassID, StuID\n");

                    // (modify whsu, 2020.04.04) robust
                    while (scanf("%d,%d",&tempClass,&tempStuId)!=2) {
                        printf("BAD FORMAT!\n");
                        printf("RE-input the data formatted as:class_id,student_id\n");
                        while (getchar()!='\n');
                    }
                    while (tempClass<0 || 1<tempClass) {
                        printf("Bad class_id, input class_id again\n");
                        scanf("%d", &tempClass);
                    }
                    // (end whsu, 2020.04.04)

                    searchByID(Class[tempClass], tempStuId);
                    break;
                case 3:
                    printf("input the data format as: ClassID, StuID\n");

                    // (modify whsu, 2020.04.03) robust
                    while (scanf("%d,%d",&tempClass,&tempStuId)!=2) {
                        printf("BAD FORMAT!\n");
                        printf("RE-input the data formatted as:class_id,student_id\n");
                        while (getchar()!='\n');
                    }
                    while (tempClass<0 || 1<tempClass) {
                        printf("Bad class_id, input class_id again\n");
                        scanf("%d", &tempClass);
                    }
                    // (end whsu, 2020.04.03)

                    Class[tempClass]=deleteByID(Class[tempClass], tempStuId);
                    break;
                case 4:
                    All=mergeLinkedList(Class);
                    outputStudentLinkedList(All);

                    // (modify whsu, 2020.04.03) security
                    All = FreeLinkNode(All);
                    // (end whsu, 2020.04.03)
                    break;
                case 5:
                    // (modify whsu, 2020.04.03) security && robust
                    if (All) reAll=reverseLinkedList(All);
                    else reAll = reverseLinkedList(All = mergeLinkedList(Class));

                    outputStudentLinkedList(reAll);

                    All = FreeLinkNode(All);
                    reAll = FreeLinkNode(reAll);
                    // (end whsu, 2020.04.03)
                    break;
                case 6:
                    printf("Class 0:\n");
                    outputStudentLinkedList(Class[0]);
                    printf("\nClass 1:\n");
                    outputStudentLinkedList(Class[1]);
                    break;
                
                // (modify whsu, 2020.04.04) robust
                default:
                    printf("invalid command!\nTip:\nOn Unix-like systems, input Ctrl-d to exit.\nOn Windows, input Ctrl-z to exit.\n");
                    while (getchar()!='\n');
                    break;
                // (end whsu, 2020.04.04)
            }
            printf("\n###################################\n");
            printf("1.insert 2.search by studentID 3.delete by studentID 4.merge 5. reverse 6.output  \n");
    }

    // security concerns
    for (int i=0 ; i<2 ; i++) Class[i] = FreeLinkNode(Class[i]);
    // return 0 as a habit
    return 0;
}
