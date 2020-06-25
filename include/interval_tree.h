#ifndef INTERVAL_TREE_H
#define INTERVAL_TREE_H

#include <algorithm>
#include <vector>
#include <utility>

template<
    typename Key,
    typename T,
    typename Compare = std::less<Key>,
    typename std::enable_if<std::is_arithmetic<Key>::value, int>::type = 0
>
class interval_tree
{
public:
    // ====== TYPEDEFS =========================================================
    typedef Key                                    bound_type;
    typedef std::pair<Key, Key>                    key_type;
    typedef T                                      mapped_type;

    typedef std::size_t                            size_type;
    typedef std::ptrdiff_t                         difference_type;
    typedef std::pair<key_type, mapped_type>       value_type;
    typedef value_type*                            pointer;
    typedef const value_type*                      const_pointer;
    typedef value_type&                            reference;
    typedef const value_type&                      const_reference;



    // ====== NODE =============================================================
    class node
    {
        friend class interval_tree;

        node() = default;
        template<class... Args>
        node(Args&& ...args) : data(std::forward<Args>(args)...) {}

        inline const key_type&    key()   { return data.first;   }
        inline const bound_type&  lower() { return key().first;  }
        inline const bound_type&  upper() { return key().second; }
        inline       mapped_type& value() { return data.second;  }

        node* parent = nullptr;
        node* left   = nullptr;
        node* right  = nullptr;

        int         height = 1;
        bound_type  max    = 0;
        value_type  data;
    };

    // ====== KEY COMPARE ======================================================
    class comparator
    {
        friend class interval_tree;

    public:
        inline bool operator()(const bound_type& lhs, const bound_type& rhs) const { return less(lhs, rhs); }
        inline bool operator()(const key_type&   lhs, const key_type&   rhs) const { return less(lhs, rhs); }
        inline bool operator()(const value_type& lhs, const value_type& rhs) const { return less(lhs, rhs); }

        inline bool less(const bound_type& lhs, const bound_type& rhs) const { return comp(lhs, rhs); }
        inline bool less(const key_type& lhs, const key_type& rhs) const
        {
            return less(lhs.first, rhs.first) || (eq(rhs.first, lhs.first) && less(lhs.second, rhs.second));
        }
        inline bool less(const value_type& lhs, const value_type& rhs) const { return less(lhs.first, rhs.second); }

        inline bool greater(const bound_type& lhs, const bound_type& rhs) const { return less(rhs, lhs); }
        inline bool greater(const key_type&   lhs, const key_type&   rhs) const { return less(rhs, lhs); }
        inline bool greater(const value_type& lhs, const value_type& rhs) const { return less(rhs, lhs); }

        inline bool less_eq(const bound_type& lhs, const bound_type& rhs) const { return !greater(lhs, rhs); }
        inline bool less_eq(const key_type&   lhs, const key_type&   rhs) const { return !greater(lhs, rhs); }
        inline bool less_eq(const value_type& lhs, const value_type& rhs) const { return !greater(lhs, rhs); }

        inline bool greater_eq(const bound_type& lhs, const bound_type& rhs) const { return !less(lhs, rhs); }
        inline bool greater_eq(const key_type&   lhs, const key_type&   rhs) const { return !less(lhs, rhs); }
        inline bool greater_eq(const value_type& lhs, const value_type& rhs) const { return !less(lhs, rhs); }

        inline bool eq(const bound_type& lhs, const bound_type& rhs) const { return !less(lhs, rhs) && !greater(lhs, rhs); }
        inline bool eq(const key_type&   lhs, const key_type&   rhs) const { return !less(lhs, rhs) && !greater(lhs, rhs); }
        inline bool eq(const value_type& lhs, const value_type& rhs) const { return !less(lhs, rhs) && !greater(lhs, rhs); }

        inline bool neq(const bound_type& lhs, const bound_type& rhs) const { return !eq(lhs, rhs); }
        inline bool neq(const key_type&   lhs, const key_type&   rhs) const { return !eq(lhs, rhs); }
        inline bool neq(const value_type& lhs, const value_type& rhs) const { return !eq(lhs, rhs); }

    protected:
        comparator() = default;
        comparator(Compare c) : comp(c) {}

        Compare comp;
    };

    typedef comparator key_compare;
    typedef comparator value_compare;



    // ====== ITERATOR =========================================================
    class iterator
    {
        friend class interval_tree;

    public:
        typedef interval_tree::difference_type  difference_type;
        typedef interval_tree::value_type       value_type;
        typedef interval_tree::pointer          pointer;
        typedef interval_tree::const_pointer    const_pointer;
        typedef interval_tree::reference        reference;
        typedef interval_tree::const_reference  const_reference;
        typedef std::bidirectional_iterator_tag iterator_category;

