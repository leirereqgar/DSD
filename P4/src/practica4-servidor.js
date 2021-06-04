var http = require("http");
var url = require("url");
var fs = require("fs");
var path = require("path");
var socketio = require("socket.io");


var MongoClient = require("mongodb").MongoClient;
var MongoServer = require("mongodb").Server;
var mimeTypes = {
	"html": "text/html",
	"jpeg": "image/jpeg",
	"jpg": "image/jpeg",
	"png": "image/png",
	"js": "text/javascript",
	"css": "text/css",
	"swf": "application/x-shockwave-flash"
};

var httpServer = http.createServer(
	function(request, response) {
		var uri = url.parse(request.url).pathname;
		if (uri=="/sensores")
			uri = "/html/practica4-sensores.html";
		else if (uri=="/cliente")
			uri = "/html/practica4-cliente.html";
		else if (uri=="/agente")
			uri = "/html/practica4-agente.html";

		var fname = path.join(process.cwd(), uri);
		fs.exists(fname, function(exists) {
			if (exists) {
				fs.readFile(fname, function(err, data){
					if (!err) {
						var extension = path.extname(fname).split(".")[1];
						var mimeType = mimeTypes[extension];
						response.writeHead(200, {"Content-Type" : mimeType});
						response.write(data);
						response.end();
					}
					else {
						response.writeHead(200, {"Content-Type": "text/plain"});
						response.write("Error de lectura en el fichero: "+uri);
						response.end();
					}
				});
			}
			else{
				console.log("Peticion invalida: "+uri);
				response.writeHead(200, {"Content-Type": "text/plain"});
				response.write("404 Not Found\n");
				response.end();
			}
		});
	}
);

MongoClient.connect("mongodb://localhost:27017/", { useUnifiedTopology: true }, (err, client) => {
	httpServer.listen(8080);
	var io = socketio(httpServer);
	const db = client.db("practica");
	const historial = "historial";

	db.collections((err, colls) => {
		// Borrar el historial al iniciar cada ejecución del servidor
		if(colls.find((item) => {return item.collectionName == historial;}))
			db.dropCollection(historial);

		db.createCollection(historial, (err, collection)=>{
			io.sockets.on("connection", (client) => {
				const referer = client.handshake.headers.referer;
				// El tipo es el cliente que llama al servidor, es la palabra que
				// vaya después de la última /: cliente, sensores, agente
				const tipo = referer.substring(referer.lastIndexOf("/")+1, referer.length);

				// Avisar por consola que se ha conectado
				client.on("conexion", (tipo)=>{
					console.log("Se ha conectado un: " + tipo);
				});

				client.on("alerta", (content) => {
					io.sockets.emit("recibir-alerta", content);
				});

				client.on("accion-usuario", (content) =>{
					io.sockets.emit("recibir-accion", content);
				});

				client.on("sensores", (sensor) =>{
					collection.insertOne({
						nombre: sensor.nombre,
						valor: sensor.valor,
						fecha: new Date()
					});

					collection.find().limit(1).sort({$natural:-1}).toArray((err, results) =>{
						io.sockets.emit("actualizar-sensores", results[0]);
					});
				});

				client.on("sistemas", (sistema) => {
					collection.insertOne({
						nombre: sistema.nombre,
						valor: sistema.valor,
						fecha: new Date()
					});
					collection.find().limit(1).sort({$natural:-1}).toArray((err, results) =>{
						io.sockets.emit("actualizar-sistemas", results[0]);
					});
				});
			});
		});
	});
});

console.log("Servicio MongoDB iniciado");
