#include <vector>

using namespace std;

class Node
{
    protected:
        vector<Node*> links;
        vector<PairNodePacket*> inPackets;
        vector<PairNodePacket*> outPackets;
        Table pit;
        Table pat;
        Table fib;
        Table fab;

    public:
        int transmissionRate = 50;
        int nodeId;

        void Forward(Packet * p, Node * to)
        {
            to->InsertPacket(new PairNodePacket(this, p));
        }

        void InsertPacket(PairNodePacket* pnp)
        {
            inPackets.push_back(pnp);
        }

        void HandleOutPackets()
        {
            for(int i = 0; i < outPackets.size(); i++)
                outPackets[i]->packet->timeToForward -= transmissionRate;

            for(int i = 0; i < outPackets.size(); i++)
                if(outPackets[i]->packet->timeToForward <= 0)
                    forward(outPackets[i]->packet, outPackets[i]->packet);
            
            for(int i = outPackets.size(); i >= 0; i--)
                if(outPackets[i]->packet->timeToForward <= 0)
                    outPackets.erase(outPackets.begin(), i);
        }

        void HandleInPackets()
        {
            for(int i = 0; i < inPackets.size(); i++)
            {
                PairNodePacket * pnp = inPackets[i];

                if(pnp->packet->packetType() == 0)
                    HandleData(pnp->packet, pnp->packet);
                else if(pnp->packet->packetType() == 1)
                    HandleInterest(pnp->packet, pnp->packet);
                else
                    HandleAd(pnp->packet, pnp->packet);
            }

            inPackets.clear();
        } 

        void HandleInterest(Packet * interest, Node * from)
        {

        }

        void HandleAd(Packet * ad, Node * from)
        {

        }

        void HandleData(Packet * ad, Node * from)
        {

        }
};