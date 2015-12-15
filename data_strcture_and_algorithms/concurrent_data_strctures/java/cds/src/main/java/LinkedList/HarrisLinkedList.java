package LinkedList;

/**
 * Created by chaomai on 12/15/15.
 */
public class HarrisLinkedList<T> {
  private volatile Node<T> head;
  private volatile Node<T> tail;

  public HarrisLinkedList() {
    head = new Node<>();
    tail = new Node<>();
    head.next = tail;
  }
}