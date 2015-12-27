package Test;

import java.io.IOException;

import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.mapreduce.lib.output.MultipleOutputs;

public class ReducerNLine extends Reducer <LongWritable, Text, LongWritable, Text>{
	
	public static int cnt = 0;
	private MultipleOutputs <LongWritable, Text> multipleOutputs;
	
	Text result = new Text();
	
	@Override
	public void reduce(LongWritable key, Iterable<Text> values, Context context) throws IOException, InterruptedException {
		
		String readline = new String();
		for(Text value : values) {
			readline += value.toString() + "\n";
		}
		result.set(readline);
		System.out.println("hahahaha");
		context.write(key, result);
	}
	
	private String generateFileName(int cnt) {
		return String.valueOf(cnt) + "_roy7wt";
	}
	
	@Override
	public void setup(Context context) {
		multipleOutputs = new MultipleOutputs<LongWritable, Text>(context);
	}
	
	@Override
	public void cleanup(Context context) throws IOException, InterruptedException {
		multipleOutputs.close();
	}
}