    protected:
        iterator(interval_tree* t, node* n = nullptr) : tree(t), n(n) {}

    public:
        iterator() = default;

        inline void swap(iterator& other) noexcept
        {
            std::swap(tree, other.tree);
            std::swap(n, other.n);
        }

        inline bool operator==(const iterator& other) const
        {
            return n == other.n;
        }

        inline bool operator!=(const iterator& other) const
        {
            return !(*this == other);
        }

        inline reference operator*()
        {
            return n->data;
        }

        inline pointer   operator->()
        {
            return &n->data;
        }

        inline const_reference operator*()  const
        {
            return n->data;
        }

        inline const_pointer   operator->() const
        {
            return &n->data;
        }

        inline iterator& operator++()
        {
            if(n)
                n = tree->next(n);
            else
                n = tree->leftest(n);

            return *this;
        }

        inline iterator  operator++(int)
        {
            iterator it(*this);
            ++*this;
            return it;
        }

        inline iterator& operator--()
        {
            if(n)
                n = tree->prev(n);
            else
                n = tree->rightest(n);

            return *this;
        }

        inline iterator  operator--(int)
        {
            iterator it(*this);
            --*this;
            return it;
        }

    protected:
        interval_tree* tree = nullptr;
        node*          n    = nullptr;
    };

    class const_iterator : public iterator
    {
        friend class interval_tree;
    public:
        typedef typename iterator::const_pointer   pointer;
        typedef typename iterator::const_reference reference;

    protected:
        const_iterator(interval_tree* t, node* n = nullptr) : iterator(t, n) {}

    public:
        const_iterator() = default;
    };

    class reverse_iterator : public iterator
    {
        friend class interval_tree;
    protected:
        reverse_iterator(interval_tree* t, node* n = nullptr) : iterator(t, n) {}

    public:
        reverse_iterator() = default;

        inline iterator& operator++()    { return iterator::operator--();  }
        inline iterator operator++(int)  { return iterator::operator--(0); }
        inline iterator& operator--()    { return iterator::operator++();  }
        inline iterator  operator--(int) { return iterator::operator++(0); }
    };

    class reverse_const_iterator : public const_iterator
    {
        friend class interval_tree;
    protected:
        reverse_const_iterator(interval_tree* t, node* n = nullptr) : const_iterator(t, n) {}

    public:
        reverse_const_iterator() = default;

        inline iterator& operator++()    { return iterator::operator--();  }
        inline iterator operator++(int)  { return iterator::operator--(0); }
        inline iterator& operator--()    { return iterator::operator++();  }
        inline iterator  operator--(int) { return iterator::operator++(0); }
    };




public:
    // ====== CONSTRUCTORS =====================================================
    interval_tree() = default;
    explicit interval_tree(const Compare& comp) : comp(comp) {}

    template<class InputIt>
    interval_tree(InputIt first, InputIt last, const Compare& comp = Compare()) :
        comp(comp)
    {
        insert(first, last);
    }

    interval_tree(const interval_tree<Key, T>& copy) { *this = copy; }
    interval_tree(interval_tree<Key, T>&& move) { *this = move; }
    interval_tree(std::initializer_list<value_type> ilist, const Compare& comp = Compare()) :
        comp(comp)
    {
        insert(ilist);
    }



    // ====== DESTRUCTOR =======================================================
    ~interval_tree()
    {
        clear();
    }


    // ====== ASSIGNMENTS ======================================================
    interval_tree& operator=(const interval_tree& copy)
    {
        if(root)
            delete_node(root);

        root = clone(copy.root);
        node_count = copy.node_count;
        comp = copy.comp;

        return *this;
    }

    interval_tree& operator=(interval_tree&& move) noexcept(std::is_nothrow_move_assignable<Compare>::value)
    {
        if(root)
            delete_node(root);

        root = std::move(move.root);
        node_count = std::move(move.node_count);
        comp = std::move(move.comp);

        return *this;
    }

    interval_tree& operator=(std::initializer_list<value_type> ilist)
    {
        clear();
        insert(ilist);

        return *this;
    }



    // ====== ITERATORS ========================================================
    inline iterator begin() noexcept
    {
        return iterator(this, root ? leftest(root) : nullptr);
    }

    inline const_iterator begin() const noexcept
    {
        return const_iterator(this, root ? leftest(root) : nullptr);
    }

