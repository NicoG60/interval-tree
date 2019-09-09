#ifndef INTERVAL_TREE_H
#define INTERVAL_TREE_H

#include <algorithm>
#include <vector>
#include <utility>

template<
    typename Key,
    typename Value,
    typename Comp = std::less<Key>
>
class interval_tree
{
public:
    class iterator;
    class reverse_iterator;
    typedef Key                                   bound_type;
    typedef std::pair<bound_type, bound_type>     key_type;
    typedef Value                                 mapped_type;
    typedef Comp                                  key_compare;

    typedef std::size_t                           size_type;
    typedef std::ptrdiff_t                        difference_type;
    typedef std::pair<key_type, mapped_type>      value_type;
    typedef value_type&                           reference;
    typedef const value_type&                     const_reference;
    typedef const iterator                        const_iterator;
    typedef const reverse_iterator                reverse_const_iterator;

private:
    struct node
    {
        node* parent = nullptr;
        node* left = nullptr;
        node* right = nullptr;

        bound_type max;
        value_type key_value;
    };

    class comparator
    {
    public:
        comparator(const key_compare& comp = key_compare()) : comp(comp) {;}
        comparator(const comparator& copy) = default;
        comparator(comparator&& move) = default;

        comparator& operator=(const comparator& copy) = default;
        comparator& operator=(comparator&& move) = default;

        bool less(const bound_type& a, const bound_type& b) const
        {
            return comp(a, b);
        }

        bool less(const key_type& a, const key_type& b) const
        {
            return less(a.first, b.first) || (equal(a.first, b.first) && less(a.second, b.second));
        }

        bool less_eq(const bound_type& a, const bound_type& b) const
        {
            return !less(b, a);
        }

        bool less_eq(const key_type& a, const key_type& b) const
        {
            return !less(b, a);
        }

        bool greater(const bound_type& a, const bound_type& b) const
        {
            return less(b, a);
        }

        bool greater(const key_type& a, const key_type& b) const
        {
            return less(b, a);
        }

        bool greater_eq(const bound_type& a, const bound_type& b) const
        {
            return !less(a, b);
        }

        bool greater_eq(const key_type& a, const key_type& b) const
        {
            return !less(a, b);
        }

        bool equal(const bound_type& a, const bound_type& b) const
        {
            return !less(a, b) && !less(b, a);
        }

        bool equal(const key_type& a, const key_type& b) const
        {
            return !less(a, b) && !less(b, a);
        }

        bool not_equal(const bound_type& a, const bound_type& b) const
        {
            return !equal(a, b);
        }

        bool not_equal(const key_type& a, const key_type& b) const
        {
            return !equal(a, b);
        }

        key_compare comp;
    };

public:
    class iterator
    {
        friend class interval_tree;
    public:
        typedef interval_tree::difference_type  difference_type;
        typedef interval_tree::value_type       value_type;
        typedef interval_tree::value_type*      pointer;
        typedef const pointer                   const_pointer;
        typedef interval_tree::reference        reference;
        typedef interval_tree::const_reference  const_reference;
        typedef std::bidirectional_iterator_tag iterator_categroy;

        iterator() = default;
        iterator(const iterator& copy) = default;
        iterator(iterator&& move) = default;

        iterator& operator=(const iterator& copy) = default;
        iterator& operator=(iterator&& move) = default;

        iterator& operator++()
        {
            if(tree)
                node = tree->next(node);

            return *this;
        }

        iterator operator++(int)
        {
            auto tmp = *this;
            ++(*this);
            return tmp;
        }

        iterator& operator--()
        {
            if(tree)
                node = tree->prev(node);

            return *this;
        }

        iterator operator--(int)
        {
            auto tmp = *this;
            ++(*this);
            return tmp;
        }

        bool operator==(const iterator& other) const
        {
            return tree == other.tree && node == other.node;
        }

        bool operator!=(const iterator& other) const
        {
            return !operator==(other);
        }

        reference operator*()
        {
            return node->key_value;
        }

        const_reference operator*() const
        {
            return node->key_value;
        }

        pointer operator->()
        {
            return &(node->key_value);
        }

        const_pointer operator->() const
        {
            return &(node->key_value);
        }

    protected:
        iterator(interval_tree* tree, node* node = nullptr) : node(node), tree(tree) {;}

