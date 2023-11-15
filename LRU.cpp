class LRUCache{
public:
    class node{
        public:
            int key;
            int val;
            node* next;
            node* prev;
            node(int k, int v){
                key=k;
                val=v;
            }
    };
    
    int c;
    unordered_map<int,node*>m;
    node* head=new node(-1,-1);
    node* tail=new node(-1,-1);

    void insert_node(node* n){
        node* temp = head->next;
        n->next=temp;
        n->prev=head;
        head->next=n;
        temp->prev=n;
    }

    void delete_node(node* n){
        node* a=n->prev;
        node* b=n->next;
        a->next=b;
        b->prev=a;
        delete n;
    }

    LRUCache(int capacity){
        c=capacity;
        head->next=tail;
        tail->prev=head;
    }

    int get(int k){
        if(m.find(k)!=m.end()){
            node* n=m[k];
            int x=n->val;
            m.erase(k);
            delete_node(n);
            insert_node(n);
            m[k]=head->next;
            return x;
        }return -1;
    }

    void put(int k,int v){
        if(m.find(k)!=m.end()){
            node* n=m[k];
            m.erase(k);
            delete_node(n);
        }
        else{
            insert_node(new node(k,v));
            m[k]=head->next;
        }
        if(m.size()==c){
            m.erase(tail->prev->key);
            delete_node(tail->prev);
        }
    }
};


/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);

 map<int,node*>mp; //key to address in dll

dll [-1,-1]-[4,4]-[3,3]-[-1,-1]

map - [[4,4],[3,3]]

get -> delete entry from map and linked list and u push it back in the correct position

put ->. add entry in the correct postion +. capacity check
you will have the least recently used key,value pair just before the tail
 */