    inline const_iterator cbegin() const noexcept
    {
        return const_iterator(this, root ? leftest(root) : nullptr);
    }

    inline iterator end() noexcept
    {
        return iterator(this);
    }

    inline const_iterator end() const noexcept
    {
        return const_iterator(this);
    }

    inline const_iterator cend() const noexcept
    {
        return const_iterator(this);
    }

    inline reverse_iterator rbegin() noexcept
    {
        return reverse_iterator(this, root ? rightest(root) : nullptr);
    }

    inline reverse_const_iterator rbegin() const noexcept
    {
        return reverse_const_iterator(this, root ? rightest(root) : nullptr);
    }

    inline reverse_const_iterator crbegin() const noexcept
    {
        return reverse_const_iterator(this, root ? rightest(root) : nullptr);
    }

    inline reverse_iterator rend() noexcept
    {
        return reverse_iterator(this);
    }

    inline reverse_const_iterator rend() const noexcept
    {
        return reverse_const_iterator(this);
    }

    inline reverse_const_iterator crend() const noexcept
    {
        return reverse_const_iterator(this);
    }



    // ====== CAPACITY =========================================================
    bool empty() const noexcept
    {
        return node_count = 0;
    }

    size_type size() const noexcept
    {
        return node_count;
    }

    size_type max_size() const noexcept
    {
        return std::numeric_limits<difference_type>::max();
    }



    // ===== MODIFIERS =========================================================
    void clear() noexcept
    {
        if(root)
        {
            delete_node(root);
            root = nullptr;
            node_count = 0;
        }
    }

    iterator insert(const value_type& value)
    {
        return emplace(value);
    }

    iterator insert(value_type&& value)
    {
        return emplace(std::forward<value_type>(value));
    }

    template<class P, std::enable_if<std::is_convertible<value_type, P&&>::value, int> = 0>
    iterator insert(P&& value)
    {
        return emplace(std::forward(value));
    }

    iterator insert(const_iterator hint, const value_type& value)
    {
        return emplace_hint(hint, value);
    }

    iterator insert(const_iterator hint, value_type&& value)
    {
        return emplace_hint(hint, std::forward(value));
    }

    template<class P, std::enable_if<std::is_convertible<value_type, P&&>::value, int> = 0>
    iterator insert(const_iterator hint, P&& value)
    {
        return emplace_hint(hint, std::forward<P>(value));
    }

    template<class InputIt>
    void insert(InputIt first, InputIt last)
    {
        while(first != last)
        {
            emplace(*first);
            ++first;
        }
    }

    void insert(std::initializer_list<value_type> ilist)
    {
        insert(ilist.begin(), ilist.end());
    }

    template<class... Args>
    iterator emplace(Args&& ...args)
    {
        node* n = new node(std::forward<Args>(args)...);

        if(root)
            insert(n);
        else
        {
            node_count ++;
            root = n;
        }

        return iterator(this, n);
    }

    template<class... Args>
    iterator emplace_hint(const_iterator hint, Args&& ...args)
    {
        node* h = hint.n;

        if(!h || !h->parent)
            return emplace(std::forward<Args>(args)...);

        node* n = new node(std::forward<Args>(args)...);

        insert(h->parent, n);

        return iterator(this, n);
    }

    iterator erase(const_iterator pos)
    {
        return iterator(this, remove(pos.n));
    }

    iterator erase(iterator pos)
    {
        return iterator(this, remove(pos.n));
    }

    iterator erase(const_iterator first, const_iterator last)
    {
        node* n = first.n;

        while(first != last)
        {
            n = remove(first.n);
            ++first;
        }

        return iterator(this, n);
    }

    size_type erase(const key_type& key)
    {
        if(!root)
            return 0;

        node* n = find(root, key);

        if(!n)
            return 0;

        size_type r = 0;

        do {
            n = remove(n);
            ++r;
        } while(n && comp.eq(n->key(), key));

        return r;
    }

    void swap(interval_tree& other) noexcept(std::is_nothrow_swappable<Compare>::value)
    {
        std::swap(root, other.root);
    }



    // ====== LOOKUP ===========================================================

    size_type count(const key_type& key) const
    {
        return std::distance(lower_bound(key), upper_bound(key));
    }

    void at(const Key& point, std::vector<iterator>& results)
    {
        return in(point, point, results);
    }

    void at(const Key& point, std::vector<const_iterator>& results) const
    {
        return in(point, point, results);
    }

    void in(const Key& start, const Key& end, std::vector<iterator>& results)
    {
        return in({start, end}, results);
    }

    void in(const Key& start, const Key& end, std::vector<const_iterator>& results) const
    {
        return in({start, end}, results);
    }

