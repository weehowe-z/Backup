# HomeWork 3 使用MapReduce构建Hbase索引

------

## 使用说明


####  1. 编译及运行

```
$ /javac -cp $CLASSPATH HBaseIndex.java
$ /tar -cvf HBaseIndex.jar *.class
$ /hadoop jar HBaseIndex.jar HBaseIndex tableName indexName columnName
```

- **tableName** 原始输入表，会默认初始化填充数据
- **indexName** 索引表
- **columnName** 需要创建索引的列名，样例中仅支持 `name` `email` `id`
- 指定参数后，程序会自动检测是否已经存在该表，并删除重建！ 
- 初始化后，输入表的内容样式为：

| Row | Information:name | Information:email | Information:id |
| --- |:------:| -----:|-----:|
| 0 | alice | alice@qq.com | 5132424123 |
| 1 | bob | bob@gmail.com | 123231243|

如需修改，可以在代码中 `createTableData` 函数修改

#### 2. 查看结果

程序执行完后会自动打印创建的索引。
或者使用 `hbase shell` 观察：
```
$ /hbase shell
$ hbase(main):001:0>  scan 'IndexTableName'
```



------

*&copy; 2015  [weehowe-z][1]* &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;*get source code on [Github][2]*

[1]: http://blog.delvin.xyz
[2]: https://github.com/weehowe-z	