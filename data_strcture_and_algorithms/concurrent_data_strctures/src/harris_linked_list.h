#ifndef HARRIS_LINKED_LIST_H
#define HARRIS_LINKED_LIST_H

#include <atomic>
#include <tuple>

template <typename Val_T>
struct ListNode {
  ListNode() : key(0), next(nullptr) {}
  ListNode(const Val_T& k) : key(k), next(nullptr) {}

  Val_T key;
  std::atomic<ListNode<Val_T>*> next;
};

template <typename Val_T>
class List {
 public:
  List() {
    head = new ListNode<Val_T>();
    tail = new ListNode<Val_T>();
    head.load()->next.store(tail);
  }
  bool find_key(Val_T);
  bool insert_key(Val_T);
  bool delete_key(Val_T);

 private:
  std::atomic<ListNode<Val_T>*> head;
  std::atomic<ListNode<Val_T>*> tail;

  std::tuple<ListNode<Val_T>*, ListNode<Val_T>*> search_key(Val_T);
  ListNode<Val_T>* get_unmarked_reference(ListNode<Val_T>*);
  ListNode<Val_T>* get_marked_reference(ListNode<Val_T>*);
  bool is_marked_ref(ListNode<Val_T>*);
};

template <typename Val_T>
bool List<Val_T>::find_key(Val_T key) {
  std::atomic<ListNode<Val_T>*> left_node;
  std::atomic<ListNode<Val_T>*> right_node;

  auto search_res = search_key(key);
  left_node.store(std::get<0>(search_res));
  right_node.store(std::get<1>(search_res));

  if (right_node == tail || right_node.load()->key != key) {
    return false;
  }
  return true;
}

template <typename Val_T>
bool List<Val_T>::insert_key(Val_T key) {
  std::atomic<ListNode<Val_T>*> left_node;
  std::atomic<ListNode<Val_T>*> right_node;
  std::atomic<ListNode<Val_T>*> new_node = new ListNode<Val_T>(key);

  while (true) {
    auto search_res = search_key(key);
    left_node.store(std::get<0>(search_res));
    right_node.store(std::get<1>(search_res));

    if (right_node == tail || right_node.load()->key == key) {
      return false;
    }
    new_node.load()->next.store(right_node);
    if (std::atomic_compare_exchange_weak(&(left_node.load()->next),
                                          &right_node, new_node)) {
      return true;
    }
  }
}

template <typename Val_T>
bool List<Val_T>::delete_key(Val_T key) {
  std::atomic<ListNode<Val_T>*> left_node;
  std::atomic<ListNode<Val_T>*> right_node_next;
  std::atomic<ListNode<Val_T>*> right_node;

  while (true) {
    auto search_res = search_key(key);
    left_node.store(std::get<0>(search_res));
    right_node.store(std::get<1>(search_res));

    if (right_node == tail || right_node.load()->key != key) {
      return false;
    }
    right_node_next.store(right_node.load()->next);

    if (!is_marked_ref(right_node.load()->next)) {
      if (std::atomic_compare_exchange_weak(
              &(right_node.load()->next), &right_node_next,
              get_marked_reference(right_node_next))) {
        break;
      }
    }
  }
  if (!std::atomic_compare_exchange_weak(&(left_node.load()->next), right_node,
                                         right_node_next)) {
    auto search_res = search_key(key);
  }
}

template <typename Val_T>
std::tuple<ListNode<Val_T>*, ListNode<Val_T>*> List<Val_T>::search_key(
    Val_T key) {
  std::atomic<ListNode<Val_T>*> left_node;
  std::atomic<ListNode<Val_T>*> left_node_next;
  std::atomic<ListNode<Val_T>*> right_node;

  while (true) {
    ListNode<Val_T>* t;
    t= head.load();
    auto t_next = t->next;

    while (is_marked_ref(t_next) || t->key < key) {
      if (!is_marked_ref(t_next)) {
        left_node = t;
        left_node_next = t_next;
      }

      t = get_unmarked_reference(t_next);
      if (t == tail) {
        break;
      }

      t_next = t->next.load();
    }
    right_node = t;

    if (right_node == left_node_next) {
      if (right_node != tail && is_marked_ref(right_node.load()->next)) {
        continue;
      }
      return std::make_tuple(left_node.load(), right_node.load());
    }

    if (std::atomic_compare_exchange_weak(&(left_node.load()->next),
                                          &left_node_next, right_node)) {
    }
    if (right_node != tail && is_marked_ref(right_node.load()->next)) {
      continue;
    }
    return std::make_tuple(left_node.load(), right_node.load());
  }
}

template <typename Val_T>
bool List<Val_T>::is_marked_ref(ListNode<Val_T>*) {}
template <typename Val_T>
ListNode<Val_T>* List<Val_T>::get_unmarked_reference(ListNode<Val_T>*) {}
template <typename Val_T>
ListNode<Val_T>* List<Val_T>::get_marked_reference(ListNode<Val_T>*) {}

#endif
