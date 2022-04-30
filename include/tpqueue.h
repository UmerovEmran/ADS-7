// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_
#include <string>

template<typename T>
class TPQueue {
 private:
  struct Ltqueue {
    T value;
    Ltqueue* prev;
    Ltqueue* next;
  };
  Ltqueue* tail;
  Ltqueue* head;
  TPQueue::Ltqueue* create(const T&);
 public:
  TPQueue():head(nullptr), tail(nullptr) {}
  T pop();
  void push(const T&);
};

struct SYM {
  char ch;
  int prior;
};

template < typename T >
void TPQueue <T>::push(const T& value) {
  Ltqueue* pass = head;
  Ltqueue* mean = create(value);
  for (bool i = false; i != true; ) {
    if (pass && pass->value.prior >= value.prior) {
        pass = pass->next;
    } else {
        i = true;
      }
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

template<typename T>
T TPQueue<T>::pop() {
  if (head && tail) {
      Ltqueue* pass = head->next;
    if (!head) {
      tail = nullptr;
    }
    if (pass) {
      pass->prev = nullptr;
    }
    T value = head->value;
    delete head;
    head = pass;
    return value;
  }
}

#endif  // INCLUDE_TPQUEUE_H_
