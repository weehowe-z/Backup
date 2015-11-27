
import java.io.IOException;
import java.util.Map;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.hbase.HBaseConfiguration;
import org.apache.hadoop.hbase.HColumnDescriptor;
import org.apache.hadoop.hbase.HTableDescriptor;
import org.apache.hadoop.hbase.TableName;
import org.apache.hadoop.hbase.client.Connection;
import org.apache.hadoop.hbase.client.ConnectionFactory;
import org.apache.hadoop.hbase.client.HBaseAdmin;
import org.apache.hadoop.hbase.client.HTable;
import org.apache.hadoop.hbase.client.Put;
import org.apache.hadoop.hbase.client.Result;
import org.apache.hadoop.hbase.client.Scan;
import org.apache.hadoop.hbase.io.ImmutableBytesWritable;
import org.apache.hadoop.hbase.mapreduce.TableMapReduceUtil;
import org.apache.hadoop.hbase.mapreduce.TableMapper;
import org.apache.hadoop.mapreduce.Job;

public class HBaseIndex {
	
	private static final String[] studentsName = {"Apple","Jack","Rose","Happer","Wenhao Zhu"};
	private static final String[] studentsEmail = {"Apple@apple.com","Jack@163.com","Rose@qq.com","Happer@sjtu.edu.cn","weehowe.z@gmail.com"};
	private static final String[] studentsID = {"5110232131","888888","01745678","110","5130309717"};
	private static final String familyName = "Information";
	private static String tableName = "Students";
	private static String indexName = "Index";
	private static String columnName = "name";
	
	public static class HbaseMapper extends
		TableMapper<ImmutableBytesWritable, Put> {
		
		public void map(ImmutableBytesWritable row, Result values, Context context) throws InterruptedException, IOException {
			context.write(row, resultToPut(row,values));
		}
		
	  	private static Put resultToPut(ImmutableBytesWritable row, Result values) throws IOException {
	  		byte[] value = values.getValue(familyName.getBytes(), columnName.getBytes());
	  		Put put = new Put(value);
	  		put.addColumn(familyName.getBytes(), "row".getBytes(), row.get());
			return put;
	   	}
				
	}
	
	public static Job createJob(Configuration conf) throws IOException {
		
		Job job = Job.getInstance(conf,"HbaseIndex");
		job.setJarByClass(HBaseIndex.class);
		
		Scan scan = new Scan();
		scan.setCaching(500);
		scan.setCacheBlocks(false);
		
		TableMapReduceUtil.initTableMapperJob(tableName,scan,HbaseMapper.class,null,null,job);
		TableMapReduceUtil.initTableReducerJob(indexName,null,job);
		//job.setOutputFormatClass(NullOutputFormat.class);//only read
		job.setNumReduceTasks(0);//T	here will be default reducer
		return job;
	}
	
	public static void printTable(Configuration conf, String name) throws IOException{
		@SuppressWarnings({ "deprecation", "resource" })
		HTable table = new HTable(conf, name);
		System.out.println("\nResult:\n");
		for (Result row: table.getScanner(familyName.getBytes())){
			System.out.format("%s:%s\t",columnName,new String(row.getRow()));
			for (Map.Entry<byte[], byte[]>entry : row.getFamilyMap(familyName.getBytes()).entrySet()){
				String key = new String(entry.getKey());
				String value = new String(entry.getValue());
				System.out.format("%s:%s ",key,value);
			}
			System.out.print('\n');
		}
		System.out.format("\nor you can type \"hbase shell\" and \"scan '%s'\" to verify in shell\n",columnName);
	}
	
	public static void createTable(HBaseAdmin admin, String name) throws IOException{
		
		TableName tableName = TableName.valueOf(name);
		if (admin.isTableAvailable(name)){
			admin.disableTable(tableName);
			admin.deleteTable(tableName);
		}
		
		HTableDescriptor tableDescriptor = new HTableDescriptor(tableName);
		tableDescriptor.addFamily(new HColumnDescriptor(familyName));
		admin.createTable(tableDescriptor);	
	}

	public static void createTableData(HBaseAdmin admin, Configuration conf, String name) throws IOException{
		@SuppressWarnings({ "deprecation", "resource" })
		HTable table = new HTable(conf, tableName);
		
		for (int i = 0; i < 5; ++i){
			System.out.println("Now adding "+studentsName[i]);
			Put put = new Put(Integer.toString(i).getBytes());
			put.addColumn(familyName.getBytes(), "name".getBytes(), studentsName[i].getBytes());
			put.addColumn(familyName.getBytes(), "email".getBytes(), studentsEmail[i].getBytes());
			put.addColumn(familyName.getBytes(), "id".getBytes(), studentsID[i].getBytes());
			table.put(put);
		}
		System.out.println("Finish Table Creation!\n");
	}
	
	public static void initTable(Configuration conf) throws IOException {
		//create connection
		Configuration config = HBaseConfiguration.create();
		Connection connection = ConnectionFactory.createConnection(config);
		HBaseAdmin admin = (HBaseAdmin)connection.getAdmin();
		
		createTable(admin,tableName);
		createTable(admin,indexName);
		createTableData(admin,config,tableName);
		
	}
	
	
	public static void main(String[] args) throws Exception  {
	  	if (args.length!=3) {
        	System.err.println("Error args specifiction.");
        	System.err.println("Plz specify [hadoop setting] HBaseIndex TableName IndexName ColumnName");
        	System.exit(1);
        }
	  	if (!(args[2].equals("name") || args[2].equals("id") || args[2].equals("email"))){
	  		System.out.println(args[2]);
	  		System.err.println("Error columnName");
	  		System.err.println("Plz specify columnName as 'name', 'id' or 'email'");
	  		System.exit(1);
	  	}
		
		tableName = args[0];
		indexName = args[1];
		columnName = args[2];
		
		Configuration conf = HBaseConfiguration.create();
		initTable(conf);
		Job job = createJob(conf);
		boolean flag = job.waitForCompletion(true);
		if (!flag){
			System.err.println("Error mapreduce job!");
			System.exit(1);
		}
		else {
			printTable(conf,indexName);
		}
		
	}

}
