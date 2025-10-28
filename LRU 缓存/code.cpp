#include <iostream>
#include <list>
#include <unordered_map>

using namespace std;

class LRUCache {
private:
    int capa; //私有变量：容量capacity
    list<pair <int, int>> cache_list; //双向链表 存储每一个元素的 <key, value>
    unordered_map<int, list<pair <int, int>>::iterator > key_it_map; 
    //splice函数需要接收一个 list 迭代器， 所以这里设计 umap 存入的 value 是一个迭代器
    //哈希表，为了实现 O1 查找 key ， 找到的是一个链表node指针


public:
    
    //构造函数，给 private 变量 capa 赋值
    LRUCache(int capacity) : capa(capacity) {
    }
    

    /*
    三步： 查找是否存在、不存在返回-1 、存在返回值并且置顶
    */
    int get(int key) {
        auto umap_it = key_it_map.find(key);
        // 哈希表迭代器类型，指向一个哈希表元素
        // unordered_map < int, list<pair <int, int>>::iterator > :: iterator。
        // umap_it的 first -> int ; second -> list<pair <int, int>>::iterator
        if(umap_it == key_it_map.end()) //没有查询到
        {
            return -1;
        }
        auto list_it = umap_it->second; // map 的 value。 类型：list<pair<int, int>>::iterator

        //目标位置（链表迭代器）、源链表（list&）、要移动的节点（链表迭代器）
        cache_list.splice(cache_list.begin(), cache_list, list_it);
        return list_it->second; // 返回 value 类型为 int
    }
    
    void put(int key, int value) {
        auto umap_iter = key_it_map.find(key);
        if(umap_iter != key_it_map.end()) //已有这个元素
        {
            auto list_iter = umap_iter->second;
            list_iter->second = value; //更新值
            cache_list.splice(cache_list.begin(), cache_list,  list_iter); //置顶
            return;
        }

        // 新书，放到最上面（emplace_front）
        cache_list.emplace_front(key, value); //双向链表加入第一个节点
        key_it_map[key] = cache_list.begin(); // 更新哈希表
        // 书太多了
        if (key_it_map.size() > capa) {
            // 去掉最后一本书
            key_it_map.erase(cache_list.back().first); //删除哈希表里的记录，括号里传入的是 key
            cache_list.pop_back(); // 双向链表的最后一个 pop 掉
        }


    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */