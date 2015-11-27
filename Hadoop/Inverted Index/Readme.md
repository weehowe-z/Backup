# HomeWork 2 倒排索引

------

## 文件结构
- 根目录下包含所有编译出来的 **class**
- 源代码文件为 **InvertedIndex.java**

## 使用说明


####  1. 编译及运行

```
$ /javac -cp $HADOOP_CLASSPATH InvertedIndex.java
$ /tar -cvf InvertedIndex.jar *.class
$ /hadoop jar InvertedIndex.jar InvertedIndex
  inputFolderPath outputFolderPath
```

> 输入输出的路径是 HDFS 中的位置，且需确保输入文件夹中不包含非法的对象（如文件夹）


#### 2. 查看 **MapReduce** 结果

```
$ /hadoop fs -cat /outputFolderPath/part-r-00000
```


## 其他

> 为什么 **Map** 阶段使用单词和URL作为 **Key**，又在  **Combiner** 阶段修改 ?

> 使用单词和URL作为 **Key** 的主要目的是，利用 **Map** 的默认排序，方便后续计算相同路径下的词频。因此也需要添加 **Combiner** 阶段对 **<KEY,VALUE>** 进行处理。

> `setOutputKeyClass` 和 `setOutputValueClass` 的设置包含了 **Map** 和 **Reduce**， 如果需要设置 **Map** 的输出类型，需要使用 `setMapOutputKeyClass` 和 `setMapOutputValueClass`


------

*&copy; 2015  [weehowe-z][1]* &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;*Fork me on [Github][2]*

[1]: http://blog.delvin.xyz
[2]: https://github.com/weehowe-z