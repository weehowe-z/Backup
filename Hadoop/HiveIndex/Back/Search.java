package Test;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.Statement;

public class Search {
	
	private final static String HIVE_PATH = "/user/hive/warehouse/dir/";

	private static KeyInteger searchNum = new KeyInteger(123456);
	private static String driver = "org.apache.hive.jdbc.HiveDriver";
	private static String sql = "";
	private static ResultSet res;
	
	public static void main(String[] args) throws Exception {
		Class.forName(driver);
		Connection conn = DriverManager.getConnection("jdbc:hive2://localhost:10000/default", "hive", "hive");
		Statement st = conn.createStatement();
		
		long startBtree = System.currentTimeMillis();
		RecordString tableName = (RecordString)BTree.getInstance().get(searchNum);
		int length = Search.HIVE_PATH.length();
		sql = "select * from " + tableName.value.substring(length) + " where key==" + searchNum;
		res = st.executeQuery(sql);
		System.out.println(res.getString("name") + "\n");
		
		long endBtree = System.currentTimeMillis();
		System.out.println("Btree time: " + (endBtree - startBtree) + "\n");
		
		long startNoIndex = System.currentTimeMillis();
		sql = "select * from source where key==" + searchNum.toString();
		res = st.executeQuery(sql);
		System.out.println(res.getString("name") + "\n");
		long endNoIndex = System.currentTimeMillis();
		System.out.println("No index time: " + (endNoIndex - startNoIndex) + "\n");
	}
}
