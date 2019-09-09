# interval_tree<Key, Value, Comp>::clear

```cpp
void clear() noexcept;
```

Erases all elements from the container. After this call, [`size()`](size.md) returns zero.

Invalidates any references, pointers, or iterators referring to contained elements. Any past-the-end iterator remains valid.

#### Complexity

Linear in size