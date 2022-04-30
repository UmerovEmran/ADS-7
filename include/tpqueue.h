// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_
#include <string>

template<typename T>
class TPQueue {
private:
  struct Lqueue {
    T value;
    Lqueue* next;
    Lqueue* prev;
  };
  TPQueue::Lqueue* create(const T&);
  Lqueue* tail;
  Lqueue* head;
public:
  TPQueue() :head(nullptr), tail(nullptr) {}
  T pop();
  void push(const T&);
};

struct SYM {
  char ch;
  int prior;
};

template<typename T>
typename TPQueue<T>::Lqueue* TPQueue<T>::create(const T& value) {
  Lqueue* mean = new Lqueue;
  mean->value = value;
  mean->next = nullptr;
  mean->prev = nullptr;
  return mean;
}

template<typename T>
T TPQueue<T>::pop() {
  if (head && tail) {
    Lqueue* pass = head->next;
    if (pass) {
      pass->prev = nullptr;
    }
    T value = head->value;
    delete head;
    head = pass;
    if (!head) {
      tail = nullptr;
    }
    return value;
  }
}

template < typename T >
void TPQueue <T>::push(const T& value) {
  Lqueue* pass = head;
  Lqueue* mean = create(value);
  while (pass && pass->value.prior >= value.prior) {
    pass = pass->next;
  }
  if (!pass && head) {
    tail->next = mean;
    mean->prev = tail;
    tail = mean;
  } else if (!pass && !head) {
      head = tail = mean;
    } else if (!pass->prev) {
        head->prev = mean;
        mean->next = head;
        head = mean;
      } else {
          pass->prev->next = mean;
          mean->prev = pass->prev;
          mean->next = pass;
          pass->prev = mean;
        }
}

#endif  // INCLUDE_TPQUEUE_H_
