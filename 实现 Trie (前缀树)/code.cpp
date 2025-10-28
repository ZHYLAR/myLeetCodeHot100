#include <iostream>
#include <string>
#include <vector> 
#include <cstring> // 用于 memset

using namespace std;

// Trie（前缀树）节点的定义
class Trie {
private:
    // isEnd 标记：表示从根节点到当前节点路径形成的字符串是否是一个完整的单词的结尾
    // 例如插入"apple"后，节点'e'的isEnd为true，而节点'p'的isEnd为false
    bool isEnd = 0;
    // next 数组：用于存储指向子节点的指针。由于只包含小写英文字母，所以数组大小为26
    // next[0] 对应 'a'，next[1] 对应 'b'，以此类推
    // 每个索引代表一个字母，指向以该字母为下一个字符的子节点
    Trie* next[26];

public:
    // 构造函数：初始化一个 Trie 节点
    Trie() {
        // 默认当前节点不是任何单词的结尾
        isEnd = false;
        // sizeof(next) 计算整个数组的字节大小
        // memset(next, 0, sizeof(next));
        for (int i = 0; i < 26; i++) 
            next[i] = nullptr;
        
    }
    
    // 插入一个单词到 Trie 树中
    // 实现原理：从根节点开始，对单词中的每个字符逐个处理
    // 如果当前字符对应的子节点不存在，则创建新节点
    // 如果存在则移动到该子节点，直到处理完所有字符
    // 最后将最后一个节点标记为单词结尾
    void insert(string word) {
        // 从根节点开始遍历。这里 `this` 指向当前 Trie 对象的根节点
        Trie* node = this;
        for (char c : word) {
         
            int index = c - 'a';
            // 如果当前节点的对应子节点为空，则创建一个新的 Trie 节点
            // 这确保了每个字符路径在树中都有对应的节点
            if (node->next[index] == nullptr) {
                node->next[index] = new Trie();
            }
            
            node = node->next[index];
        }
        // 单词的所有字符处理完毕后，将最后一个节点标记为单词的结尾
        // 这样可以区分前缀和完整单词，例如"app"和"apple"中的"app"
        node->isEnd = true;
    }
    

    // 搜索 Trie 树中是否存在一个完整的单词
    // 实现原理：从根节点开始，沿着单词的每个字符在树中查找路径
    // 如果路径中断（某个字符对应的子节点不存在），则返回false
    // 如果成功遍历完所有字符，检查最后一个节点是否标记为单词结尾
    bool search(string word) {
      
        Trie* node = this;
  
        for (char c : word) {
      
            node = node->next[c - 'a'];
            // 如果在任何一步发现对应子节点为空，说明单词不存在，返回 false
            // 这意味着单词的路径在Trie中不存在
            if (node == nullptr) {
                return false;
            }
        }
        // 遍历完所有字符后，检查最后一个节点是否被标记为单词的结尾
        // 如果是，说明找到了完整的单词；否则，只找到了一个前缀
        // 例如：插入"apple"后搜索"app"会返回false，因为"app"只是前缀而非完整单词
        return node->isEnd;
    }
    
    // 检查 Trie 树中是否存在以给定前缀开始的单词
    // 实现原理：与search方法类似，但不要求最后一个节点是单词结尾
    // 只要前缀的所有字符都能在Trie中找到对应的路径即可
    bool startsWith(string prefix) {
        // 从根节点开始遍历
        Trie* node = this;
        // 遍历前缀中的每一个字符
        for (char c : prefix) {
            // 移动到下一个节点
            node = node->next[c - 'a'];
            // 如果在任何一步发现对应子节点为空，说明不存在该前缀，返回 false
            // 这意味着前缀的路径在Trie中不存在
            if (node == nullptr) {
                return false;
            }
        }
        // 如果成功遍历完所有前缀字符，说明该前缀存在
        // 不需要检查isEnd标志，因为只要路径存在就说明前缀存在
        return true;
    }
};

int main() {
    Trie* obj = new Trie();
    obj->insert("apple");
    cout << obj->search("apple") << endl;   // 预期输出：1 (true)
    cout << obj->search("app") << endl;     // 预期输出：0 (false)
    cout << obj->startsWith("app") << endl; // 预期输出：1 (true)
    obj->insert("app");
    cout << obj->search("app") << endl;     // 预期输出：1 (true)

    return 0;
}