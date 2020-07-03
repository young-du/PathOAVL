#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include "Bucket.h"
#include "Block.h"
#include "RandomForOram.h"
#include "OAVLTreePathEviction.h"
#include "OAVLTreeInterface.h"
#include "RandForOramInterface.h"
#include "UntrustedStorageInterface.h"
#include "ServerStorage.h"
#include "CorrectnessTester.h"

using namespace std;

void CorrectnessTester::runTester1() {
    int bucketSize = 4;
    int numBlocks = pow(2, 10);
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


void CorrectnessTester::runTester2() {
    int bucketSize = 4;
    int numBlocks = pow(2, 10);
    Bucket::setMaxSize(bucketSize);    

    UntrustedStorageInterface* storage = new ServerStorage();
    RandForOramInterface* random = new RandomForOram();
    OAVLTreeInterface* oavl = new OAVLTreePathEviction(storage, random, bucketSize, numBlocks);

    cout << "Test begins..." << endl;
    vector<int> ele;
    for (int i = 0; i < 1024; ++i) {
        ele.push_back(i);
    }
    random_shuffle(ele.begin(), ele.end());

    int dy = 1;

    for (auto e: ele) {
        cout << dy++ << " : insert " << e << endl;
        oavl->insert(e,e);
    }
    storage->dumpAllValidBlocks();
    for (int i = 0; i < 1024; ++i) {
        int res = oavl->search(i);
        cout << res << endl;
    }
    storage->dumpAllValidBlocks();
    oavl->dumpStash();
}