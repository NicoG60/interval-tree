# interval-tree ![C/C++ CI](https://github.com/NicoG60/interval-tree/workflows/C/C++%20CI/badge.svg?branch=master)

Implementation of an Augmented AVL interval Tree in the STL fashion



# Usage

## Include

make the `include` dir reachable for your project and simply include `<interval_tree.h>`

## Details

```cpp
template<
    class Key,
    class Value,
    class Comp = std::less<Key>
> class interval_tree;
```

interval_tree is a container associating pairs of keys with a value. the keys represent the lower and upper bounds of an interval. the container is ordered using the comparison function Comp. Search, insertion, removal have logarithmic complexity.

Elements with the exact same interval keys are allowed and are ordered by insertion.

### Member types

| Member type        | Definition                             |
| ------------------ | -------------------------------------- |
| `bound_type`       | Key                                    |
| `key_type`         | `std::pair<bound_type, bound_type>`    |
| `mapped_type`      | Value                                  |
| `value_type`       | `std::pair<key_type, mapped_type>`     |
| `reference`        | `value_type&`                          |
| `iterator`         | Legacy Bidirectionnal Iterator         |
| `reverse_iterator` | Reverse Legacy Bidirectionnal Iterator |

### Member function

| Constructors                        |                                 |
| ----------------------------------- | ------------------------------- |
| [(constructor)](doc/constructor.md) | constructs the interval tree    |
| [(destructor)](doc/destructor.md)   | destructs the interval tree     |
| [`operator=`](doc/operator=.md)     | Assigns values to the container |



| Iterators                           |                                             |
| ----------------------------------- | ------------------------------------------- |
| [`begin` `cbegin`](doc/begin.md)    | returns an iterator to the beginning        |
| [`end` `cend`](doc/end.md)          | returns an iterator to the end              |
| [`rbegin` `crbegin`](doc/rbegin.md) | returns a reverse iterator to the beginning |
| [`rend` `crend`](doc/rend.md)       | returns a reverse iterator to the end       |

| Capacity                      |                                                 |
| ----------------------------- | ----------------------------------------------- |
| [`empty`](doc/empty.md)       | check wether the container is empty             |
| [`size`](doc/size.md)         | return the number of elements                   |
| [`max_size`](doc/max_size.md) | return the theorical maximum number of elements |

| Modifiers                             |                                           |
| ------------------------------------- | ----------------------------------------- |
| [`clear`](doc/clear.md)               | clears the content                        |
| [`insert`](doc/insert.md)             | inserts elements                          |
| [`emplace`](doc/emplace.md)           | constructs elements in place              |
| [`emplace_hint`](doc/emplace_hint.md) | constructs elements in-place using a hint |
| [`erase`](doc/erase.md)               | erases elements                           |
| [`swap`](doc/swap.md)                 | swap contents                             |

| Lookup                              |                                                                          |
| ----------------------------------- | ------------------------------------------------------------------------ |
| [`count`](doc/count.md)             | count the number of element with a given key                             |
| [`at`](doc/at.md)                   | access specified element or get all intervals overlapping a single value |
| [`in`](doc/in.md)                   | get all intervals overlapping an interval.                               |
| [`find`](doc/find.md)               | finds an element with a specific key                                     |
| [`equal_range`](doc/equal_range.md) | returns range of elements matching a specific key                        |
| [`lower_bound`](doc/lower_bound.md) | returns an iterator to the first element not less than the given key     |
| [`upper_bound`](doc/upper_bound.md) | returns an iterator to the first element greater than the given key      |
