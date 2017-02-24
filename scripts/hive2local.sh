#！/bin/bash
source ~/.bashrc
source ~/.bash_profile

function print_usage() {
        echo -e "$0 -d {DATE} -t {TABLE} -l {LIMIT}"
}

v_date=""
v_table=""
v_limit=""
while getopts "d:t:l:" opt
do
        case $opt in
                d )
                        v_date=$OPTARG;;
                t )
                        v_table=$OPTARG;;

                l )
                        v_limit=$OPTARG;;
                h )
                        print_usage;
                        exit 0
                        ;;
                ? )
                        handle_ret 1;;
                esac
done

SCRIPT_DIR=/home/work/shangzhengwu/cpu/script
FILE_DIR=/home/work/shangzhengwu/cpu/${v_table}/data

source ${SCRIPT_DIR}/source.sh

if [[ $v_date = "" ]]; then
    v_date=`date -d "1 days ago" +%Y%m%d`
fi

mkdir -p ${FILE_DIR}/${v_date}
DAY_DAT_FILE=${FILE_DIR}/${v_date}/${v_table}.dat
echo "`date`[info]]download data to local $DAY_DAT_FILE"
# 导出是否成功检测
if [[ -s $DAY_DAT_FILE ]]
then
    echo "$DAY_DAT_FILE had exit. will overwrite the old file.";
fi

INPUT_FILE=/app/ecom/weigou/weigou-ecst/hive/warehouse/dm.db/$v_table/dt=$v_date/

while [ 1 ]
     do
         cnt=`hadoop fs -ls ${INPUT_FILE}* 2>/dev/null | wc -l`
         size=`hadoop fs -dus ${INPUT_FILE} 2>/dev/null  | awk '{print $2}'`
         print_log "Number of report records parts:  $cnt "
         print_log "Size of report:  $size "
         if [ $cnt -gt 0 ] && [ $size -gt 0 ]
         then
              print_log "$2 $1 report ready!"
              break
         else
              print_log "$2 $1 report not ready!"
              sleep 600s
         fi
done

if [[ $v_limit = "" ]]
then
  hive -e "use dm;select * from ${v_table} where dt=$v_date"|sed 's/NULL/0/gm' > $DAY_DAT_FILE
else
  hive -e "use dm;select * from ${v_table} where dt=$v_date limit $v_limit"|sed 's/NULL/0/gm' > $DAY_DAT_FILE
fi
# hive -hivevar v_date="${v_date}" -i /home/work/app/svnroot/strategy-platform/sql/udf.sql -f dm_report_cu_monitor_daily_pv_media.sql|sed 's/NULL/0/gm' > $DAY_DAT_FILE

# 导出是否成功检测
if [[ ! -s $DAY_DAT_FILE ]]
then
    echo "$DAY_DAT_FILE download fail.";
    exit 1;
fi
