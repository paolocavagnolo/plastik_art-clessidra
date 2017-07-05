#Raspberry configuration

- password: "associazione di jacopo"
- aggiornato tutto: 29-06-2017 13:00

#Router configuration

- SSID: "clessidra"
- PSK: "cesena2017"

#HAPI configuration
- create folder 'clessidra'
- create 'package.json'
- 'npm install --save hapi@13'
- create 'index.js'
- wget https://nodejs.org/dist/v4.2.4/node-v4.2.4-linux-armv6l.tar.gz
- sudo mv node-v4.2.4-linux-armv6l.tar.gz /opt
- cd /opt
- sudo tar -xzf node-v4.2.4-linux-armv6l.tar.gz
- sudo mv node-v4.2.4-linux-armv6l nodejs
- sudo rm node-v4.2.4-linux-armv6l.tar.gz
- sudo ln -s /opt/nodejs/bin/node /usr/bin/node
- sudo ln -s /opt/nodejs/bin/npm /usr/bin/npm
