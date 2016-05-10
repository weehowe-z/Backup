package Test;

import java.io.IOException;

import java.util.regex.Pattern;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.FSDataInputStream;
import org.apache.hadoop.fs.FSDataOutputStream;
import org.apache.hadoop.fs.FileStatus;
import org.apache.hadoop.fs.FileSystem;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapred.lib.NLineInputFormat;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;
import org.apache.hadoop.util.LineReader;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;



public class CreateIndexFile {
	
	//Basic Path Constant
	private final static String HIVE_PATH = "/user/hive/warehouse/dir/";
	private final static String HIVE_WAREHOUSE_PATH = "/user/hive/warehouse/";
	
	//Basic SQlite Constant
	private static String driver = "org.apache.hive.jdbc.HiveDriver";
	private static String sql = "";
	private static ResultSet res;
	
	
	public static void createFiles() throws IOException, ClassNotFoundException, InterruptedException, Exception {
    	
		//Initial Operation for Hive Connection
		Class.forName(driver);
		Connection conn = DriverManager.getConnection("jdbc:hive2://localhost:10000/default", "hive", "hive");
		Statement st = conn.createStatement();
		
		//Initial HDFS Configuration
		Configuration conf = new Configuration();
		FileSystem hdfs = FileSystem.get(conf);
		Path findf = new Path(CreateIndexFile.HIVE_PATH);
		
		//Annotation:
		//ParentPath & ParentLength for the convenience 
		//ParentPath -> hdfs://localhost:9000
		
		@SuppressWarnings("deprecation")
		String parentPath = hdfs.getName() + CreateIndexFile.HIVE_PATH;
		int parentLength = parentPath.length();
		int childTableLength = CreateIndexFile.HIVE_PATH.length();
		
		//Regular expression to find the child table file
		Pattern pattern = Pattern.compile("^part-m-.*");
		
		StringBuilder stringBuilder = new StringBuilder();
		FileStatus []status = hdfs.listStatus(findf);
		for (FileStatus fs : status) {
			
			//Absolution Path
			String childPathString = fs.getPath().toString();
//			System.out.println(childPathString);
			
			//Create Child Table in Hive(HDFS)
			sql = "create table " + childPathString.substring(parentLength) + " (key int, name string) row format delimited fields terminated by '\t'";
			res = st.executeQuery(sql);
			sql = "load data inpath '" + childPathString + "' overwrite into table " + childPathString.substring(parentLength);
			res = st.executeQuery(sql);
			
			
			if (pattern.matcher(childPathString.substring(parentLength)).matches()) {
				Path childPath = new Path(childPathString);
				FSDataInputStream inputStream = hdfs.open(childPath);
				LineReader reader = new LineReader(inputStream);
				
				Text line = new Text();
				String resultStart = null;
				if (reader.readLine(line) > 0) {
					resultStart = line.toString();
				}
				
				//TODO better performace
				String resultEnd = null;
				while (reader.readLine(line) > 0) {
					//Read one line each time and use the last one line's string
					resultEnd = line.toString();
				}

				//Get start, end and the hivePath
				int start = Integer.valueOf(resultStart.split("\t")[0]);
				int end = Integer.valueOf(resultEnd.split("\t")[0]);
				String result = start + "\t" + end + "\t" + 
						CreateIndexFile.HIVE_WAREHOUSE_PATH + childPath.getName() + "\n";
				stringBuilder.append(result);
				
				
				//TODO : Append Operation does not work 
//				byte[] buff = result.getBytes();			
//				FSDataOutputStream outputStream = hdfs.append(indexTable);
//				outputStream.write(buff, 0, buff.length);
				
			}
		}

		byte[] buff = stringBuilder.toString().getBytes();
		Path indexTable = new Path(CreateIndexFile.HIVE_PATH + "indexTable");
		FSDataOutputStream outputStream = hdfs.create(indexTable);
		outputStream.write(buff, 0, buff.length);

	}
	
}
