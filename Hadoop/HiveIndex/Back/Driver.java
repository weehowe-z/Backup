package Test;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.conf.Configured;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.LongWritable;


import org.apache.hadoop.mapred.JobConf;
import org.apache.hadoop.mapred.OutputFormat;
import org.apache.hadoop.mapred.lib.MultipleOutputs;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.input.NLineInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;
import org.apache.hadoop.mapreduce.lib.output.LazyOutputFormat;
import org.apache.hadoop.mapreduce.lib.output.TextOutputFormat;
import org.apache.hadoop.util.Tool;
import org.apache.hadoop.util.ToolRunner;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.Scanner;

import com.sun.jersey.core.impl.provider.entity.XMLJAXBElementProvider.Text;

public class Driver extends Configured implements Tool {
	private static String driver = "org.apache.hive.jdbc.HiveDriver";
	private static String sql = "";
	private static ResultSet res;
	public static final int CHILD_TABLE_SIZE = 10000;
    @Override
    public int run(String[] args) throws Exception {

        if (args.length != 2) {
            System.out
                  .printf("Two parameters are required for DriverNLineInputFormat- <input dir> <output dir>\n");
            return -1;
        }

        Job job = new Job(getConf());
        job.setJobName("NLineInputFormat example");
        job.setJarByClass(Driver.class);

        job.setInputFormatClass(NLineInputFormat.class);
        NLineInputFormat.addInputPath(job, new Path(args[0]));
        job.getConfiguration().setInt("mapreduce.input.lineinputformat.linespermap", Driver.CHILD_TABLE_SIZE);

        LazyOutputFormat.setOutputFormatClass(job, TextOutputFormat.class);
        FileOutputFormat.setOutputPath(job, new Path(args[1]));

        job.setMapperClass(MapperNLine.class);
        job.setNumReduceTasks(0);

        boolean success = job.waitForCompletion(true);
        return success ? 0 : 1;
    }

    public static void main(String[] args) throws Exception {
    	
    	//Initial Operation for Hive Connection
    	Class.forName(driver);
		Connection conn = DriverManager.getConnection("jdbc:hive2://localhost:10000/default", "hive", "hive");
		Statement st = conn.createStatement();
		
		//SQL statements to create the source table and load the local data into the table
		sql = "create table source (key int, name string) row format delimited fields terminated by '\t'";
		st.execute(sql);
		//sql = "select user()";
		sql = "load data local inpath '/home/hadoop/source.txt' into table source";
		st.execute(sql);
		
    	
		//创建子表文件
        int exitCode = ToolRunner.run(new Configuration(), new Driver(), args);
        
        //生成子表索引
        CreateIndexFile.createFiles();
        
        //生成B+树
//        CreateBTree.main(null);
        
//		System.out.println("Tree has been built");
//		System.out.println("Print the id you want to find :");
//		Scanner scanner = new Scanner(System.in);
//		int key = scanner.nextInt() / Driver.CHILD_TABLE_SIZE;
//		System.out.println(key);
		
//		RecordString result = (RecordString) BTree.getInstance().get(new KeyInteger(123456));
//		System.out.println(result.getValue());
        
        System.exit(exitCode);
    }
}
