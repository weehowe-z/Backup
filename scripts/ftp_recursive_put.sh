#!/bin/sh

# ftp cli dose not support recursive put
# use ncftp instead
# both of them only support `rm` and `rmdir` without flags like '-rf'
# ....残念だな

# [Install `ncftp` first]

HOST='202.120.39.121'
PORT='2188'
USER='kc'
PASSWD='kc'
REMOTE_DIR='C39/'
LOCAL_DIR='_site/*'

ncftpput -u $USER -p $PASSWD -P $PORT -R $HOST $REMOTE_DIR $LOCAL_DIR

# ftp -n $HOST <<END_SCRIPT
#
# quote USER $USER
# quote PASS $PASSWD
#
# delete $REMOTE_FILE
# put $LOCAL_FILE
#
# ls
#
# quit
# END_SCRIPT
#
# exit 0
