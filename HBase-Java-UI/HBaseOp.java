import java.io.IOException;
import java.util.Map;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.hbase.HBaseConfiguration;
import org.apache.hadoop.hbase.HTableDescriptor;
import org.apache.hadoop.hbase.HColumnDescriptor;
import org.apache.hadoop.hbase.TableName;
import org.apache.hadoop.hbase.client.*;


public class HBaseOp {

	public static void main(String[] args) throws IOException{
		Configuration config = HBaseConfiguration.create();
		Connection connection = ConnectionFactory.createConnection(config);
		HBaseAdmin admin = (HBaseAdmin)connection.getAdmin();
		TableName name = TableName.valueOf("test-table");
		HTableDescriptor tableDescriptor = new HTableDescriptor(name);
		tableDescriptor.addFamily(new HColumnDescriptor("family"));
		admin.createTable(tableDescriptor);
		System.out.println("Finish Creation!\n");
		
		HTable table = new HTable(config, name.getName());
		Put putRow = new Put("row2".getBytes());
		putRow.addColumn("family".getBytes(), "col2".getBytes(), "myValue211".getBytes());
		table.put(putRow);
		
		System.out.println("hahah!");
		
		for (Result row: table.getScanner("family".getBytes())){
			System.out.format("Rowname, %s\n",new String(row.getRow()));
			for (Map.Entry<byte[], byte[]>entry : row.getFamilyMap("family".getBytes()).entrySet()){
				String key = new String(entry.getKey());
				String value = new String(entry.getValue());
				System.out.format("haha %s,%s\n",key,value);
			}
		}
		
		admin.disableTable(name);
		admin.deleteTable(name);
		
	}
}
