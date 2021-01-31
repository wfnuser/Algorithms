package ratelimit

import (
	"fmt"
	"sync"
	"time"
)

type RateLimiter struct {
	rate   int64
	max    int64
	last   int64
	amount int64
	lock   sync.Mutex
}

// (now - last) * rate

func cur() int64 {
	return time.Now().Unix()
}

func New(rate int64, max int64) *RateLimiter {
	// TODO: 检查一下rate和max是否合法
	return &RateLimiter{
		rate:   rate,
		max:    max,
		last:   cur(),
		amount: max,
	}
}

func (rl *RateLimiter) Pass() bool {
	rl.lock.Lock()
	defer rl.lock.Unlock()

	// 当前桶中 是否还有令牌
	passed := cur() - rl.last
	fmt.Println("passed is: ", passed)

	amount := rl.amount + passed*rl.rate

	if amount > rl.max {
		amount = rl.max
	}

	if amount <= 0 {
		return false
	}

	amount--
	rl.amount = amount
	rl.last = cur()
	return true
}
