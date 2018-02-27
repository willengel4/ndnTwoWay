class Table
{
    public:
        vector<Entry *> entries;

        Entry* SearchExact(Name name, vector<Entry*> entries)
        {
            for(int = 0; i < entries.size(); i++)
                if(entries[i]->packet->name->name == name->name)
                    return entries[i];
            return NULL;
        }
};