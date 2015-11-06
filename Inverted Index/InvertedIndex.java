import java.io.IOException;
import java.util.StringTokenizer;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.mapreduce.lib.input.FileSplit;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;

public class InvertedIndex {

  public static class TokenizerMapper
       extends Mapper<Object, Text, Text, Text>{

    private final static String delim = " ,.!;?:\"\'";//all signs in delim will be ommited
    private final static String one = "1";
    private Text outputKey = new Text();
    private Text outputValue = new Text(one);

    public void map(Object key, Text value, Context context) throws IOException, InterruptedException {
      Path filePath = ((FileSplit) context.getInputSplit()).getPath();
      String fileName = filePath.getName();
      StringTokenizer str = new StringTokenizer(value.toString(),delim);
      while (str.hasMoreTokens()) {
        outputKey.set(str.nextToken()+":"+fileName);
        context.write(outputKey, outputValue);
      }
    }
  }

  //[important] Optional Between map and reduce to reduce burden of big data/type change
  public static class Combiner
       extends Reducer<Text,Text,Text,Text> {
    private Text result = new Text(); 
    private Text outputKey = new Text();
    private Text outputValue = new Text();
   	//Implementing this interface allows an object to be the target of the "foreach" statement.
    public void reduce(Text key, Iterable<Text> values,Context context) throws IOException, InterruptedException {
      int sum = 0;
      for (Text val : values) {
      	//System.out.println(val.toString());
        sum +=  Integer.parseInt(val.toString());
      }
      String[] parts = key.toString().split(":");
      outputKey.set(parts[0]);
      outputValue.set(parts[1]+":"+String.valueOf(sum));
      //System.out.println("Changing "+parts[0] +" " +parts[1]+":"+String.valueOf(sum));
	  context.write(outputKey, outputValue);
    }
  }

  public static class IntSumReducer
       extends Reducer<Text,Text,Text,Text> {
    //private IntWritable result = new IntWritable();
    private Text result = new Text(); 
    private Text outputValue = new Text();
   	//Implementing this interface allows an object to be the target of the "foreach" statement.
    public void reduce(Text key, Iterable<Text> values,Context context) throws IOException, InterruptedException {
      String fileList = "";
      for (Text val : values) {
        if (fileList != ""){
          fileList = val.toString() + "," + fileList;
        }
        else {
          fileList = val.toString();
        }
      }
      outputValue.set(fileList);
	  context.write(key, outputValue);
    }
  }

  public static void main(String[] args) throws Exception {
  	if (args.length!=2) {
        	System.err.println("Error paths specifiction.");
        	System.err.println("Plz specify [hadoop setting] InvertedIndex  inputPath  outputPath.");
        	System.exit(1);
        }
    Configuration conf = new Configuration();
    Job job = Job.getInstance(conf, "Inverted Index");
    job.setJarByClass(InvertedIndex.class);
    job.setMapperClass(TokenizerMapper.class);
    //[Important]if Use Combiner and Reducer as the same class ,the imput must match out put !!!
    job.setCombinerClass(Combiner.class);
    job.setReducerClass(IntSumReducer.class);
    job.setOutputKeyClass(Text.class);
    job.setOutputValueClass(Text.class);
    //[Important]if map reduce has different output type, must set class respectively!!
    //job.setMapOutputKeyClass(Text.class);
    //job.setMapOutputValueClass(IntWritable.class);
    FileInputFormat.addInputPath(job, new Path(args[0]));
    FileOutputFormat.setOutputPath(job, new Path(args[1]));
    System.exit(job.waitForCompletion(true) ? 0 : 1);
  }
}