package st

import (
	"testing"
)

func TestSegmentTree(t *testing.T) {
	tree := NewSegmentTree([]int{11, 12, 13, 14, 15})
	tree.Print()
}
