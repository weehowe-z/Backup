package Test;


import java.net.URI;
import java.io.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

import org.apache.hadoop.io.Text;
import org.apache.hadoop.fs.*;
import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.conf.Configured;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.IOUtils;

import org.apache.hadoop.mapred.JobConf;
import org.apache.hadoop.mapred.OutputFormat;
import org.apache.hadoop.mapred.lib.MultipleOutputs;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.input.NLineInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;
import org.apache.hadoop.mapreduce.lib.output.LazyOutputFormat;
import org.apache.hadoop.mapreduce.lib.output.TextOutputFormat;
import org.apache.hadoop.util.Progressable;
import org.apache.hadoop.util.LineReader;
import org.apache.hadoop.util.Tool;
import org.apache.hadoop.util.ToolRunner;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;


public class Driver extends Configured implements Tool {
    private static String username = "hadoopuser";
    private static String password = "zwh19hy1f68";
    private static String sql = "";
    private static ResultSet res;
    // private static String INPUT_PATH = "/home/hadoopuser/source.txt";
    private final static String INPUT_PATH = "/home/hadoopuser/specpro2/source.txt";
    private final static String INDEX_PATH = "/user/hive/warehouse/dir/indexTable";
    private final static String MAPRED_INPUT_PATH = "/user/hive/warehouse/input/source.txt";
    private final static String driver = "org.apache.hive.jdbc.HiveDriver";
    public final static int CHILD_TABLE_SIZE = 10000;


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

    public static BTree<Integer, String> createBTree() throws IOException {
        
        Configuration conf = new Configuration();
        FileSystem hdfs = FileSystem.get(conf);
        String tableStringPath = hdfs.getName() + INDEX_PATH;
        System.out.println(tableStringPath);
        
        BTree<Integer, String> tree = new BTree<Integer, String>();
        // The name of the file to open.

        // This will reference one line at a time
        String line = null;
        FileReader fileReader = new FileReader(INPUT_PATH);
        // Always wrap FileReader in BufferedReader.
        BufferedReader bufferedReader = new BufferedReader(fileReader);
        while((line = bufferedReader.readLine()) != null) {
                String[] var = line.split("\t");
                tree.put(Integer.parseInt(var[0]),var[1]);
            }   
        bufferedReader.close();         
        
        return tree;
        // System.out.println("Print the id you want to find :");
        // Scanner scanner = new Scanner(System.in);
        // Integer num = scanner.nextInt();
        // String result = tree.get(num);
        // System.out.println(result);
    }

    public static void main(String[] args) throws Exception {
    	
    	//Initial Operation for Hive Connection
    	Class.forName(driver);
		Connection conn = DriverManager.getConnection("jdbc:hive2://localhost:10000/default", username, password);
		Statement st = conn.createStatement();
		
		//SQL statements to create the source table and load the local data into the table
        sql = "drop table source";
        st.execute(sql);
		sql = "create table source (key int, name string) row format delimited fields terminated by '\t'";
		st.execute(sql);
		//sql = "select user()";
		sql = "load data local inpath '" + INPUT_PATH + "' into table source";
		st.execute(sql);
		
        copy();
        int exitCode = ToolRunner.run(new Configuration(), new Driver(), args);
        // createBTree();
        // CreateIndexFile.createFiles();

        System.exit(exitCode);
    }

    public static void copy() throws Exception{
        String src = INPUT_PATH;
        String dst = MAPRED_INPUT_PATH;
        Configuration conf = new Configuration();
        FileSystem fs = FileSystem.get(URI.create(dst),conf);
        InputStream in = new BufferedInputStream(new FileInputStream(src));
        OutputStream out = fs.create(new Path(dst), new Progressable(){
            public void progress(){
                System.out.print(".");
            }
        });
        IOUtils.copyBytes(in, out, 4096, true);
    }
}
