# interval_tree<Key, Value, Comp>::~interval_tree

```cpp
~interval_tree();
```

Destructs the container. The destructors of the elements are called and the used storage is deallocated. Note, that if the elements are pointers, the pointed-to objects are not destroyed.

#### Complexity

Linear in size of the container