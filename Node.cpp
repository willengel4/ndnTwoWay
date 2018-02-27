#include <vector>

using namespace std;

class Node
{
    protected:
        vector<Node*> links;
        vector<PairNodePacket*> inPackets;
        vector<PairNodePacket*> outPackets;
        Table contentStore;
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

        void ForwardMultiple(Packet * p, vector<Node*> nodes, int excluding)
        {
            for(int i = 0; i < nodes.size(); i++)
                if(nodes[i].nodeId != excluding)
                    Forward(p, nodes[i]);
        }

        void ForwardMultiple(Packet * p, vector<Node*> nodes)
        {
            ForwardMultiple(p, nodes, -1);
        }

        void InsertPacket(PairNodePacket* pnp)
        {
            inPackets.push_back(pnp);
        }

        void HandleOutPackets()
        {
            for(int i = outPackets.size() - 1; i >= 0; i--)
            {
                outPackets[i]->packet->timeToForward -= transmissionRate;

                if(outPackets[i]->packet->timeToForward <= 0)
                {
                    forward(outPackets[i]->packet, outPackets[i]->packet);
                    outPackets.erase(outPackets.begin(), i);
                }
            }
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
            /* Content store hit. Forward the content
             * store packet back onto the incoming face */
            if(contentStore.SearchExact(interest->name))
            {
                Forward(contentStore.SearchExact()->packet, from);
                return;
            }

            /* PIT hit. Discard */
            if(pit.SearchExact(interest->name))
                return;

            /* PAT hit. Interest meets Ad. Send Interest 
             * towards Producer via breadcrumb */
            if(pat.SearchExact(interest->name))
            {
                Forward(interest, pat.SearchExact(interest->name)->nodes[0]);
                return; 
            }

            /* FIB hit. Forward Interest along matching FIB entry faces */
            if(fib.SearchExact(interest->name))
            {
                ForwardMultiple(interest, fib.SearchExact(interest->name)->nodes);
                return;
            }

            /* FAB hit. Forward Interest along matching FAB entry faces */
            if(fab.SearchExact(interest->name))
            {
                ForwardMultiple(interest, fab.SearchExact(interest->name)->nodes);
                return;
            }

            /* No hits, forward along all nodes except in node */
            ForwardMultiple(interest, links, from.nodeId);
        }

        void HandleAd(Packet * ad, Node * from)
        {
            /* Content store hit. Forward the content
             * store packet back onto the incoming face */
            if(contentStore.SearchExact(ad->name))
                return;

            /* PIT hit. Ad meets interest. Copy ad, make it an interest. Forward it along pat entry face. */
            if(pit.SearchExact(ad->name))
            {
                Packet* searchResult = pat.SearchExact(ad->name);
                Packet* newInterest = new Packet();
                newInterest->packetType = 1;
                newInterest->name = searchResult->name;
                newInterest->dataSize = searchResult->dataSize;
                Forward(newInterest, searchResult->nodes[0]);                
                return;
            }

            /* PAT hit. Redundant ad. */
            if(pat.SearchExact(ad->name))
                return;

            /* FIB hit. Forward ad along matching FIB entry faces */
            if(fib.SearchExact(ad->name))
            {
                ForwardMultiple(ad, fib.SearchExact(ad->name)->nodes);
                return;
            }

            /* FAB hit. Forward ad along matching FAB entry faces */
            if(fab.SearchExact(ad->name))
            {
                ForwardMultiple(ad, fab.SearchExact(ad->name)->nodes);
                return;
            }

            /* No hits, forward along all nodes except in node */
            ForwardMultiple(ad, links, from.nodeId);
        }

        void HandleData(Packet * ad, Node * from)
        {

        }
};