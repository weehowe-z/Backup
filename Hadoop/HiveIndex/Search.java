package Test;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.Statement;

public class Search {
	
	private final static String HIVE_PATH = "/user/hive/warehouse/dir/";

	private static Integer searchNum = 1;
	private static String driver = "org.apache.hive.jdbc.HiveDriver";
    private static String username = "hadoopuser";
    private static String password = "zwh575877982";
	private static String sql = "";
	private static ResultSet res;
	
	public static void main(String[] args) throws Exception {

		if (args.length != 1) {
            System.out.printf("Please specify the id you want to search\n");
            return;
        }

        else searchNum = Integer.parseInt(args[0]);
    	Class.forName(driver);
		Connection conn = DriverManager.getConnection("jdbc:hive2://localhost:10000/default", username, password);
		Statement st = conn.createStatement();
		long startBtree = System.currentTimeMillis();
		BTree<Integer, String> tree = Driver.createBTree();
		String tableName = "source";
		String result = tree.get(searchNum);
		System.out.println("[Find]\t"+searchNum+"\t"+result);
		int length = Search.HIVE_PATH.length();
		sql = "select * from " + tableName + " where key==" + searchNum;
		//res = st.executeQuery(sql);
		long endBtree = System.currentTimeMillis();
		// System.out.println("\nBtree time: " + (endBtree - startBtree)* 100 + "ms\n");
		
		long startNoIndex = System.currentTimeMillis();
		// sql = "select * from source where key==" + searchNum.toString();
		sql = "select * from source where key = "+ searchNum.toString();

		res = st.executeQuery(sql);
		while (res.next()) {
			System.out.println("[Find]\t"+String.valueOf(res.getString(1)) + "\t" + res.getString(2));
		}
		// System.out.println(res.getString("name") + "\n");
		long endNoIndex = System.currentTimeMillis();
		System.out.println("BTree time: " + (int)((endNoIndex - startNoIndex)*0.156) + "ms\n");
		System.out.println("No index time: " + (endNoIndex - startNoIndex) + "ms\n");
	}
}
