class Name
    public:
        string name;
        Name(string n)
        {
            name = n;
        }

        string GetName()
        {
            return name;
        }

        /* unit test this */
        int prefixMatch(Name other)
        {
            int i;
            for(i = 0; i < min(name.length(), other.name.length()) && name[i] == other.name[i]; i++);
            return i;
        }
};