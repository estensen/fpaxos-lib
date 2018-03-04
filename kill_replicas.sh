for pid in $(ps -ef | grep "./sample" | awk '{print $2}'); do kill -9 $pid; done
