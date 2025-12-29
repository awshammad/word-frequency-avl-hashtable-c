// Aws Hammad - 1221697 - sec : 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct NodeAVL;
typedef struct NodeAVL *AVL_Tree;
struct NodeAVL {
    char word[50];
    AVL_Tree left;
    AVL_Tree right;
    int height;
    int frequency;
};
struct hashNode {
    char word[50];
    int frequency;
    struct hashNode* next;// handling collisions using chaining
};
struct HashTable {
    struct hashNode *table[53]; // array of linked lists
};
typedef struct HashTable *Table;
typedef struct hashNode *Node;
AVL_Tree insert(AVL_Tree t, char word[]);
AVL_Tree find_min(AVL_Tree T);
AVL_Tree deleteNode(AVL_Tree T, char* x);
int main() {
    AVL_Tree root = NULL;
    Table t = (Table)malloc(sizeof(struct HashTable));// make the hash table
    for (int i = 0; i < 53; i++) {
        t->table[i] = NULL;// initialize the indexes to null
    }
    int op = 0;
    while (op != 10) {
        printMenu();
        scanf("%d", &op);
        switch (op) {
        case 1:
            readWords(&root);// read from file and insert into the AVL Tree
            break;
        case 2:
            addWord(&root);// insert a word from the user into the AVL Tree
            break;
        case 3:
            Delete(&root);// delete a word from the AVL Tree
            break;
        case 4:
            printInOrder(root);// print the AVL tree in order traversal
            break;
        case 5:
            traverseAndInsert(root, t);// load all the words from the AVL Tree into a hash table
            break;
        case 6:
            user_insert(t);// insert a word from the user into the hash table
            break;
        case 7:
            deleteWordFromHashTable(t);// delete a word from the hash table
            break;
        case 8:
            search(t);// search for a word in the hash table
            break;
        case 9:
            printHash(t);// Print words statistics in the hash table
            break;
        case 10:
            printf("\nExiting the program...\nThanks for your time, Bye!\n");
            break;
        default:
            printf("\nERROR! Please enter a number between 1 and 10.\n");
            break;
        }
    }
    return 0;
}
void printMenu() {
    printf("\nProgram Menu:\n");
    printf("-------------\n");
    printf("1. Load data from the file into AVL tree \t");
    printf("2. Insert a word into the AVL tree \n");
    printf("3. Delete a word from the AVL tree \t\t");
    printf("4. Print the words as sorted in the AVL tree \n");
    printf("5. Create the Hash Table \t\t\t");
    printf("6. Insert a word to the Hash table \n");
    printf("7. Delete a word from the hash table \t\t");
    printf("8. Search for a word in the hash table and print its frequency \n");
    printf("9. Print words statistics \t\t\t");
    printf("10. Exit the application \n");
    printf("\nselect an option by entering its number: ");
}
void readWords(AVL_Tree *T) {
    FILE *in = fopen("input.txt", "r");// open a file to read from it
    if (in == NULL) {
        printf("Unable to open file\n");
        return;
    }
    char word[50];// a string to get the words from text
    char clean[50];
    while (fscanf(in, "%49s", word) == 1) {// read until EOF
        int j=0;
        for (int i = 0; i<strlen(word); i++) {
            if ((word[i] >= 'a' && word[i] <= 'z') || (word[i] >= 'A' && word[i] <= 'Z')) {
                clean[j] = tolower(word[i]);
                j++;
            }
        }
        clean[j]='\0';
        if (j > 0) {
            *T = insert(*T, clean); // Insert the cleaned word into the AVL tree
        }
    }
    printf("\nThe text from the file has been uploaded.\n");// the reading is done
    fclose(in);
}
int Max (int x, int y) {// a function to get the max of two numbers
    if(x>y)
        return x;// x is greater
    else
        return y;// y is greater
}
int getHeight (AVL_Tree t) {
    if(t==NULL)
        return -1;
    else
        return t->height;// return the height of the node
}
AVL_Tree singleRotateLeft(AVL_Tree a) {
    AVL_Tree b = a->right;// have the right of a into b
    a->right = b->left;// let the right of a equals the left of b (a->right)
    b->left = a;// then the left of b is equals to a
    // update the height
    a->height = 1 + Max(getHeight(a->left), getHeight(a->right));// the height of a  equals 1 + the max between the height of left node and right node
    b->height = 1 + Max(getHeight(b->left), getHeight(b->right));// the height of b equals 1 + the max between the height of left node and right node
    return b;
}
AVL_Tree singleRotateRight(AVL_Tree a) {
    AVL_Tree b = a->left;// have the left of a into b
    a->left = b->right;// let the left of a equals the right of b (a->left)
    b->right = a;// then the right of b is equals to a
    // update the height
    a->height = 1 + Max(getHeight(a->left), getHeight(a->right));// the height of a  equals 1 + the max between the height of left node and right node
    b->height = 1 + Max(getHeight(b->left), getHeight(b->right));// the height of b equals 1 + the max between the height of left node and right node
    return b;
}
AVL_Tree doubleRotateLeft(AVL_Tree t) {// rotate left then rotate right
    t->left = singleRotateLeft(t->left);
    return singleRotateRight(t);
}
AVL_Tree doubleRotateRight(AVL_Tree t) {// rotate right then rotate left
    t->right = singleRotateRight(t->right);
    return singleRotateLeft(t);
}
int get_balance(AVL_Tree N) {
    if (N == NULL)
        return 0;
    return getHeight(N->left) - getHeight(N->right);// the balance of any node equals to the height of the left - the height of the right
}
AVL_Tree insert(AVL_Tree t, char word[]) {
    if (t == NULL) {// if the tree is empty create new node
        t = (AVL_Tree)malloc(sizeof(struct NodeAVL));
        strcpy(t->word, word);// copy the word into the node
        t->height = 1;// set the height to 1
        t->left = t->right = NULL;// initialize the node
        t->frequency = 1;// set frequency to 1
    } else if (strcasecmp(word, t->word) < 0) {// if the word is smaller than the node's word
        t->left = insert(t->left, word);// insert in the left
        if (getHeight(t->left) - getHeight(t->right) >= 2) {// if the tree became unbalance
            if (strcasecmp(word, t->left->word) < 0)// if the tree is smaller than the left child then do a SRR
                t = singleRotateRight(t);
            else
                t = doubleRotateLeft(t);// if the tree is greater than the left child then do a DRL
        }
    } else if (strcasecmp(word, t->word) > 0) {// if the word is greater than the node's word
        t->right = insert(t->right, word);// insert in the right
        if (getHeight(t->right) - getHeight(t->left) >= 2) {// if the tree became unbalance
            if (strcasecmp(word, t->right->word) > 0)// if the tree is greater than the right child then do a SRL
                t = singleRotateLeft(t);
            else
                t = doubleRotateRight(t);// if the tree is smaller than the right child then do a DRR
        }
    } else {
        t->frequency++;// if the word is already exists then add 1 to the frequenct
    }

    t->height = 1 + Max(getHeight(t->left), getHeight(t->right));// update the height of the node
    return t;
}
void addWord (AVL_Tree *T) {
    char word [50];
    char clean [50];
    printf("Enter a word to add : \n");
    while (getchar() != '\n');// to stop reading when the user write (Enter)
    scanf("%49[^\n]", word);
    int j=0;
    for (int i = 0; i<strlen(word); i++) {
        if ((word[i] >= 'a' && word[i] <= 'z') || (word[i] >= 'A' && word[i] <= 'Z')) {
            clean[j] = tolower(word[i]);
            j++;
        }
    }
    clean[j]='\0';
    if (j > 0) {
        *T = insert(*T, clean); // Insert the cleaned word into the AVL tree
        printf("The word (%s) has been added :)\n", clean);
    } else {
        printf("ERROR! Your word should have at least one character.\n");
    }
}
void printInOrder(AVL_Tree t) {
    if (t != NULL) {
        printInOrder(t->left);// left
        printf("[%s - frequency = %d] \n", t->word, t->frequency);// root
        printInOrder(t->right);// right
    }
}
AVL_Tree deleteNode(AVL_Tree T, char* x) {
    // if the tree is empty
    if (T == NULL) {
        printf("The word (%s) is not found :(\n",x);
        return T;
    }
    // search for the word to be deleted
    if (strcasecmp(x, T->word) < 0) {
        T->left = deleteNode(T->left, x);// the word is in the left subtree
    } else if (strcasecmp(x, T->word) > 0) {
        T->right = deleteNode(T->right, x);// the word is in the right subtree
    } else {// the node we want to delete it is found
        if (T->left == NULL || T->right == NULL) {// case 1: the node has only one child or has no child
            AVL_Tree t;
            if (T->left != NULL) { // only left child exists
                t = T->left;
            } else { // the right child exists or no child exists
                t = T->right;
            }
            if (t == NULL) { // no child case
                t = T;
                T = NULL;
            } else {// if there is one child copy the contents of the exist child
                *T = *t;
            }
            free(t);// free the node
        } else {// case 2: the node has two children
            AVL_Tree t = find_min(T->right);// find the smallest in the right subtree
            strcpy(T->word, t->word);// copy the smallest's word to this node
            T->right = deleteNode(T->right, t->word);// delete the smallest
        }
    }
    if (T == NULL)
        return T;// if the tree had only one node return
    T->height = 1 + Max(getHeight(T->left), getHeight(T->right));// update the height of the current node
    // there are 4 cases if the node became not balanced
    if (get_balance(T) <= -2 && get_balance(T->right) <= 0)// right right case
        return singleRotateLeft(T);
    if (get_balance(T) <= -2 && get_balance(T->right) >= 1) // right left case
        return doubleRotateRight(T);
    if (get_balance(T) >= 2 && get_balance(T->left) >= 0)// left left case
        return singleRotateRight(T);
    if (get_balance(T) >= 2 && get_balance(T->left) <= -1) // left right case
        return doubleRotateLeft(T);
    return T;
}
void Delete(AVL_Tree* T) {
    char word[50];
    printf("Enter a word to delete : ");
    while (getchar() != '\n');  // read until the user press (Enter)
    scanf("%49[^\n]", word);
    *T = deleteNode(*T, word);// delete the node that have the word
}
AVL_Tree find_min(AVL_Tree T) {
    if (T==NULL)
        return NULL;
    else if (T->left==NULL)
        return (T);// the smallest node
    else
        return (find_min (T->left));// go left until left of the node is null
}
unsigned int hashFunction(char *x, unsigned int tableSize) {
    unsigned int val = 0;// put the hash value 0
    while (*x != '\0') {// move through all characters in the string
        val = (val << 5) + *x;// shift the hash value to the left by 5 bits and add the ASCII of the character to it
        x++;// move to the next character
    }
    return val % tableSize;// return the hash value module the table size
}
Node create_hash_node(char *word) {
    Node n = (Node)malloc(sizeof(struct hashNode));// n is the new node
    if (n) {
        strcpy(n->word, word);// copy the word into the node's word
        n->frequency = 1;// initialize the frequency to 1
        n->next = NULL;
    }
    return n;
}
void insertHash(Table t, char *word,int frequency) {
    unsigned int i = hashFunction(word, 53);// get the hash index from the hash function
    Node n = create_hash_node(word);// create node that have the word in it
    n->frequency = frequency;
    if (t->table[i] != NULL) {// if the index in the hash table is not empty
        Node p = t->table[i];// put a pointer on the node
        while (p != NULL) {// go through all the linked list at this index
            if (strcasecmp(p->word, word) == 0) {// if we found a node that have the word we want to insert
                p->frequency+=n->frequency;// add 1 to the frequency
                free(n);
                return;
            }
            if (p->next == NULL) {// if the end of the linked list
                p->next = n;// then add the node at the end
                return;
            }
            p = p->next;// move to the next node
        }
    } else {// if the index in the hash table is empty
        t->table[i] = n;// simply add the node in it
    }
}
void user_insert (Table t) {
    char word [50];
    char clean[50];
    printf("Enter a word to add to the hash table : ");
    while (getchar() != '\n');// to stop reading when the user write (Enter)
    scanf("%49[^\n]", word);
    int j=0;
    for (int i = 0; i<strlen(word); i++) {
        if ((word[i] >= 'a' && word[i] <= 'z') || (word[i] >= 'A' && word[i] <= 'Z')) {
            clean[j] = tolower(word[i]);
            j++;
        }
    }
    clean[j]='\0';
    if (j > 0) {
        insertHash(t,clean,1);// insert the word that the user entered into the hash table
        printf("The word (%s) has been added :)\n", clean);
    } else {
        printf("ERROR! Your word should have at least one character.\n");
    }
}
void traverseAndInsert(AVL_Tree T, Table t) {
    if (T != NULL) {// implementing in order traversal
        traverseAndInsert(T->left, t);// left
        insertHash(t, T->word,T->frequency);// root
        traverseAndInsert(T->right, t);// right
    }
}
Node searchForNode(Table t, char *word) {
    unsigned int i = hashFunction(word, 53);// get the hash index from the hash function
    Node p = t->table[i];// put a pointer on the node that have the index
    while (p != NULL) {// go through all the nodes in this index
        if (strcasecmp(p->word, word) == 0)
            return p;// found
        p = p->next;// if not found move to the next node
    }
    return NULL;// not found
}
void search(Table t) {
    char word[50];
    char lower[50];
    printf("Enter a word to search for in the hash table : ");
    while (getchar() != '\n');  // read until the user press (Enter)
    scanf("%49[^\n]", word);
    int j=0;
    for (int i = 0; i<strlen(word); i++) {
        lower[j] = tolower(word[i]);
        j++;
    }
    lower[j]='\0';
    unsigned int i = hashFunction(lower, 53);// get the hash index from the hash function
    Node p = searchForNode(t, lower);
    if (p == NULL) {// not found
        printf("The word (%s) is not in the hash table :(\n",word);
        return;
    }
    printf("(%s - %d) at index %d ", p->word, p->frequency,i);// the node that has the word is found
}
/*void printHashTable(Table t) {
    for (int i = 0; i < 50; i++) {
        Node node = t->table[i];
        while (node != NULL) {
            printf("Word: %s, Frequency: %d\n", node->word, node->frequency);
            node = node->next;
        }
    }
}*/
void printHash(Table t) {
    int totalUnique = 0;
    char mostFrequent [50];
    int highestFrequency = 0;
    int threshold;
    printf("Enter the threshold to see words repeated more than this number : ");
    scanf("%d",&threshold);
    printf("Words with frequency more than %d : ", threshold);
    for (int i = 0; i < 50; i++) {// to go through all the indexes
        Node p = t->table[i];
        if (p != NULL) {// if the index have one node or more
            while (p != NULL) {// to go through all the nodes in the index
                if (p->frequency==1) totalUnique++;
                if (p->frequency >= highestFrequency) {
                    highestFrequency = p->frequency;
                    strcpy(mostFrequent,p->word);
                }
                if (p->frequency > threshold) {
                    printf("(%s : %d) ",p->word,p->frequency);
                }
                p = p->next;// move to the next node
            }
        }
    }
    printf("\nTotal unique words : %d\n", totalUnique);
    printf("Most frequent word : (%s : %d)\n", mostFrequent, highestFrequency);
}
void deleteHash(Table t, char *word) {
    unsigned int i = hashFunction(word, 53);// get the hash index from the hash function
    Node p = t->table[i];// put a pointer on the node that have the index
    Node prev = NULL;// previous pointer to point on the node before the one to be deleted
    while (p != NULL) {// go through all the nodes
        if (strcasecmp(p->word, word) == 0) {// if the node that has the word is found
            if (prev == NULL) {// if the node is the first one in the index
                t->table[i] = p->next;
            } else {// if not the first one
                prev->next = p->next;// let the previous point on the next and delete the node
            }
            free(p);
            printf("The word (%s) has been deleted from the hash table :(\n", word);
            return;
        }
        prev = p;
        p = p->next;// move to the next node
    }
    printf("The word (%s) is not found in the hash table :(\n", word);// not found
}
void deleteWordFromHashTable(Table t) {
    char word [50];
    char lower[50];
    printf("Enter a word to delete from the hash table : ");
    while (getchar() != '\n');// to stop reading when the user write (Enter)
    scanf("%49[^\n]", word);
    int j=0;
    for (int i = 0; i<strlen(word); i++) {
        lower[j] = tolower(word[i]);
        j++;
    }
    lower[j]='\0';
    deleteHash(t, lower);
}