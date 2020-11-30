#include <iostream>
#include <string>
#include <cassert>
#include <vector>


int str_hash( const std::string& data, size_t& m )
{
    size_t hash = 0;
    for( size_t i = 0; i != data.size(); i++ )
        hash = ( hash * 2013 + data[i] ) % m;
    return hash;
}

static constexpr size_t BUCKETS_COUNT[] = {
         8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072
};

template <class T> struct HashFunc;

template<> struct HashFunc<std::string> {
    size_t operator()(const std::string& key, size_t& m) {
        return str_hash(key, m);
    }
};

template <class Key, class Hash = HashFunc<Key>>
class HashSet {
private:
    static constexpr double max_load_factor = 0.75;
    struct Node {
        Key key;
        int state;
        Node(const Key& key, const Key& state) :
        key(key), state(0) {
        }
        Node(): key(""), state(0) {

        }
        Node(const Node& rhs) {
            key = rhs.key;
            state = rhs.state;
        }
    };

public:
    friend
    void test();
    HashSet(Hash hash = Hash()) :
        buckets(0),
        buckets_count(0),
        items_count(0),
        size_idx(0),
        hash(hash)
    {
    }
    ~HashSet() {
    }
    Key* find(const Key& key) {
        if (buckets_count == 0) {
            return nullptr;
        }
        int idx = hash(key,buckets_count);//hash_value % buckets_count;
        for(size_t i = 0; i < buckets_count; ++i ) {
            if (buckets[idx].state == 0 || buckets[idx].state == 3)
                return nullptr;
            if (buckets[idx].key == key)
                return &buckets[idx].key;
            idx = (idx + i+1)%buckets_count;
        }
        return nullptr;
    }
    bool insert (const Key& key) {
        if (buckets_count == 0) {
            grow();
        }
        if(find(key)) {
            return false;
        }
        if (items_count != 0) {
            if (static_cast<double>(buckets_count)* max_load_factor < items_count) {
                grow();
            }
        }
        int idx = hash(key,buckets_count);

        for(size_t i = 0; i < buckets_count; ++i ) {
            if (buckets[idx].state != 2) {
                buckets[idx].state = 2;
                buckets[idx].key = key;
                items_count++;
                return true;
            }
            idx = (idx + i +1)%buckets_count;
        }
        return false;
    }
    bool erase(const Key& key) {
        if (buckets_count == 0) {
            return false;
        }
        int idx = hash(key,buckets_count);//hash_value % buckets_count;

        for(size_t i = 0; i < buckets_count; ++i ) {
            if (buckets[idx].state == 0) {
                return false;
            }
            if (buckets[idx].key == key) {
                buckets[idx].state = 3;
                buckets[idx].key = "";
                items_count--;
                return true;
            }
            idx =(idx + i+1)%buckets_count;
        }
        return false;
    }


private:
    void grow() {
        size_t new_buckets_count = BUCKETS_COUNT[size_idx++];

        int state = 0;
        Key key = "";
        std::vector<Node> new_buckets;

        new_buckets.reserve(new_buckets_count);
        for (size_t i = 0; i < new_buckets_count; i++) {
            new_buckets.push_back( Node());
        }
        for (size_t i = 0; i < buckets_count; i++) {
            int idx = hash(buckets[i].key,new_buckets_count);
            for (size_t j = 0; j < new_buckets_count; j++){
                if (new_buckets[idx].state != 2) {
                    new_buckets[idx] = buckets[i];
                    break;
                }
                idx = (idx + j+1)%new_buckets_count;
            }
        }
        buckets = new_buckets;
        buckets_count = new_buckets_count;
    }
    std::vector<Node> buckets;
    size_t buckets_count;
    double items_count;
    size_t size_idx;
    Hash hash;
};
void test() {
    std::string k = "";
    HashSet<std::string> h;
    bool res = false;

    // start
    k = "buy";
    res = h.insert(k);
    assert(res == true);
    std::cout << "OK\n";

    k = "buy";
    res = h.find(k);
    assert(res == true);
    std::cout << "OK\n";

    k = "buy";
    res = h.insert(k);
    assert(res == false);
    std::cout << "OK\n";

    k = "kek";
    res = h.find(k);
    assert(res == false);
    std::cout << "OK\n";

    k = "kek";
    res = h.erase(k);
    assert(res == false);
    std::cout << "OK\n";

    k = "buy";
    res = h.insert(k);
    assert(res == false);
    std::cout << "OK\n";

    k = "kek";
    res = h.find(k);
    assert(res == false);
    std::cout << "OK\n";

    k = "lol";
    res = h.find(k);
    assert(res == false);
    std::cout << "OK\n";

    k = "lol";
    res = h.insert(k);
    assert(res == true);
    std::cout << "OK\n";
    /////////////////////////////////////////////////////////

    k = "huh";
    for (size_t i = 0; i < 10000; i++) {
        if (i > 5000) {
            res = h.erase(k);
            assert(res == false);
        }
        if (i == 0) {
            res = h.insert(k);
            assert(res == true);
        } else if (i == 1) {
            res = h.find(k);
            assert(res == true);
        } else if (i > 1 && i < 5000) {
            res = h.insert(k);
            assert(res == false);
        } else if (i == 5000){
            res = h.erase(k);
            assert(res == true);
        }


    }
    std::cout << "OKKKK\n";
    //////////////////////////////////////////
    for (size_t i = 0; i < 90000; i++) {
        k = "opg";
        k = k + std::to_string(i);
        res = h.insert(k);
        assert(res == true);
    }

    //std::cout << "OKAY\n" << h.buckets[14614].key;
    //for (size_t i = 0; i < h.buckets_count; i++) {
//        std::cout << h.buckets[i].key << " " << h.buckets[i].state << std::endl;
    //}
    std::cout << h.buckets_count << std::endl;
    for (size_t i = 0; i < 90000; i++) {
        k = "opg";
        k = k + std::to_string(i);
        res = h.insert(k);
        assert(res == false);

    }
    std::cout << "OKAY\n";
    res = h.erase("opg0");
    assert(res == true);
    res = h.find("opg1");
    assert(res == true);
    std::cout << "OKAY\n";
    for (size_t i = 89999; i > 0; i--) {
        k = "opg";
        k = k + std::to_string(i);
        //std::cout << k << std::endl;
        res = h.erase(k);
        if (i == 0) {
            assert(res == false);
            continue;
        }
        //std::cout << i << std::endl;
        assert(res == true);
    }
    std::cout << "OKAY\n";


}
int main() {
    test();
    std::string key = "";
    char operation = '\0';
    HashSet<std::string> hset;
    while (std::cin >> operation >> key) {
        bool res = false;
        switch (operation) {
            case '+':
                res = hset.insert(key);
                break;
            case '-':
                res = hset.erase(key);
                break;
            case '?':
                res = (hset.find(key) != nullptr);
                break;
            default:
                return 1;
        }
        if (res) {
            std::cout << "OK\n";
        } else {
            std::cout << "FAIL\n";
        }
    }
    return 0;
}