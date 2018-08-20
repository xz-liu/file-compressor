# ds_exp
studying data structure

## zip

file compressor 

![image](http://github.com/joker-xii/ds_exp/raw/master/demo/zip.jpg)

## rbtree demo

A demo for red-black tree

![image](http://github.com/joker-xii/ds_exp/raw/master/demo/rbtree.png)

## containers

### vector
supported functions
```
    vector()
    vector(Allocator)
    vector(Iter begin,Iter end)
    vector(std::initializer_list<T> init,Allocator a=Alloc())
    vector(vector const&)
    vector(size_t size)
    vector(size_t size,T val)
    operator=(vector const&)
    operator[](size_t)
    begin()
    end()
    cbegin()
    cend()
    rbegin()
    rend()
    size()
    empty()
    clear()
    assign(Iter begin,Iter end)
    assign(size_type cnt, T val)
    push_back(T const&)
    pop_back()
    erase(Iter)
    erase(Iter begin,Iter end)
    erase(size_t pos)
    front()
    back()
    insert(Iter,T)
    resize(size_t)
    reserve(size_t)
    emplace(Iter where,Args&&... args)
    emplace_back(Args&&... args)
    get_allocator()
```
