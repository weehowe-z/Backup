import java.net.URI;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.BufferedInputStream;
import java.io.FileInputStream;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.*;
import org.apache.hadoop.io.IOUtils;
import org.apache.hadoop.util.Progressable;

public class FileCopyWithProgress{
	public static void main(String[] args) throws Exception{
		String src = args[0];
		String dst = args[1];
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