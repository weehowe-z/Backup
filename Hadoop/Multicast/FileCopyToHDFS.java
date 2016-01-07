import java.net.URI;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.BufferedInputStream;
import java.io.FileInputStream;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.*;
import org.apache.hadoop.io.IOUtils;

public class FileCopyToHDFS{
	public static void main(String[] args) throws Exception{
		String source = args[0];
		String destination = args[1];
		Configuration conf = new Configuration();//means deafult setting in hadoop core-site.xml
		FileSystem fileSystem = FileSystem.get(URI.create(destination),conf);
		InputStream InputFile = new BufferedInputStream(new FileInputStream(source));
		FSDataOutputStream OutputFile = fileSystem.create(new Path(destination));
		IOUtils.copyBytes(InputFile, OutputFile, 4096, true);
		//copyBytes(InputStream in, OutputStream out, int buffSize, boolean close)
	}
}