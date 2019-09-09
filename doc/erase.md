# interval_tree<Key, Value, Comp>::erase

```cpp
iterator erase( const_iterator pos );
```

Removes specified elements from the container. References and iterators to the erased elements are invalidated. Other references and iterators are not affected.

The iterator `pos` must be valid and dereferenceable. Thus the [end()](end.md) iterator (which is valid, but is not dereferenceable) cannot be used as a value for `pos`.

#### Parameters

- **pos** : iterator to the element to remove

#### Returns

Iterator following the removed element.

#### Complexity

Logarithmic in the size of the container