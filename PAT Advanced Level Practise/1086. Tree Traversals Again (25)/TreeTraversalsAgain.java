

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.StreamTokenizer;
import java.util.Stack;

public class Main{

	private static TNode[] tree;//Array to store the tree
	
	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		StreamTokenizer st = new StreamTokenizer(
				new BufferedReader(new InputStreamReader(System.in)));
		st.nextToken();
		int nNodes = (int) st.nval;//Number of nodes
		tree = new TNode[nNodes];
		Stack<TNode> stack = new Stack<TNode>();//Stack 
		int current = 0;//The index of the node on which the new nodes attach to
		int index = 0;
		for (int i = 0; i < 2*nNodes; i ++) {
			st.nextToken();
			String s = st.sval;
			if (s.equals("Push")) {
				st.nextToken();
				int data = (int) st.nval;
				TNode node = new TNode(index, data);
				stack.push(node);
				tree[index] = node;
				if (i != 0)
					if (tree[current].getLeft() == -1)
						tree[current].setLeft(index);
					else
						tree[current].setRight(index);
				current = index ++;
			} else if (s.equals("Pop")) 
				current = stack.pop().getIndex();
		}
		String str = traversal(0);
		str = str.substring(0, str.length() - 1);
		System.out.println(str);
	}

	private static String traversal(int root) {
		// TODO Auto-generated method stub
		String result = "";
		if (root != -1) {
			result += traversal(tree[root].getLeft());
			result += traversal(tree[root].getRight());
			result += tree[root].getData();
			result += " ";
		}
		return result;
	}

}

class TNode {
	
	//Constructor
	public TNode (int index, int data) {
		this.index = index;
		this.data = data;
		this.left = -1;
		this.right = -1;
	}
	
	/** Returns the index of the node. */
	public int getIndex() {
		return index;
	}
	
	/** Returns the data. */
	public int getData() {
		return data;
	}
	
	/** Returns the index of the left. */
	public int getLeft() {
		return left;
	}
	
	/** Sets the index of the left. */
	public void setLeft(int left) {
		this.left = left;
	}
	
	/** Returns the index of the right. */
	public int getRight() {
		return right;
	}
	
	/** Sets the index of the right. */
	public void setRight(int right) {
		this.right = right;
	}
	
	/* Private instance variables. */
	private int index;
	private int data;
	private int left;
	private int right;
}
