#ifndef CONSUMER_H
#define CONSUMER_H
#include "Node.cpp"

using namespace std;

class Consumer : public Node
{
    public:
        Consumer()
        {
            Node::Node();
        }

        virtual void Act()
        {
            Node::Act();

            string nameRequest = *datas[rand() % datas->size()]->name;
            Packet * p = new Packet(1, 10, nameRequest);
            for(int i = 0; i < links.size(); i++)
                Forward(p, links[i]);
        }
};
#endif