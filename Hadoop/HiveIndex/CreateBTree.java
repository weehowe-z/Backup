package Test;

import java.util.ArrayList;
import java.util.List;

import java.io.IOException;
import java.util.Scanner;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.FSDataInputStream;
import org.apache.hadoop.fs.FileSystem;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.util.LineReader;



public class CreateBTree {
	
	private final static String INDEX_PATH = "/user/hive/warehouse/dir/indexTable";
	
	public static void main(String []args) throws IOException {
		
//		BTree<KeyInteger, RecordString> tree = null;
//		tree = new BTree<KeyInteger, RecordString>(2);
		
		Configuration conf = new Configuration();
		FileSystem hdfs = FileSystem.get(conf);
		String tableStringPath = hdfs.getName() + CreateBTree.INDEX_PATH;
		System.out.println(tableStringPath);
		
		Path tablePath = new Path(tableStringPath);
		FSDataInputStream inputStream = hdfs.open(tablePath);
		Text line = new Text();
		LineReader reader = new LineReader(inputStream);
		
		while (reader.readLine(line) > 0) {
			String [] arr = line.toString().split("\t");
			
			int id = Integer.valueOf(arr[1]) / Driver.CHILD_TABLE_SIZE;
			String path = arr[2];
			
			KeyInteger key = new KeyInteger(id);
			RecordString record = new RecordString(path);
			BTree.getInstance().insert(key, record);
		}
		
		
		// System.out.println("Tree has been built");
		// System.out.println("Print the id you want to find :");
		// Scanner scanner = new Scanner(System.in);
		// int num = scanner.nextInt() / Driver.CHILD_TABLE_SIZE;
		// System.out.println(num);
		
		// RecordString result = (RecordString) BTree.getInstance().get(new KeyInteger(num));
		// System.out.println(result.getValue());
	}
}
