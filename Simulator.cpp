#include <stdio.h>
#include <iostream>
#include "Consumer.cpp"

using namespace std;

int main()
{
    vector<DataObject *> allDataObjects;
    Consumer * consumer = new Consumer();
    Producet * producer = new Producer();
    Node * router = new Node();
    consumer->datas = producer->datas = router->datas = &allDataObjects;

    for(int i = 0; i < 3; i++)
    {
        consumer->Act();
        producer->Act();
        router->Act();
    }

    return 0;
}