    protected:
        node* node = nullptr;
        interval_tree* tree = nullptr;
    };

    class reverse_iterator : public iterator
    {
        friend class interval_tree;

    public:
        reverse_iterator() = default;
        reverse_iterator(const reverse_iterator& copy) = default;
        reverse_iterator(reverse_iterator&& move) = default;

        reverse_iterator& operator++()
        {
            if(this->tree)
                this->node = this->tree->prev(this->node);

            return *this;
        }

        reverse_iterator operator++(int)
        {
            auto tmp = *this;
            ++(*this);
            return tmp;
        }

        reverse_iterator& operator--()
        {
            if(this->tree)
                this->node = this->tree->next(this->node);

            return *this;
        }

        reverse_iterator operator--(int)
        {
            auto tmp = *this;
            ++(*this);
            return tmp;
        }


    protected:
        reverse_iterator(interval_tree* tree, node* node = nullptr) :
            iterator(tree, node) {;}
    };

public:
    interval_tree() {;}

    explicit interval_tree(const Comp& comp) : c(comp) {;}

    template<class InputIt>
    interval_tree(InputIt first,
                  InputIt last,
                  const Comp& comp = Comp()) :
        c(comp)
    {
        insert(first, last);
    }

    interval_tree(const interval_tree<Key, Value>& copy) :
        root(clone(copy.root)),
        c(copy.c)
    {;}

    interval_tree(interval_tree<Key, Value>&& move) :
        root(std::move(move.root)),
        c(std::move(move.c))
    {;}

    interval_tree(std::initializer_list<value_type> init,
                  const Comp& comp = Comp()) :
        c(comp)
    {
        insert(init);
    }

    ~interval_tree()
    {
        clear();
    }

    interval_tree<Key, Value>& operator=(const interval_tree<Key, Value>& copy)
    {
        clear();
        root = clone(copy.root);
        c = copy.c;
        return *this;
    }

    interval_tree<Key, Value>& operator=(interval_tree<Key, Value>&& move)
    {
        root = std::move(move.root);
        c = std::move(move.c);
        return *this;
    }

    interval_tree<Key, Value>& operator=(std::initializer_list<value_type> list)
    {
        clear();
        insert(list);
        return *this;
    }

    Value& at(const key_type& key)
    {
        node* n = findFirst(root, key);
        if(n)
            return n->key_value.second;
        else
            throw std::out_of_range("Key does't exists");
    }

    const Value& at(const key_type& key) const
    {
        node* n = findFirst(root, key);
        if(n)
            return n->key_value.second;
        else
            throw std::out_of_range("Key does't exists");
    }

    void at(const bound_type& point, std::vector<value_type>& results) const
    {
        in({point, point}, results);
    }

    void in(const bound_type& start, const bound_type& end, std::vector<value_type>& results) const
    {
        in({start, end}, results);
    }

    void in(const key_type& interval, std::vector<value_type>& results) const
    {
        search(root, interval, results);
    }

    Value& operator[](const key_type& key)
    {
        node* n = findFirst(root, key);
        if(n)
            return n->key_value.second;
        else
        {
            auto it = insert({key, mapped_type()});
            return it->second;
        }
    }

    Value& operator[](key_type&& key)
    {
        node* n = findFirst(root, key);
        if(n)
            return n->key_value.second;
        else
        {
            auto it = insert({key, mapped_type()});
            return it->second;
        }
    }

    iterator begin() noexcept
    {
        return iterator(this, leftest(root));
    }

    const_iterator begin() const noexcept
    {
        return cbegin();
    }

    const_iterator cbegin() const noexcept
    {
        return const_iterator(this, leftest(root));
    }

    reverse_iterator rbegin() noexcept
    {
        return reverse_iterator(this, rightest(root));
    }

    reverse_const_iterator rbegin() const noexcept
    {
        return crbegin();
    }

    reverse_const_iterator crbegin() const noexcept
    {
        return reverse_const_iterator(this, rightest(root));
    }

    iterator end() noexcept
    {
        return iterator(this);
    }

    const_iterator end() const noexcept
    {
        return cend();
    }

    const_iterator cend() const noexcept
    {
        return const_iterator(this);
    }

    reverse_iterator rend() noexcept
    {
        return reverse_iterator(this);
    }

