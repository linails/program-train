/*
 * Progarm Name: server-http.js
 * Created Time: 2016-12-05 13:49:50
 * Last modified: 2016-12-05 14:24:50
 */

var http = require('http'), io = require('socket.io');

var server = http.createServer(function(req, res){
    res.writeHead(200, {'Content-Type':'text/html'});
    res.end('<h1>Hello Socket ...</h1>');
});

server.listen(9999);

var socket = io.listen(server);
socket.on('connection', function(client){
    client.on('message', function(event){
        console.log('Received message from client', event);
    });

    client.on('disconnect', function(){
        clearInterval(interval);
        console.log('Server has disconnect');
    });

    var interval = setInterval(function(){
        client.send('This is a message from the server !' + new Date().getTime);
    });

});

