#ifndef btree_mgr_h
#define btree_mgr_h

#include "dberror.h"
#include "tables.h"

// added struct
typedef struct Node{
    RID* rid;
    int* key;
    int* idflag;
    bool fullFlag;
    bool leafFlag;
    DataType keytype;
    struct Node* next;
}Node;

typedef struct btree{
    Node* root;
    int numNodes;
    int numEntries;
}btree;

// structure for accessing btrees
typedef struct BTreeHandle {
  DataType keyType;
  char *idxId;
  btree* btree;
  Node* node;
} BTreeHandle;

typedef struct BT_ScanHandle {
  BTreeHandle *tree;
//  void *mgmtData;
    int currentId;
    int scanCount;
} BT_ScanHandle;

// init and shutdown index manager
extern RC initIndexManager (void *mgmtData);
extern RC shutdownIndexManager ();

// create, destroy, open, and close an btree index
extern RC createBtree (char *idxId, DataType keyType, int n);
extern RC openBtree (BTreeHandle *tree, char *idxId);
extern RC closeBtree (BTreeHandle *tree);
extern RC deleteBtree (char *idxId);

// access information about a b-tree
extern RC getNumNodes (BTreeHandle *tree, int *result);
extern RC getNumEntries (BTreeHandle *tree, int *result);
extern RC getKeyType (BTreeHandle *tree, DataType *result);

// index access
extern RC findKey (BTreeHandle *tree, Value *key, RID *result);
extern RC insertKey (BTreeHandle *tree, Value *key, RID rid);
extern RC deleteKey (BTreeHandle *tree, Value *key);
extern RC openTreeScan (BTreeHandle *tree, BT_ScanHandle *handle);
extern RC nextEntry (BT_ScanHandle *handle, RID *result);
extern RC closeTreeScan (BT_ScanHandle *handle);

// debug and test functions
extern char *printTree (BTreeHandle *tree);

#endif // btree_mgr_h
