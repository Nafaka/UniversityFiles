#ifndef ADS_SET_H
#define ADS_SET_H

#include <functional>
#include <algorithm>
#include <iostream>
#include <stdexcept>

template <typename Key, size_t N = 7>
class ADS_set {
public:
//    class /* iterator type (implementation-defined) */;
    using value_type = Key;
    using key_type = Key;
    using reference = value_type &;
    using const_reference = const value_type &;
    using size_type = size_t;
    using difference_type = std::ptrdiff_t;
//    using const_iterator = /* iterator type */;
//    using iterator = const_iterator;
//    using key_compare = std::less<key_type>;                         // B+-Tree
    using key_equal = std::equal_to<key_type>;                       // Hashing
    using hasher = std::hash<key_type>;                              // Hashing
private:
    struct Element{
        key_type key;
        Element *next {nullptr};
        Element(const key_type& key, Element* next): key(key), next(next){}
    };
    Element **table = new Element*[N] {nullptr};
    size_type elementSize{0};
    size_type tableSize{N};
    float lf {0.7};
    void add(const key_type& key);
    Element *locate(const key_type& key) const;
    size_type hash_func(const key_type& key)  const {return hasher{}(key) % tableSize;}
    void resize();
public:
    ADS_set() {}                                                                           // PH1
    ADS_set(std::initializer_list<key_type> ilist) { insert(ilist); }                       // PH1
    template<typename InputIt> ADS_set(InputIt first, InputIt last) { insert(first, last);}  // PH1
//    ADS_set(const ADS_set &other);

//    ~ADS_set();

//    ADS_set &operator=(const ADS_set &other);
//    ADS_set &operator=(std::initializer_list<key_type> ilist);

    size_type size() const  { return elementSize;}                                                   // PH1
    bool empty() const {  return elementSize == 0; }                                                      // PH1

    void insert(std::initializer_list<key_type> ilist) { insert(ilist.begin(), ilist.end());}        // PH1
//    std::pair<iterator,bool> insert(const key_type &key);
    template<typename InputIt> void insert(InputIt first, InputIt last){
        for(; first != last; ++first){
            add(*first);
        }
    }                                                                                               // PH1

   void clear(){
        for(size_type i = 0; i < N; ++i){
            while (table[i] != nullptr){
                Element *next = table[i]->next;
                delete table[i];
                table[i] = next;
            }
        }
    }
//    size_type erase(const key_type &key);

    size_type count(const key_type &key) const {
        return locate(key) != nullptr;
    }                                                                                           // PH1
//    iterator find(const key_type &key) const;

    /*void swap(ADS_set &other) {
        swap(table, other.table);
    }*/

//    const_iterator begin() const;
//    const_iterator end() const;

    void dump(std::ostream &o = std::cerr) const{
        for(size_type i = 0; i < tableSize; ++i){
            o << "[" << i << "] ";
            for(Element *e = table[i]; e != nullptr; e = e->next){
                o << " -> " << e->key;
            }
            o << "\n";
        }
    }

//    friend bool operator==(const ADS_set &lhs, const ADS_set &rhs);
//    friend bool operator!=(const ADS_set &lhs, const ADS_set &rhs);
};


//New implemented functions

template <typename Key, size_t N>
void ADS_set<Key,N>::add(const key_type &key){
    size_type index = hash_func(key);
    if (locate(key) == nullptr) {
        table[index] = new Element(key, table[index]);
        ++elementSize;
        if (static_cast<float>(elementSize) / tableSize > lf) {
            resize();
        }
    }
}
template <typename Key, size_t N>
typename ADS_set<Key,N>::Element *ADS_set<Key,N>::locate(const key_type& key) const {
    size_type index = hash_func(key);
    for (Element *e = table[index]; e != nullptr; e = e->next) {
        if (key_equal{}(e->key, key))
            return e;
    }
    return nullptr;
}
template <typename Key, size_t N>
void ADS_set<Key, N>::resize() {
    size_type newTableSize = (tableSize * 2)+1;
    Element** new_table = new Element*[newTableSize]{nullptr};

    for (size_type i = 0; i < tableSize; ++i) {
        Element* current = table[i];
        while (current != nullptr) {
            size_type newIndex = hasher{}(current->key) % newTableSize;
            Element* temp = current->next;
            current->next = new_table[newIndex];
            new_table[newIndex] = current;
            current = temp;
        }
    }
    delete[] table;
    table = new_table;
    tableSize = newTableSize;
}

//template <typename Key, size_t N>
//class ADS_set<Key,N>::/* iterator type */ {
/*public:
    using value_type = Key;
    using difference_type = std::ptrdiff_t;
    using reference = const value_type &;
    using pointer = const value_type *;
    using iterator_category = std::forward_iterator_tag;
*/
//    explicit /* iterator type */(/* implementation-dependent */);
//    reference operator*() const;
//    pointer operator->() const;
//    /* iterator type */ &operator++();
//    /* iterator type */ operator++(int);
//    friend bool operator==(const /* iterator type */ &lhs, const /* iterator type */ &rhs);
//    friend bool operator!=(const /* iterator type */ &lhs, const /* iterator type */ &rhs);
//};

template <typename Key, size_t N>
void swap(ADS_set<Key,N> &lhs, ADS_set<Key,N> &rhs) { lhs.swap(rhs); }

#endif // ADS_SET_H