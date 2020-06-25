# interval_tree<Key, Value, Comp>::emplace

```cpp
template<class... Args>
iterator emplace( Args&& ...args );
```

Inserts a new element into the container constructed in-place with the given `args`

Careful use of `emplace` allows the new element to be constructed while avoiding unnecessary copy or move operations. The constructor of the new element is called with exactly the same arguments as supplied to `emplace`, forwarded via `std::forward<Args>(args)...`.

#### Parameters

- **args** : the arguments passed to the constructor

#### Returns

An iterator to the inserted element

#### Complexity

Logarithmic in the size of the container