#include <iostream>
#include <cmath>
#include "Bucket.h"
#include "Block.h"
#include "RandomForOram.h"
#include "OAVLTreePathEviction.h"
#include "OAVLTreeInterface.h"
#include "RandForOramInterface.h"
#include "UntrustedStorageInterface.h"
#include "ServerStorage.h"

using namespace std;

int main() {
    int bucketSize = 4;
    int numBlocks = pow(2, 12);
    Bucket::setMaxSize(bucketSize);    

    UntrustedStorageInterface* storage = new ServerStorage();
    RandForOramInterface* random = new RandomForOram();
    OAVLTreeInterface* oavl = new OAVLTreePathEviction(storage, random, bucketSize, numBlocks);

    cout << "Test begins..." << endl;

    cout << "insert " << 9<< endl;
    oavl->insert(9,9);
    storage->dumpAllValidBlocks();
    
    for (int i = 7; i >= 1; i-=2){
        cout << "insert " << i<< endl;
        oavl->insert(i,i);
        storage->dumpAllValidBlocks();
        cout << "insert " << i+1<< endl;
        oavl->insert(i+1,i+1);
        storage->dumpAllValidBlocks();
    }
    int res = oavl->search(9);
    cout << res << endl;
}
