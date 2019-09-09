# interval_tree<Key, Value, Comp>::emplace

```cpp
template<class... Args>
iterator emplace( const key_type& key, Args&& ...args );

template<class... Args>
iterator emplace( key_type&& key, Args&& ...args );
```

Inserts a new element into the container constructed in-place with the given `args`

Careful use of `emplace` allows the new element to be constructed while avoiding unnecessary copy or move operations. The constructor of the new element is called with exactly the same arguments as supplied to `emplace`, forwarded via `std::forward<Args>(args)...`.

```cpp
template<class... Args>
iterator emplace(key_type&& key, Args&& ...args)
{
    return insert({key, mapped_type(std::forward<Args>(args)...)});
}
```



#### Parameters

- **key** : the key where the value should go
- **args** : the arguments passed to the constructor

#### Returns

An iterator to the inserted element

#### Complexity

Logarithmic in the size of the container