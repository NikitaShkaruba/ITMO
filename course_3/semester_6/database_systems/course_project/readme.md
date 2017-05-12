### How to setup Cassandra
```bash
# Install Cassandra
$ yum install cassandra

# Change `listen_address: localhost` to `listen_address: 146.185.143.190`  
$ sudo vim /etc/cassandra/default.conf/cassandra.yml 

# Run cassandra. Check right ip address and port at this log line:
# Starting listening for CQL clients on /146.185.143.190:9042...
$ sudo cassandra -f
```

### How to setup Neo4j
```bash
# Neo4j has amazing documentation and output. Love it C:

# Install neo4j
$ yum install neo4j

# Uncomment and setup ip address here: dbms.connectors.default_listen_address=146.185.143.190
$ sudo vim /etc/neo4j/neo4j.conf

$ neo4j-admin set-initial-password {PASSWORD}

# Run neo4j. Check right ip address and port at this log line:
$ sudo systemctl start neo4j

# Check logs like that. Make sure "Bolt enabled on 146.185.143.190:7687" contains your ip
$ journalctl -e -u neo4j
```

## Foreword
I am not afraid to objective criticism, so feel free to write/tell me about my mistakes.
Have fun with my code :smirk: