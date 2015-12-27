package Test;

public class Test {
	public static void main(String [] args) {
		String test = "a" + "\t" + "b" + "\t" + "c";
		String []arr = test.split("\t");
		System.out.println(arr[0]);
		System.out.println(arr[1]);
		System.out.println(arr[2]);
	}
}