    void in(const key_type& interval, std::vector<iterator>& results)
    {
        if(root)
            search(root, interval, results);
    }

    void in(const key_type& interval, std::vector<const_iterator>& results) const
    {
        if(root)
            search(root, interval, results);
    }

    iterator find(const key_type& k)
    {
        return _find<iterator>(k);
    }

    const_iterator find(const key_type& k) const
    {
        return _find<const_iterator>(k);
    }

    std::pair<iterator,iterator> equal_range(const key_type& key)
    {
        return _equal_range<iterator>(key);
    }

    std::pair<const_iterator,const_iterator> equal_range(const key_type& key) const
    {
        return _equal_range<const_iterator>(key);
    }

    iterator lower_bound(const key_type& k)
    {
        return _lower_bound<iterator>(k);
    }

    const_iterator lower_bound(const key_type& k) const
    {
        return _lower_bound<const_iterator>(k);
    }

    iterator upper_bound(const key_type& k)
    {
        return _upper_bound<iterator>(k);
    }

    const_iterator upper_bound(const key_type& k) const
    {
        return _upper_bound<const_iterator>(k);
    }



    // ====== OBSERVER =========================================================
    key_compare   key_comp() const
    {
        return comp;
    }

    value_compare value_comp() const
    {
        return comp;
    }



    // ====== PRIVATE ==========================================================
private:
    node* clone(node* n, node* p = nullptr) const
    {
        node* nn = new node(n->data);
        nn->parent = p;
        nn->max = n->max;
        nn->height = n->height;

        if(n->left)
            nn->left = clone(n->left, nn);

        if(n->right)
            nn->right = clone(n->right, nn);

        return nn;
    }

    void update_height_max(node* n)
    {
        bound_type m = n->upper();
        bound_type h = 1;

        if(n->left)
        {
            m = std::max(m, n->left->max);
            h = std::max(h, n->left->height + 1);
        }

        if(n->right)
        {
            m = std::max(m, n->right->max);
            h = std::max(h, n->right->height + 1);
        }

        if(n->max != m || n->height != h || (!n->left && !n->right))
        {
            n->max = m;
            n->height = h;

            if(n->parent)
                update_height_max(n->parent);
        }
    }

    void delete_node(node* n)
    {
        delete_child(n);
        delete n;
    }

    void delete_child(node* n)
    {
        if(n->left)
        {
            delete_node(n->left);
            n->left = nullptr;
        }

        if(n->right)
        {
            delete_node(n->right);
            n->right = nullptr;
        }
    }

    inline bool is_left_child(node* n) const
    {
        return n == n->parent->left;
    }

    inline node* leftest(node* n) const
    {
        while(n->left)
            n = n->left;

        return n;
    }

    inline node* rightest(node* n) const
    {
        while(n->right)
            n = n->right;

        return n;
    }

    inline node* next(node* n) const
    {
        if(n->right)
            return leftest(n->right);

        while(n->parent && !is_left_child(n))
            n = n->parent;

        return n->parent;
    }

    inline node* prev(node* n) const
    {
        if(n->left)
            return rightest(n->left);

        while(n->parent && is_left_child(n))
            n = n->parent;

        return n->parent;
    }

    inline int balance_factor(node* n) const
    {
        return (n->right ? n->right->height : 0)
               - (n->left ? n->left->height : 0);
    }

    node* rotate_right(node* n)
    {
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

        update_height_max(n);

        return tmp;
    }

    node* rotate_left(node* n)
    {
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

        update_height_max(n);

        return tmp;
    }

    node* lower_bound(node* n, const key_type& k) const
    {
        node* r = nullptr;
        while(n)
        {
            if(!comp.less(n->key(), k))
            {
                r = n;
                n = n->left;
            }
            else
                n = n->right;
        }

        return r;
    }

    node* upper_bound(node* n, const key_type& k) const
    {
        node* r = nullptr;
        while(n)
        {
            if(comp.greater(n->key(), k))
            {
                r = n;
                n = n->left;
            }
            else
                n = n->right;
        }

        return r;
    }

    node* find_last(node* n, const key_type& k) const
    {
        node* r = n;

        while(n)
        {
            r = n;
            if(comp(k, n->key()))
                n = n->left;
            else
                n = n->right;
        }

        return r;
    }

