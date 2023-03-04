
#include <gtest/gtest.h>

#include "heap.hpp"

TEST(HeapTest, Simple) {
  MinHeap heap;
  heap.Push(1);
  ASSERT_EQ(heap.PopMin(), 1);
}

TEST(HeapTest, Basic) {
  MinHeap heap;
  heap.Push(1);
  heap.Push(2);
  heap.Push(3);              // [1, 2, 3]
  ASSERT_EQ(heap.PopMin(), 1);  // [2, 3] -> 1
  ASSERT_EQ(heap.PopMin(), 2);  // [3] -> 2
  ASSERT_EQ(heap.PopMin(), 3);  // [] -> 3
}

TEST(HeapTest, Empty) {
  MinHeap heap;
  ASSERT_ANY_THROW(heap.PopMin());
  heap.Push(1);
  ASSERT_EQ(heap.PopMin(), 1);  // [(1), 2, 3]
  ASSERT_ANY_THROW(heap.PopMin());
}

TEST(HeapTest, Complex) {
  MinHeap heap;
  heap.Push(6);              // [6]
  heap.Push(1);              // [1, 6]
  heap.Push(2);              // [1, 2, 6]
  heap.Push(3);              // [1, 2, 3, 6]
  heap.Push(5);              // [1, 2, 3, 5, 6]
  heap.Push(4);              // [1, 2, 3, 4, 5, 6]
  ASSERT_EQ(heap.PopMin(), 1);  // [2, 3, 4, 5, 6] -> 1
  ASSERT_EQ(heap.PopMin(), 2);  // [3, 4, 5, 6] -> 2
  ASSERT_EQ(heap.PopMin(), 3);  // [4, 5, 6] -> 3
  ASSERT_EQ(heap.PopMin(), 4);  // [5, 6] -> 4
  ASSERT_EQ(heap.PopMin(), 5);  // [6] -> 5
  heap.Push(7);              // [6, 7]
  heap.Push(1);              // [1, 6, 7]
  heap.Push(2);              // [1, 2, 6, 7]
  ASSERT_EQ(heap.PopMin(), 1);  // [2, 6, 7] -> 1
  heap.Push(3);              // [2, 3, 6, 7]
  heap.Push(5);              // [2, 3, 5, 6, 7]
  heap.Push(4);              // [2, 3, 4, 5, 6, 7]
  ASSERT_EQ(heap.PopMin(), 2);  // [3, 4, 5, 6, 7] -> 2
  ASSERT_EQ(heap.PopMin(), 3);  // [4, 5, 6, 7] -> 3
  ASSERT_EQ(heap.PopMin(), 4);  // [5, 6, 7] -> 4
  ASSERT_EQ(heap.PopMin(), 5);  // [6, 7] -> 5
  ASSERT_EQ(heap.PopMin(), 6);  // [7] -> 6
  ASSERT_EQ(heap.PopMin(), 7);  // [] -> 7
}