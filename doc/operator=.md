# interval_tree<Key, Value, Comp>::operator=

```cpp
interval_tree& operator=( const interval_tree& other );              // (1)
interval_tree& operator=( interval_tree&& other );                   // (2)
interval_tree& operator=( std::initializer_list<value_type> ilist ); // (3)
```

Replace the content of the container

1. Copy assignment operator. Replaces the contents with a copy of the contents of `other`.
2. Move assignment operator. Replaces the contents with those of `other` using move semantics (i.e. the data in `other` is moved from `other` into this container). `other` is in a valid but unspecified state afterwards.
3. Replaces the contents with those identified by initializer list `ilist`.

#### Parameters

- **other** : another container to use as data source
- **ilist** : initializer list to use as data source

#### Returns

`*this`

#### Complexity

1. Linear in size of `*this` and `other`
2. Linear in size of `*this`
5. N log(N) where `N = size() + init.size()`