    template<class IT>
    void search(node* n, const key_type& interval, std::vector<IT>& r) const
    {
        // if interval is to the right of every node, there wont be any match
        if(comp.greater(interval.first, n->max))
            return;

        // search the left side
        if(n->left)
            search(n->left, interval, r);

        // if the current node matches
        if(intervalOverlaps(interval, n->key()))
            r.push_back(IT(const_cast<interval_tree*>(this), n));

        // if interval is to the left of this one, they wont be any match to the right
        if(comp.less(interval.second, n->lower()))
            return;

        if(n->right)
            search(n->right, interval, r);
    }

    void insert(node* n)
    {
        node* p = find_last(root, n->key());

        n->parent = p;

        if(comp.less(n->key(), p->key()))
            p->left = n;
        else
            p->right = n;

        update_height_max(n);

        rebalance(p);

        node_count++;
    }

    node* remove(node* n)
    {
        node* r = next(n);

        if(n->left && n->right)
        {
            node* s = leftest(n->right);
            n->data = s->data;
            n->max = s->max;
            remove(s);
            return r;
        }
        else if(n->left)
            replace_in_parent(n, n->left);
        else if(n->right)
            replace_in_parent(n, n->right);
        else
            replace_in_parent(n, nullptr);

        delete n;
        node_count--;
        return r;
    }

    void replace_in_parent(node* n, node* v)
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
            update_height_max(v);
    }

    void rebalance(node* n)
    {
        int f = balance_factor(n);
        if(f < -1)
        {
            if(n->left && balance_factor(n->left) > 0)
                n->left = rotate_left(n->left);

            n = rotate_right(n);
        }
        else if(f > 1)
        {
            if(n->right && balance_factor(n->right) < 0)
                n->right = rotate_right(n->right);

            n = rotate_left(n);
        }

        if(n->parent)
            rebalance(n->parent);
        else
            root = n;
    }

    bool intervalOverlaps(const key_type& a, const key_type& b) const
    {
        return comp.less_eq(a.first, b.second) && comp.greater_eq(a.second, b.first);
    }

    template<class IT>
    IT _find(const key_type& k) const
    {
        node* n = lower_bound(root, k);

        if(n && comp.eq(n->key(), k))
            return n;

        return nullptr;
    }

    template<class IT>
    IT _lower_bound(const key_type& k) const
    {
        return IT(this, lower_bound(root, k));
    }

    template<class IT>
    IT _upper_bound(const key_type& k) const
    {
        return IT(this, upper_bound(root, k));
    }

    template<class IT>
    std::pair<IT, IT> _equal_range(const key_type& k) const
    {
        return {_lower_bound<IT>(k), _upper_bound<IT>(k)};
    }

private:
    node*      root = nullptr;
    size_type  node_count = 0;
    comparator comp;
};

template<class K, class T, class C>
void swap(interval_tree<K, T, C>& lhs,
          interval_tree<K, T, C>& rhs) noexcept(noexcept(lhs.swap(rhs)))
{
    lhs.swap(rhs);
}

template<class K, class T, class C>
void swap(typename interval_tree<K, T, C>::iterator& lhs,
          typename interval_tree<K, T, C>::iterator& rhs) noexcept(noexcept(lhs.swap(rhs)))
{
    lhs.swap(rhs);
}

template<class K, class T, class C>
bool operator==(const interval_tree<K, T, C>& lhs,
                const interval_tree<K, T, C>& rhs)
{
    if(lhs.size() != rhs.size())
        return false;

    auto lit = lhs.cbegin();
    auto el  = lhs.cend();

    auto rit = rhs.cbegin();
    auto er  = rhs.cend();

    while(lit != el && rit != er)
    {
        if(*lit != *rit)
            return false;
    }

    return true;
}

template<class K, class T, class C>
bool operator!=(const interval_tree<K, T, C>& lhs,
                const interval_tree<K, T, C>& rhs)
{
    return !(lhs == rhs);
}

template<class K, class T, class C>
bool operator <(const interval_tree<K, T, C>& lhs,
                const interval_tree<K, T, C>& rhs)
{
    return std::lexicographical_compare(lhs.cbegin(), lhs.cend(),
                                        rhs.cbegin(), rhs.cend());
}

template<class K, class T, class C>
bool operator >(const interval_tree<K, T, C>& lhs,
                const interval_tree<K, T, C>& rhs)
{
    return rhs < lhs;
}

template<class K, class T, class C>
bool operator<=(const interval_tree<K, T, C>& lhs,
                const interval_tree<K, T, C>& rhs)
{
    return !(lhs > rhs);
}

template<class K, class T, class C>
bool operator>=(const interval_tree<K, T, C>& lhs,
                const interval_tree<K, T, C>& rhs)
{
    return !(lhs < rhs);
}

#endif // INTERVAL_TREE_H
