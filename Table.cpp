class Table
{
    public:
        vector<Entry *> entries;

        Entry* SearchExact(Name name)
        {
            for(int = 0; i < entries.size(); i++)
                if(entries[i]->packet->name->name == name->name)
                    return entries[i];
            return NULL;
        }

        Entry* SearchLongestPrefix(Name name)
        {
            int longest = 0;
            Entry * ent = NULL;

            for(int i = 0; i < entries.size(); i++)
            {
                string n = entries[i]->packet->name->name;

                int countSlash = 0;
                for(int f = 0; f < min(n.length, name->name.length) && n[i] == name.name[i]; f++)
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
};