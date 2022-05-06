#ifndef MSORT_H
#define MSORT_H

#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>

template <typename T, typename F = std::less<T>>
class mergesort_util
{
private:
  T *t;
  int s;
  bool isMerge;
  F f;

public:
  mergesort_util(T tomb[], const int size, bool mergeon = true) : t(tomb), s(size), isMerge(mergeon) {}

  mergesort_util(T tomb[], const int size, bool mergeon, F fun) : t(tomb), s(size), isMerge(mergeon)
  {
    f = fun;
  }

  void change(T &a, T &b)
  {
    if (f(a, b)) std::swap(a, b);
  }

  void split(int start, int end)
  {
    int mid = ceil((start + end) / 2.0);

    if (end - start > 1)
    {
      split(start, mid - 1);
      split(mid, end);
    }

    if (isMerge || end - start == 1)
    {
      merge(start, end);
    }
  }

  void merge(int start, int end)
  {
    if (start != end)
    {
      int mid = ceil((start + end) / 2.0);
      std::queue<T> left;
      for (int i = start; i < mid; i++)
      {
        left.push(t[i]);
      }

      int leftidx = start;
      int rightidx = mid;
      while (left.size() > 0 && rightidx <= end)
      {
        if (f(t[rightidx], left.front()))
        {
          t[leftidx++] = t[rightidx++];
        }
        else
        {
          t[leftidx++] = left.front();
          left.pop();
        }
      }

      while (left.size() > 0)
      {
        t[leftidx++] = left.front();
        left.pop();
      }
    }
  }

  void sort()
  {
    split(0, s - 1);
  }

  void set_merge_on()
  {
    isMerge = true;
  }
};

template <typename T, typename F = std::less<T>>
void mergesort(T arr[], int s, F f)
{
  mergesort_util<T, F> tmp(arr, s, true, f);
  tmp.sort();
}

template <typename T>
void mergesort(T arr[], int s)
{
  mergesort_util<T> tmp(arr, s, true);
  tmp.sort();
}

#endif