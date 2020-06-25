# interval_tree<Key, Value, Comp>::rend, interval_tree<Key, Value, Comp>::crend

```cpp
iterator rend() noexcept;
const_iterator rend() const noexcept;
const_iterator crend() const noexcept;
```

Returns a reverse iterator to the element following the last element of the reversed container. It corresponds to the element preceding the first element of the non-reversed container. This element acts as a placeholder, attempting to access it results in undefined behavior.

![iterators](http://upload.cppreference.com/mwiki/images/3/39/range-rbegin-rend.svg)

#### Returns

Reverse iterator to the element following the last element.