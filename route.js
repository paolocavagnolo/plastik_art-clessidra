'use strict';

const Arduino = require('./handlers/arduino');

module.exports = [{
    method: 'GET',
    path: '/btn1',
    handler: Arduino.serial1
},{
	method: 'GET',
    path: '/btn2',
    handler: Arduino.serial2
},{
	method: 'GET',
    path: '/btn3',
    handler: Arduino.serial3
},{
	method: 'GET',
    path: '/btn4',
    handler: Arduino.serial4
},{
	method: 'GET',
    path: '/btn5',
    handler: Arduino.serial5
},{
	method: 'GET',
    path: '/btn6',
    handler: Arduino.serial6
},{
	method: 'GET',
    path: '/btn7',
    handler: Arduino.serial7
},{
	method: 'GET',
    path: '/btn8',
    handler: Arduino.serial8
},{
	method: 'GET',
    path: '/play',
    handler: Arduino.play
}];

