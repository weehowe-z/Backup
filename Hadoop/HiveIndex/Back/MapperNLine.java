package Test;

import java.io.IOException;
import java.util.StringTokenizer;

import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Mapper;


public class MapperNLine extends Mapper<LongWritable, Text, LongWritable, Text> {

	
    @Override
    public void map(LongWritable key, Text value, Context context)
          throws IOException, InterruptedException {

    	String string = value.toString();
    	String [] result = string.split("\t");
    	LongWritable longWritable = new LongWritable();
    	longWritable.set((Long.valueOf(result[0])));
    	Text text = new Text();
    	text.set(result[1]);
    	
    	//longWritable-id, text-name;
    	context.write(longWritable, text);
    	
    }
}

