package LinkedList;

/**
 * Created by chaomai on 12/15/15.
 */
class Node<T> {
  final T key;
  volatile Node<T> next;

  Node(T key) {
    this.key = key;
  }
}