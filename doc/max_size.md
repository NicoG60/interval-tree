# interval_tree<Key, Value, Comp>::max_size

```cpp
size_type max_size() const noexcept;
```

Returns the maximum number of elements the container is able to hold due to system or library implementation limitations, i.e. `std::distance(begin(), end())` for the largest container.

#### Returns

Maximum number of elements.

#### Complexity

Constant

#### Notes
This value typically reflects the theoretical limit on the size of the container, at most `std::numeric_limits<difference_type>::max()`. At runtime, the size of the container may be limited to a value smaller than `max_size()` by the amount of RAM available.