    reverse_const_iterator rend() const noexcept
    {
        return cend();
    }

    reverse_const_iterator crend() const noexcept
    {
        return reverse_const_iterator(this);
    }

    bool empty() const noexcept
    {
        return count(root) == 0;
    }

    size_type size() const noexcept
    {
        return count(root);
    }

    void clear() noexcept
    {
        if(root)
        {
            deleteChild(root);
            delete root;
            root = nullptr;
        }
    }

    iterator insert(const value_type& value)
    {
        auto interval = value.first;

        if(c.greater(interval.first, interval.second))
            std::swap(interval.first, interval.second);

        node* n = new node;
        n->key_value = {interval, value.second};

        if(root)
            insert(root, n);
        else
            root = n;

        return iterator(this, n);
    }

    iterator insert(value_type&& value)
    {
        auto& interval = value.first;

        if(c.greater(interval.first, interval.second))
            std::swap(interval.first, interval.second);

        node* n = new node;
        n->key_value = value;

        if(root)
            insert(root, n);
        else
            root = n;

        return iterator(this, n);
    }

    template<class InputIt>
    void insert(InputIt first, InputIt last)
    {
        while(first != last)
            insert(*first++);
    }

    void insert(std::initializer_list<value_type> list)
    {
        for(auto& v : list)
            insert(v);
    }

    template<class... Args>
    iterator emplace(const key_type& key, Args&& ...args)
    {
        return insert({key, mapped_type(std::forward<Args>(args)...)});
    }

    template<class... Args>
    iterator emplace(key_type&& key, Args&& ...args)
    {
        return insert({key, mapped_type(std::forward<Args>(args)...)});
    }

    iterator erase(const_iterator pos)
    {
        return iterator(this, remove(pos.node));
    }

    void swap(interval_tree<Key, Value>& other)
    {
        std::swap(root, other._root);
    }

    iterator find(const key_type& k)
    {
        return iterator(this, findFirst(root, k));
    }

    const_iterator find(const key_type& k) const
    {
        return const_iterator(this, findFirst(root, k));
    }

    iterator find_last(const key_type& k)
    {
        return iterator(this, findLast(root, k));
    }

    const_iterator find_last(const key_type& k) const
    {
        return const_iterator(this, findLast(root, k));
    }

private:
    node* clone(node* n, node* p = nullptr) const
    {
        if(!n)
            return nullptr;

        node* r = new node;
        r->parent = p;
        r->left = clone(n->left, r);
        r->right = clone(n->right, r);
        r->key_value = n->key_value;
        r->max = n->max;
        return r;
    }

    void updateMax(node* n)
    {
        bound_type l = n->left ? n->left->max : 0;
        bound_type r = n->right ? n->right->max : 0;

        n->max = std::max(std::max(l, r, c.comp), n->key_value.first.second, c.comp);

        if(n->parent)
            updateMax(n->parent);
    }

    void deleteChild(node* n)
    {
        if(!n)
            return;

        if(n->left)
        {
            deleteChild(n->left);
            delete n->left;
        }

        if(n->right)
        {
            deleteChild(n->right);
            delete n->right;
        }
    }

    size_type count(node* n) const
    {
        if(!n)
            return 0;

        size_type r = 1;

        if(n->left)
            r += count(n->left);

        if(n->right)
            r += count(n->right);

        return r;
    }

    node* leftest(node* n)
    {
        if(!n)
            return nullptr;

        if(n->left)
            return leftest(n->left);

        return n;
    }

    node* rightest(node* n)
    {
        if(!n)
            return nullptr;

        if(n->right)
            return rightest(n->right);

        return n;
    }

    node* next(node* n)
    {
        if(!n)
            return nullptr;

        if(n->right)
            return leftest(n->right);

        while(n->parent)
        {
            node* last = n;
            n = n->parent;

            if(last == n->left)
                return n;
        }

        return nullptr;
    }

    node* prev(node* n)
    {
        if(!n)
            return nullptr;

        if(n->left)
            return rightest(n->left);

        while(n->parent)
        {
            node* last = n;
            n = n->parent;

            if(last == n->right)
                return n;
        }

        return nullptr;
    }

    int balanceFactor(node* n) const
    {
        return (n->right ? heigh(n->right) : 0)
               - (n->left ? heigh(n->left) : 0);
    }

