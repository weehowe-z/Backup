import java.io.IOException;
import java.util.Map;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.hbase.HBaseConfiguration;
import org.apache.hadoop.hbase.HTableDescriptor;
import org.apache.hadoop.hbase.HColumnDescriptor;
import org.apache.hadoop.hbase.TableName;
import org.apache.hadoop.hbase.client.*;


public class HBaseOp {
	private static final String[] studentsName = {"Apple","Jack","Rose","Happer","Wenhao Zhu"};
	private static final String[] studentsEmail = {"Apple@apple.com","Jack@163.com","Rose@qq.com","Happer@sjtu.edu.cn","weehowe.z@gmail.com"};
	private static final String[] studentsID = {"5110232131","888888","01745678","110","5130309717"};
	private static final String tableName = "Students";
	private static final String familyName = "Information";
	private static final String indexTableName = "Index";
	private static final String indexFamilyName = "Row";
	public static void main(String[] args) throws IOException{
		//create connection
		Configuration config = HBaseConfiguration.create();
		Connection connection = ConnectionFactory.createConnection(config);
		HBaseAdmin admin = (HBaseAdmin)connection.getAdmin();
		
		//add original table
		TableName name = TableName.valueOf(tableName);
		HTableDescriptor tableDescriptor = new HTableDescriptor(name);
		tableDescriptor.addFamily(new HColumnDescriptor(familyName));
		admin.disableTable(name);
		admin.deleteTable(name);
		admin.createTable(tableDescriptor);	
		
		//add index table
		TableName indexName = TableName.valueOf(indexTableName);
		HTableDescriptor indexTableDescriptor = new HTableDescriptor(indexName);
		indexTableDescriptor.addFamily(new HColumnDescriptor(indexFamilyName));
		admin.disableTable(indexName);
		admin.deleteTable(indexName);
		admin.createTable(indexTableDescriptor);	
		
		@SuppressWarnings("deprecation")
		HTable table = new HTable(config, tableName);
		
		for (int i = 0; i < 5; ++i){
			System.out.println("Now adding "+studentsName[i]);
			Put put = new Put(Integer.toString(i).getBytes());
			put.addColumn(familyName.getBytes(), "name".getBytes(), studentsName[i].getBytes());
			put.addColumn(familyName.getBytes(), "email".getBytes(), studentsEmail[i].getBytes());
			put.addColumn(familyName.getBytes(), "id".getBytes(), studentsID[i].getBytes());
			table.put(put);
		}
		System.out.println("Finish Table Creation!\n");

		
		for (Result row: table.getScanner(familyName.getBytes())){
			System.out.format("Row %s\n",new String(row.getRow()));
			for (Map.Entry<byte[], byte[]>entry : row.getFamilyMap(familyName.getBytes()).entrySet()){
				String key = new String(entry.getKey());
				String value = new String(entry.getValue());
				System.out.format("%s:%s ",key,value);
			}
			System.out.print('\n');
		}
		
//		admin.disableTable(name);
//		admin.deleteTable(name);
		
	}
}
