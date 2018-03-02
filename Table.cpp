#ifndef TABLE_H
#define TABLE_H
#include <vector>
#include "Entry.cpp"

using namespace std;

class Table
{
    public:
        vector<Entry *> entries;

        Entry* SearchExact(string name)
        {
            for(int = 0; i < entries.size(); i++)
                if(entries[i]->packet->name == name)
                    return entries[i];
            return NULL;
        }

        Entry* SearchLongestPrefix(string name)
        {
            int longest = 0;
            Entry * ent = NULL;

            for(int i = 0; i < entries.size(); i++)
            {
                string n = entries[i]->packet->name;

                int countSlash = 0;
                for(int f = 0; f < min(n.length, name.length) && n[i] == name[i]; f++)
                    if(n[i] == '/')
                        countSlash++;

                if(countSlash > longest)
                {
                    longest = countSlash;
                    ent = entries[i];
                }
            }

            return ent;
        }

        void AddEntry(Packet * p, Node * node)
        {
            Entry * e = new Entry();
            e->packet = p;
            e->nodes.push_back(node);
            entries.push_back(e);
        }
};
#endif