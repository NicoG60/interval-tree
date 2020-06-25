# interval_tree<Key, Value, Comp>::begin, interval_tree<Key, Value, Comp>::cbegin

```cpp
iterator begin() noexcept;
const_iterator begin() const noexcept;
const_iterator cbegin() const noexcept;
```

Returns an iterator to the first element of the container. If the container is empty, the returned iterator will be equal to [end()](end.md).

![iterators](http://upload.cppreference.com/mwiki/images/1/1b/range-begin-end.svg)

#### Returns

Iterator to the first element.