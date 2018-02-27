using namespace std;

class Packet
{
    public:
        int packetType;
        int dataSize;
        int timeToForward;
        Name name;
        
        Packet(int pt, int ds, Name n)
        {
            packetType = pt;
            dataSize = ds;
            name = n;
            timeToForward = dataSize;
        }

        void resetTimeToForward()
        {
            timeToForward = dataSize;
        }
};