import "/node_modules/jquery/dist/jquery.min.js";
import "/socket.io/socket.io.js";

const URL = document.URL.substring(0, document.URL.lastIndexOf("/"));
const socket = io.connect(URL);

function AC () {
	var boton = $("#AC");

	boton.on("click", () => {
		if(boton.text() == "Encender") {
			socket.emit("sistemas", {nombre: "Aire acondicionado", valor: "encendido"});
			socket.emit("accion-usuario", {nombre: "Aire acondicionado", valor: "encendido"});
		}
		else if (boton.text() == "Apagar"){
			socket.emit("sistemas", {nombre: "Aire acondicionado", valor: "apagado"});
			socket.emit("accion-usuario", {nombre: "Aire acondicionado", valor: "apagado"});
		}
	});
}

function persianas() {
	var boton = $("#persianas");

	boton.on("click", () => {
		if(boton.text() == "Bajar") {
			socket.emit("sistemas", {nombre: "Persianas", valor: "bajadas"});
			socket.emit("accion-usuario", {nombre: "Persianas", valor: "bajadas"});
		}
		else {
			socket.emit("sistemas", {nombre: "Persianas", valor:"subidas"});
			socket.emit("accion-usuario", {nombre: "Persianas", valor:"subidas"});
		}
	});
}

function luces() {
	var boton = $("#luces");

	boton.on("click", () => {
		console.log("luces");
		if(boton.text() == "Encender") {
			socket.emit("sistemas", {nombre: "Luces", valor: "encendidas"});
			socket.emit("accion-usuario", {nombre: "Luces", valor: "encendidas"});
		}
		else {
			socket.emit("sistemas", {nombre: "Luces", valor:"apagadas"});
			socket.emit("accion-usuario", {nombre: "Luces", valor:"apagadas"});
		}
	});
}

function actualizaciones () {
	socket.on("connect", ()=>{
		socket.emit("conexion", "cliente");
	});

	socket.on("actualizar-sensores", (event) => {
		if(event.nombre == "Temperatura")
			$("#temperatura").text(event.valor);
		else if (event.nombre == "Luminosidad")
			$("#nivel-luminosidad").text(event.valor);
	});

	socket.on("actualizar-sistemas", (event) => {
		if (event.nombre == "Aire acondicionado") {
			var boton = $("#AC");
			if (event.valor = "encendido")
				boton.html("Apagar");
			else
				boton.html("Encender")
		}
		else if (event.nombre == "Persianas")
			$("#nivel-luminosidad").text(event.valor);
	});

}

$(() => {
	AC();
	persianas();
	luces();
	actualizaciones();
});
