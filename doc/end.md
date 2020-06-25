# interval_tree<Key, Value, Comp>::end, interval_tree<Key, Value, Comp>::cend

```cpp
iterator end() noexcept;
const_iterator end() const noexcept;
const_iterator cend() const noexcept;
```

Returns an iterator to the element following the last element of the container. This element acts as a placeholder; attempting to access it results in undefined behavior.

![iterators](http://upload.cppreference.com/mwiki/images/1/1b/range-begin-end.svg)

#### Returns

Iterator to the element following the last element.