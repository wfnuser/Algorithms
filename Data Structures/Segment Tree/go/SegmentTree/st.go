package st

import (
	"errors"
	"fmt"
)

type SegmentTree struct {
	tree []int //线段树
	a    []int //数组数据
}

func leftChild(i int) int {
	return 2*i + 1
}

// 传入一个数组arrs和一个功能函数func,根据功能函数返回一个线段树
func NewSegmentTree(arrs []int) *SegmentTree {
	length := len(arrs)
	tree := &SegmentTree{
		tree: make([]int, length*4),
		a:    arrs,
	}
	tree.build(0, 0, length-1)
	return tree
}

// 在tree的index位置创建 arrs [ l 到 r ]  的线段树
func (tree *SegmentTree) build(index, l, r int) int {
	// 递归终止条件
	if l == r {
		tree.tree[index] = tree.a[l]
		return tree.a[l]
	}
	// 递归过程
	leftI := leftChild(index)
	rightI := leftI + 1
	mid := l + (r-l)/2
	leftResp := tree.build(leftI, l, mid)
	rightResp := tree.build(rightI, mid+1, r)
	tree.tree[index] = leftResp + rightResp
	return tree.tree[index]
}

// 查询arrs范围queryL到queryR 的结果
func (tree *SegmentTree) Query(queryL, queryR int) (int, error) {
	length := len(tree.a)
	if queryL < 0 || queryL > queryR || queryR >= length {
		return 0, errors.New("index is illegal")
	}
	return tree.queryrange(0, 0, length-1, queryL, queryR), nil
}

// 在以index为根的线段树中[l...r]范围里，搜索区间[queryL...queryR]的值
func (tree *SegmentTree) queryrange(index, l, r, queryL, queryR int) int {
	if l == queryL && r == queryR {
		return tree.tree[index]
	}
	leftI := leftChild(index)
	rightI := leftI + 1
	mid := l + (r-l)/2
	if queryL > mid {
		return tree.queryrange(rightI, mid+1, r, queryL, queryR)
	}
	if queryR <= mid {
		return tree.queryrange(leftI, l, mid, queryL, queryR)
	}
	leftResp := tree.queryrange(leftI, l, mid, queryL, mid)
	rightResp := tree.queryrange(rightI, mid+1, r, mid+1, queryR)
	return leftResp + rightResp
}

// 更新a中索引k的值为v
func (tree *SegmentTree) Change(k, v int) {
	length := len(tree.a)
	if k < 0 || k >= length {
		return
	}
	tree.set(0, 0, length-1, k, v)
}

// 在以treeIndex为根的线段树中更新index的值为e
func (tree *SegmentTree) set(treeIndex, l, r, k, v int) {
	if l == r {
		tree.tree[treeIndex] = v
		return
	}
	leftI := leftChild(treeIndex)
	rightI := leftI + 1
	midI := l + (r-l)/2
	if k > midI {
		tree.set(rightI, midI+1, r, k, v)
	} else {
		tree.set(leftI, l, midI, k, v)
	}
	tree.tree[treeIndex] = tree.tree[leftI] + tree.tree[rightI]
}

func (tree *SegmentTree) Print() {
	fmt.Println(tree.tree)
}
