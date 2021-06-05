import "/node_modules/jquery/dist/jquery.min.js";
import "/socket.io/socket.io.js";

const URL = document.URL.substring(0, document.URL.lastIndexOf("/"));
const socket = io.connect(URL);

function comprobarAC(temperatura) {
	if(temperatura > 30 && $("#AC").text() == "apagado") {
		socket.emit("sistemas", {nombre: "Aire", valor: "encendido"});
		socket.emit("alerta", {nombre: "Aire", valor: temperatura});
	}
	else if (temperatura < 21 && $("#AC").text() == "encendido") {
		socket.emit("sistemas", {nombre: "Aire", valor: "apagado"});
	}
}

function comprobarCalefaccion(temperatura) {
	if(temperatura >= 21 && $("#cal").text() == "encendida") {
		socket.emit("sistemas", {nombre: "Calefaccion", valor: "apagada"});
	}
	else if (temperatura < 21 && $("#cal").text() == "apagada") {
		socket.emit("sistemas", {nombre: "Calefaccion", valor: "encendida"});
		socket.emit("alerta", {nombre: "Calefaccion", valor: temperatura});
	}
}

function comprobarPersianas(lum) {
	if(lum >= 50 && $("#persianas").text() == "bajadas") {
		socket.emit("sistemas", {nombre: "Persianas", valor: "subidas"});
		socket.emit("alerta", {nombre: "Persianas", valor: lum});
	}
	else if (lum < 50 && $("#persianas").text() == "subidas") {
		socket.emit("sistemas", {nombre: "Persianas", valor: "bajadas"});
	}
}

function comprobarLuces(lum) {
	if(lum < 50 && $("#luces").text() == "apagadas") {
		socket.emit("sistemas", {nombre: "Luces", valor: "encendidas"});
		socket.emit("alerta", {nombre: "Luces", valor: lum});
	}
	else if (lum >= 50 && $("#luces").text() == "encendidas") {
		socket.emit("sistemas", {nombre: "Luces", valor: "apagadas"});
	}
}

function actualizaciones () {
	socket.on("connect", ()=>{
		socket.emit("conexion", "agente");
	});

	socket.on("actualizar-sensores", (event) => {
		if(event.nombre == "Temperatura"){
			$("#temperatura").text(event.valor);
			comprobarAC(event.valor);
			comprobarCalefaccion(event.valor);
		}
		else if (event.nombre == "Luminosidad"){
			$("#nivel-lum").text(event.valor);
			comprobarPersianas(event.valor);
			comprobarLuces(event.valor);
		}
	});

	socket.on("actualizar-sistemas", (event) => {
		if (event.nombre == "Aire")
			$("#AC").text(event.valor);
		else if (event.nombre == "Calefaccion")
			$("#cal").text(event.valor);
		else if (event.nombre == "Persianas")
			$("#persianas").text(event.valor);
		else if (event.nombre == "Luces")
			$("#luces").text(event.valor);
	});
}

$(() => {
	actualizaciones();
});