    int heigh(node* n) const
    {
        int l = n->left ? heigh(n->left) : 0;
        int r = n->right ? heigh(n->right) : 0;

        return std::max(l, r) + 1;
    }

    node* rotateRight(node* n)
    {
        if(!n)
            return nullptr;

        if(!n->left)
            return n;

        node* tmp = n->left;

        n->left = tmp->right;
        if(n->left)
            n->left->parent = n;

        tmp->parent = n->parent;
        if(tmp->parent)
        {
            if(n == tmp->parent->left)
                tmp->parent->left = tmp;
            else
                tmp->parent->right = tmp;
        }

        tmp->right = n;
        n->parent = tmp;

        updateMax(tmp);

        return tmp;
    }

    node* rotateLeft(node* n)
    {
        if(!n)
            return nullptr;

        if(!n->right)
            return n;

        node* tmp = n->right;

        n->right = tmp->left;
        if(n->right)
            n->right->parent = n;

        tmp->parent = n->parent;
        if(tmp->parent)
        {
            if(n == tmp->parent->left)
                tmp->parent->left = tmp;
            else
                tmp->parent->right = tmp;
        }

        tmp->left = n;
        n->parent = tmp;

        updateMax(tmp);

        return tmp;
    }

    node* findRoot(node* n)
    {
        if(!n)
            return nullptr;

        if(n->parent)
            return findRoot(n->parent);

        return this;
    }

    node* findFirst(node* n, const key_type& k)
    {
        if(!n)
            return nullptr;

        if(c.equal(n->key_value.first, k))
            return n;

        if(c.less(k, n->key_value.first))
            return findFirst(n->left, k);
        else
            return findFirst(n->right, k);
    }

    node* findLast(node* n, const key_type& k)
    {
        if(c.less(k, n->key_value.first) && n->left)
            return findLast(n->left, k);
        else if(c.greater_eq(k, n->key_value.first) && n->right)
            return findLast(n->right, k);
        else
            return n;
    }

    bool intervalOverlaps(const key_type& a, const key_type& b) const
    {
        return c.less_eq(a.first, b.second) && c.greater_eq(a.second, b.first);
    }

    void search(node* n, const key_type& interval,
                std::vector<value_type>& results) const
    {
        if(!n)
            return;

        if(c.greater(interval.first, n->max))
            return;

        if(n->left)
            search(n->left, interval, results);

        if(intervalOverlaps(interval, n->key_value.first))
            results.push_back(n->key_value);

        if(c.less(interval.second, n->key_value.first.first))
            return;

        if(n->right)
            search(n->right, interval, results);
    }


    void insert(node* r, node* n)
    {
        if(!r || !n)
            return;

        node* p = findLast(r, n->key_value.first);

        n->parent = p;

        if(c.less(n->key_value.first, p->key_value.first))
            p->left = n;
        else
            p->right = n;

        updateMax(n);

        rebalance(p);
    }

    node* remove(node* n)
    {
        node* r = next(n);

        if(n->left && n->right)
        {
            node* s = leftest(n->right);
            n->key_value = s->key_value;
            n->max = s->max;
            remove(s);
            return r;
        }
        else if(n->left)
            replaceInParent(n, n->left);
        else if(n->right)
            replaceInParent(n, n->right);
        else
            replaceInParent(n, nullptr);

        delete n;
        return r;
    }

    void replaceInParent(node* n, node* v)
    {
        if(v)
            v->parent = n->parent;

        if(n->parent)
        {
            if(n == n->parent->left)
                n->parent->left = v;
            else
                n->parent->right = v;

            rebalance(n->parent);
        }
        else
            root = v;

        if(v)
            updateMax(v);
    }

    void rebalance(node* n)
    {
        if(balanceFactor(n) < -1)
        {
            if(n->left && balanceFactor(n->left) > 0)
                n->left = rotateLeft(n->left);

            n = rotateRight(n);
        }
        else if(balanceFactor(n) > 1)
        {
            if(n->right && balanceFactor(n->right) < 0)
                n->right = rotateRight(n->right);

            n = rotateLeft(n);
        }

        if(n->parent)
            rebalance(n->parent);
        else
            root = n;
    }

private:
    node* root = nullptr;
    comparator c;
};

#endif // INTERVAL_TREE_H
