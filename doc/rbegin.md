# interval_tree<Key, Value, Comp>::rbegin, interval_tree<Key, Value, Comp>::crbegin

```cpp
iterator rbegin() noexcept;
const_iterator rbegin() const noexcept;
const_iterator crbegin() const noexcept;
```

Returns a reverse iterator to the first element of the reversed container. It corresponds to the last element of the non-reversed container. If the container is empty, the returned iterator is equal to [rend()](rend.md).

![iterators](http://upload.cppreference.com/mwiki/images/3/39/range-rbegin-rend.svg)

#### Returns

Reverse iterator to the first element.

#### Complexity

Linear in size