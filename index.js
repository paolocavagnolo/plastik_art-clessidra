'use strict';

const Hapi = require('hapi');

const SerialPort = require('serialport');
const myPort = new SerialPort('/dev/ttyACM0', {baudRate: 9600});

const server = new Hapi.Server();

server.connection({ port: 80 });

server.bind({
   myPort: myPort
});


server.register([
    require('inert')
], (err) => {
   if (err) {
       throw err;
   }

   server.route(require('./routes'));

   server.start(() => {

       console.log('Server listening at:', server.info.uri);
  });
});