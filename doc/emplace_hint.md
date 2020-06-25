# interval_tree<Key, Value, Comp>::emplace

```cpp
template<class... Args>
iterator emplace( const_iterator hint, Args&& ...args );
```

Inserts a new element into the container as close as possible to the position just before hint. The element is constructed in-place, i.e. no copy or move operations are performed.

The constructor of the element type (value_type, that is, `std::pair<key_type, mapped_type>)` is called with exactly the same arguments as supplied to the function, forwarded with `std::forward<Args>(args)...`.

No iterators or references are invalidated.

#### Parameters
- **hint** : 	iterator to the position before which the new element will be inserted
- **args** : the arguments passed to the constructor

#### Returns

An iterator to the inserted element

#### Complexity

Logarithmic in the size of the container in general, but amortized constant if the new element is inserted just before hint.