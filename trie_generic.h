#ifndef __TRIE_GENERIC_H__
#define __TRIE_GENERIC_H__

#include <map>

template<typename ElementType>
class TrieGeneric {
public:
    using element_type = ElementType;

    void AddKeyword(const element_type *keyword, size_t count) {
        if(!keyword || count <= 0) {
            return;
        }

        Node *parent = &m_root;

        for(size_t i = 0; i < count; ++i) {
            const element_type &word = keyword[i];

            typename std::map<element_type, Node>::iterator it = parent->CHILDREN.find(word);

            if(it != parent->CHILDREN.end()) {
                parent = &it->second;
            } else {
                std::pair<element_type, Node> new_pair;
                new_pair.first = word;
                new_pair.second.ELEM = word;

                parent = &(parent->CHILDREN.insert(parent->CHILDREN.end(), std::move(new_pair)))->second;
            }
        }

        parent->END = true;
    }

    // return matched_number - 1 (-1 if not found)
    ssize_t CheckFirst(element_type *data, size_t count, size_t first) {
        Node *parent = &m_root;

        for(size_t i = first; i < count; ++i) {
            const element_type &word = data[i];

            typename std::map<element_type, Node>::iterator it = parent->CHILDREN.find(word);

            if(it == parent->CHILDREN.end()) {
                return -1;
            }

            parent = &it->second;

            if(parent->END) {
                // [first, i] matched
                return i - first;
            }
        }

        return -1;
    }

    size_t CheckAndReplace(element_type *data, size_t count, const element_type &replacement) {
        size_t ret = 0;

        for(size_t i = 0; i < count; ++i) {
            ssize_t matched = CheckFirst(data, count, i);

            if(matched < 0) {
                continue;
            }

            // [i, i + matched] replaced
            for(size_t k = i; k <= i + matched; ++k) {
                data[k] = replacement;
            }

            ret += matched + 1;
            i += matched;
        }

        return ret;
    }

private:
    struct Node {
        element_type ELEM;
        bool END = false;

        std::map<element_type, Node> CHILDREN;
    };

    Node m_root;
};


#endif
