'use strict';

exports.play = function (request, reply) {

	reply.file('./website/index.html');

}

exports.serial1 = function (request, reply) {
    
	this.myPort.write('1'); 

	reply.file('./website/index.html');

}

exports.serial2 = function (request, reply) {
    
	this.myPort.write('2'); 

	reply.file('./website/index.html');

}

exports.serial3 = function (request, reply) {
    
	this.myPort.write('3'); 

	reply.file('./website/index.html');

}

exports.serial4 = function (request, reply) {
    
	this.myPort.write('4'); 

	reply.file('./website/index.html');

}

exports.serial5 = function (request, reply) {
    
	this.myPort.write('5'); 

	reply.file('./website/index.html');

}

exports.serial6 = function (request, reply) {
    
	this.myPort.write('6'); 

	reply.file('./website/index.html');

}

exports.serial7 = function (request, reply) {
    
	this.myPort.write('7'); 

	reply.file('./website/index.html');

}

exports.serial8 = function (request, reply) {
    
	this.myPort.write('8'); 

	reply.file('./website/index.html');

}

