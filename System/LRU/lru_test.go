package lru

import (
	"testing"
)

func TestPass(t *testing.T) {
	l, e := NewLRU(3)
	if e != nil {
		t.Errorf("new lru failed")
	}

	_, ok := l.Get(10)
	if ok {
		t.Errorf("should not get nonexistent value")
	}
	l.Put(10, 10)
	l.Put(10, 20)
	if l.innerList.Len() != 1 {
		t.Errorf("uncorrect size")
	}
	v, ok := l.Get(10)
	if v != 20 {
		t.Errorf("uncorrect value")
	}
	l.Put(11, 11)
	l.Put(12, 12)
	l.Put(13, 13)
	l.Put(11, 14)
	if l.innerList.Len() != 3 {
		t.Errorf("uncorrect size")
	}
	if l.innerList.Front().Value.(*entry).key != 11 {
		t.Errorf("uncorrect position")
	}
}
