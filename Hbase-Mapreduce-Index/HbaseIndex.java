
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.hbase.HBaseConfiguration;
import org.apache.hadoop.hbase.KeyValue;
import org.apache.hadoop.hbase.client.Put;
import org.apache.hadoop.hbase.client.Result;
import org.apache.hadoop.hbase.client.Scan;
import org.apache.hadoop.hbase.io.ImmutableBytesWritable;
import org.apache.hadoop.hbase.mapreduce.TableMapReduceUtil;
import org.apache.hadoop.hbase.mapreduce.TableMapper;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.lib.output.NullOutputFormat;

public class HbaseIndex {
	
//	public static class HbaseMapper extends 
//		TableMapper<ImmutableBytesWritable, Put>{
//		private byte[] family;
//		private HashMap<byte[],ImmutableBytesWritable> indexes;
//		
//		public void map(ImmutableBytesWritable rowKey, Result result, Context context)
//			throws IOException, InterruptedException{
//				for (Map.Entry<byte[], ImmutableBytesWritable> index: indexes.entrySet()){
//					byte[] qualifiers = index.getKey();
//					ImmutableBytesWritable tableName = index.getValue();
//					byte[] value = result.getValue(family, qualifiers);
//					
//					if (value!=null){
//						Put putRow = new Put(value);
////						putRow.add(value, qualifier, value)
//						context.write(tableName,putRow);
//					}
//					
//				}
//		}
//	}
	
	public static class HbaseMapper extends
		TableMapper<ImmutableBytesWritable, Put> {
		
		public void map(ImmutableBytesWritable row, Result values, Context context) throws InterruptedException, IOException {
			System.out.println("mapping!");
			byte[] name = values.getValue("Information".getBytes(), "name".getBytes());
			System.out.println(new String(name) );
			System.out.println(new String(values.getRow()));
			context.write(row, resultToPut(row,values));
		}
		
	  	private static Put resultToPut(ImmutableBytesWritable row, Result values) throws IOException {
	  		byte[] name = values.getValue("Information".getBytes(), "name".getBytes());
	  		Put put = new Put(name);
	  		put.addColumn("Row".getBytes(), "row".getBytes(), row.get());
			return put;
	   	}
		
//			for (Map.Entry<byte[], byte[]>entry : row.getFamilyMap(familyName.getBytes()).entrySet()){
//				String key = new String(entry.getKey());
//				String value = new String(entry.getValue());
//				Sy
//		   }
		
	}
		
	public static void main(String[] args) throws Exception  {
	  	if (args.length!=2) {
        	System.err.println("Error args specifiction.");
        	System.err.println("Plz specify [hadoop setting] HbaseIndex TableName ColumnFamily  ColumnName");
        	System.exit(1);
        }
		
		String tableName = args[0];
		String indexTableName = args[1];
		
		Configuration conf = HBaseConfiguration.create();
		Job job = Job.getInstance(conf,"HbaseIndex");
		job.setJarByClass(HbaseIndex.class);
		
		Scan scan = new Scan();
		scan.setCaching(500);
		scan.setCacheBlocks(false);
		
		TableMapReduceUtil.initTableMapperJob(tableName,scan,HbaseMapper.class,null,null,job);
		TableMapReduceUtil.initTableReducerJob(indexTableName,null,job);
		//job.setOutputFormatClass(NullOutputFormat.class);//only read
		job.setNumReduceTasks(0);//There will be default reducer
		
		System.exit(job.waitForCompletion(true) ? 0 : 1);
		
	}

}
