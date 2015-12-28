import org.junit.Assert;
import org.junit.Test;

/**
 * Created by chaomai on 12/28/15.
 */
public class ImmutableQueueTest {
  private <E> void checkQueue(E[] data, ImmutableQueue<E> imq) {
    for (E i : data) {
      Assert.assertEquals(i, imq.peek());
      imq = imq.dequeue();
    }
  }

  @Test
  public void testEnqueue() throws Exception {
    Integer[] data = {0, 1, 2, 3, 4, 5};
    ImmutableQueue<Integer> imq = new ImmutableQueue<Integer>();

    for (int i : data) {
      imq = imq.enqueue(i);
    }

    Assert.assertEquals(data.length, imq.size());

    checkQueue(data, imq);
  }

  @Test
  public void testDequeue() throws Exception {
    Integer[] data = {0, 1, 2, 3, 4, 5};
    ImmutableQueue<Integer> imq = new ImmutableQueue<Integer>();

    for (int i : data) {
      imq = imq.enqueue(i);
    }

    Assert.assertEquals(data.length, imq.size());

    ImmutableQueue<Integer> nq = imq.dequeue().dequeue().dequeue();

    checkQueue(data, imq);

    for (int i = 3; i < data.length; ++i) {
      Assert.assertEquals(data[i], nq.peek());
      nq = nq.dequeue();
    }
  }
}