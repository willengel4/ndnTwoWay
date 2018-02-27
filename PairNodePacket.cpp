class PairNodePacket
{
    public:
        Node * node;
        Packet * packet;

        PairNodePacket(Node * n, Packet * p)
        {
            node = n;
            packet = p;
        }
}