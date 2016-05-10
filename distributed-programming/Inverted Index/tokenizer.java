import java.util.StringTokenizer;


public class tokenizer {
	public static void main(String[] args) {
		String delim = " ,.!";//more signs should be include
		String paper = "Four score and seven years ago our fathers brought forth on this continent, a new nation, conceived in Liberty, and dedicated to the proposition that all men are created equal.";
		StringTokenizer st = new StringTokenizer(paper,delim);
    	while (st.hasMoreTokens()) {
    		System.out.println(st.nextToken());
    	}
	}
}