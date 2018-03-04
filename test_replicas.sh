
./build/sample/replica 0 ./paxos.conf > 0.log &
echo 'started 0'
./build/sample/replica 1 ./paxos.conf > 1.log &
echo 'started 1'
./build/sample/replica 2 ./paxos.conf > 2.log &
echo 'started 2'
./build/sample/replica 3 ./paxos.conf > 3.log &
echo 'started 3'
sleep 2
./build/sample/client ./paxos.conf -p 0 -o 10 &
