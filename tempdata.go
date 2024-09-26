package main

import (
	"fmt"
	"time"
	"sync"
)

/*
协程是由用户来调度的，可以创建成千上万个
在函数或方法前加上关键字：go，你会同时运行一个新的goroutine
*/
var wg sync.WaitGroup//设置同步等待组，为全局变量
func main() {


	//临界资源：可以被多个进程/协程共享的资源
	/*
	a := 3
	go func() {
		a = 1
		fmt.Println("子a=", a)
	}()
	time.Sleep(1 * time.Second)
	fmt.Println("父a=", a)
	 */
	//使用sync包来实现临界资源的控制
	wg.Add(2)//两个goroutine


	go PrintfNum()
	go alphabtes()
	fmt.Println("main开始等待")
	wg.Wait()//main进入阻塞状态，资源由两个goroutine抢占
	fmt.Println("over")
}
func PrintfNum() {
	for i := 1; i <= 5; i++ {
		time.Sleep(250 * time.Millisecond)
		fmt.Printf("|———子GoroutineNum:%d\n", i)
	}
	wg.Done()//执行完毕后，wg.add()里面的goroutine数量--
}
func alphabtes() {
	for i := 'a'; i <= 'e'; i++ {
		time.Sleep(400 * time.Millisecond)
		fmt.Printf("|———子GoroutineAlp:%c\n", i)
	}
	wg.Done()
}