package lru

import (
	"container/list"
	"errors"
)

type LRU struct {
	size      int
	innerList *list.List
	innerMap  map[int]*list.Element
}

type entry struct {
	key   int
	value int
}

func NewLRU(size int) (*LRU, error) {
	if size <= 0 {
		return nil, errors.New("must provide a positive size")
	}
	c := &LRU{
		size:      size,
		innerList: list.New(),
		innerMap:  make(map[int]*list.Element),
	}
	return c, nil
}

func (c *LRU) Get(key int) (int, bool) {
	if e, ok := c.innerMap[key]; ok {
		c.innerList.MoveToFront(e)
		return e.Value.(*entry).value, true
	}
	return -1, false
}

func (c *LRU) Put(key int, value int) (evicted bool) {
	if e, ok := c.innerMap[key]; ok {
		c.innerList.MoveToFront(e)
		e.Value.(*entry).value = value
		return false
	} else {
		e := &entry{key, value}
		ent := c.innerList.PushFront(e)
		c.innerMap[key] = ent

		if c.innerList.Len() > c.size {
			last := c.innerList.Back()
			c.innerList.Remove(last)
			delete(c.innerMap, last.Value.(*entry).key)
			return true
		}
		return false
	}
}
