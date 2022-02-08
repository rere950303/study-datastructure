//
// - Implementation -
//

// destructor
template <class HashMapElemType>
HashMap<HashMapElemType>::HashMap(unsigned int c) 
{
    mapsize = 0;
    capacity = c;
    divisor = c - (1 - c % 2);
    ht = new HashMapElemType* [capacity];
    for(int i = 0; i < capacity; i++) {
        ht[i] = NULL;
    }
}

// destructor
template <class HashMapElemType>
HashMap<HashMapElemType>::~HashMap() 
{
    for(int i = 0; i < capacity; i++)
    {
        HashMapElemType* elem = ht[i];
        while(elem != NULL)
        {
            HashMapElemType* tmp = elem;
            elem = elem->link;
            free(tmp);
        }
    }
    free(ht);
}

template <class HashMapElemType>
HashMapElemType* 
HashMap<HashMapElemType>::find(const KeyType k) 
{
    unsigned int hashvalue = hashfunction(k);
    HashMapElemType* elem = ht[hashvalue];
    
    while(elem != NULL)
    {
        if(elem->key == k)
        {
            break;
        }
        else
        {
            elem = elem->link;
        }
    }

    return elem;
}

template <class HashMapElemType>
void 
HashMap<HashMapElemType>::insert(const KeyType k, const ValType v) 
{
	unsigned int hashvalue = hashfunction(k);
    HashMapElemType* insertElem = new HashMapElemType;
    insertElem->key = k;
    insertElem->val = v;
    insertElem->link = NULL;
    HashMapElemType* elem = ht[hashvalue];
    HashMapElemType* tmp;
    
    if (elem != NULL)
    {
        while (elem != NULL) {
            if (elem->key == k) {
                elem->val = v;
                break;
            }
            tmp = elem;
            elem = elem->link;
        }
        
        if (elem == NULL) {
            tmp->link = insertElem;
        }
    }
    else
    {
        ht[hashvalue] = insertElem;
    }
    
    mapsize++;
}

template <class HashMapElemType>
bool 
HashMap<HashMapElemType>::remove(const KeyType k) 
{
    unsigned int hashVal = hashfunction(k);
    
    if (ht[hashVal] == NULL) {
        return false;
    } else {
        if(ht[hashVal]->key == k) {
            HashMapElemType* tmp = ht[hashVal];
            ht[hashVal] = ht[hashVal]->link;
            free(tmp);
            mapsize--;
            return true;
        }
        
        HashMapElemType* target = ht[hashVal]->link;
        HashMapElemType* prev = ht[hashVal];
        
        while(target != NULL) {
            if(target->key == k){
                prev->link = target->link;
                free(target);
                mapsize--;
                return true;
            }
            prev = target;
            target = target->link;
        }
    }
    
    return false;
}

template <class HashMapElemType>
unsigned int 
HashMap<HashMapElemType>::hashfunction(const KeyType k)
{
    unsigned int hashkey = 0;
    int pc = 0;
    
    while (k[pc] != '\0') {
        hashkey += (unsigned int) k[pc++];
    }
    
    return hashkey % divisor;
}

template <class HashMapElemType>
void 
HashMap<HashMapElemType>::print()
{
	for(int i = 0; i < capacity; i++) {
        if(ht[i] != NULL) {
            HashMapElemType* elem = ht[i];
            while (elem != NULL) {
                std::cout << elem->key << ":" << elem->val << std::endl;
                elem = elem->link;
            }
        }
    }
}
