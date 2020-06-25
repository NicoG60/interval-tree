# interval_tree<Key, Value, Comp>::interval_tree

```cpp
interval_tree();
explicit interval_tree(const Comp& comp);	          // (1)
//----------------------------------------------------------
template<class InputIt>
interval_tree(InputIt first, InputIt last,            // (2)
              const Comp& comp = Comp() );
//----------------------------------------------------------
interval_tree(const interval_tree& other);            // (3)
//----------------------------------------------------------
interval_tree(interval_tree&& other);                 // (4)
//----------------------------------------------------------
interval_tree(std::initializer_list<value_type> init,
              const Comp& comp = Comp() );            // (5)
```

Constructs a new container from variety of data sources and optionnally using user supplied comparison function object `comp`

1. Constructs an empty container.
2. Constructs the container with the contents of the range `[first, last)` 
3. Copy constructor. Constructs the container with the copy of the contents of `other`.
4. Move constructor. Constructs the container with the contents of `other` using move semantics.
5. Constructs the container with the contents of the initializer list `init`.

#### Parameters

- **comp** : comparison function object to use for all comparisons of keys
- **first, last** : the range to copy the elements from
- **other** : another container to be used as source to initialize the elements of the container with
- **init** : initializer list to initialize the elements of the container with

##### Type requirements

- `InputIt` must meet the requirements of LegacyInputIterator.
- `Compare` must meet the requirements of Compare.

#### Complexity

1. Constant
2. *N log(N)* where `N = std::distance(first, last)`
3. Linear in size of `other`
4. Constant
5. N log(N) where `N = init.size()`